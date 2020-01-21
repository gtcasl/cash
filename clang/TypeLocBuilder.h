//===--- TypeLocBuilder.h - Type Source Info collector ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//  This file defines TypeLocBuilder, a class for building TypeLocs
//  bottom-up.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_SEMA_TYPELOCBUILDER_H
#define LLVM_CLANG_LIB_SEMA_TYPELOCBUILDER_H

#include "clang/AST/ASTContext.h"
#include "clang/AST/TypeLoc.h"

namespace clang {

class TypeLocBuilder {
  enum { InlineCapacity = 8 * sizeof(SourceLocation) };

  /// The underlying location-data buffer.  Data grows from the end
  /// of the buffer backwards.
  char *Buffer;

  /// The capacity of the current buffer.
  size_t Capacity;

  /// The index of the first occupied byte in the buffer.
  size_t Index;

#ifndef NDEBUG
  /// The last type pushed on this builder.
  QualType LastTy;
#endif

  /// The inline buffer.
  enum { BufferMaxAlignment = alignof(void *) };
  llvm::AlignedCharArray<BufferMaxAlignment, InlineCapacity> InlineBuffer;
  unsigned NumBytesAtAlign4, NumBytesAtAlign8;

 public:
  TypeLocBuilder()
    : Buffer(InlineBuffer.buffer), Capacity(InlineCapacity),
      Index(InlineCapacity), NumBytesAtAlign4(0), NumBytesAtAlign8(0)
  {
  }

  ~TypeLocBuilder() {
    if (Buffer != InlineBuffer.buffer)
      delete[] Buffer;
  }

  /// Ensures that this buffer has at least as much capacity as described.
  void reserve(size_t Requested) {
    if (Requested > Capacity)
      // For now, match the request exactly.
      grow(Requested);
  }

  /// Pushes a copy of the given TypeLoc onto this builder.  The builder
  /// must be empty for this to work.
  void pushFullCopy(TypeLoc L);

  /// Pushes space for a typespec TypeLoc.  Invalidates any TypeLocs
  /// previously retrieved from this builder.
  TypeSpecTypeLoc pushTypeSpec(QualType T) {
    size_t LocalSize = TypeSpecTypeLoc::LocalDataSize;
    unsigned LocalAlign = TypeSpecTypeLoc::LocalDataAlignment;
    return pushImpl(T, LocalSize, LocalAlign).castAs<TypeSpecTypeLoc>();
  }

  /// Resets this builder to the newly-initialized state.
  void clear() {
#ifndef NDEBUG
    LastTy = QualType();
#endif
    Index = Capacity;
    NumBytesAtAlign4 = NumBytesAtAlign8 = 0;
  }

  /// Tell the TypeLocBuilder that the type it is storing has been
  /// modified in some safe way that doesn't affect type-location information.
  void TypeWasModifiedSafely(QualType T) {
#ifndef NDEBUG
    LastTy = T;
#endif
  }

  /// Pushes space for a new TypeLoc of the given type.  Invalidates
  /// any TypeLocs previously retrieved from this builder.
  template <class TyLocType> TyLocType push(QualType T) {
    TyLocType Loc = TypeLoc(T, nullptr).castAs<TyLocType>();
    size_t LocalSize = Loc.getLocalDataSize();
    unsigned LocalAlign = Loc.getLocalDataAlignment();
    return pushImpl2(T, LocalSize, LocalAlign).castAs<TyLocType>();
  }

  /// Creates a TypeSourceInfo for the given type.
  TypeSourceInfo *getTypeSourceInfo(ASTContext& Context, QualType T) {
#ifndef NDEBUG
    assert(T == LastTy && "type doesn't match last type pushed!");
#endif

    size_t FullDataSize = Capacity - Index;
    TypeSourceInfo *DI = Context.CreateTypeSourceInfo(T, FullDataSize);
    memcpy(DI->getTypeLoc().getOpaqueData(), &Buffer[Index], FullDataSize);
    return DI;
  }

  /// Copies the type-location information to the given AST context and
  /// returns a \c TypeLoc referring into the AST context.
  TypeLoc getTypeLocInContext(ASTContext &Context, QualType T) {
#ifndef NDEBUG
    assert(T == LastTy && "type doesn't match last type pushed!");
#endif

    size_t FullDataSize = Capacity - Index;
    void *Mem = Context.Allocate(FullDataSize);
    memcpy(Mem, &Buffer[Index], FullDataSize);
    return TypeLoc(T, Mem);
  }

private:

  TypeLoc pushImpl(QualType T, size_t LocalSize, unsigned LocalAlignment);

  /// Grow to the given capacity.
  void grow(size_t NewCapacity);

  /// Retrieve a temporary TypeLoc that refers into this \c TypeLocBuilder
  /// object.
  ///
  /// The resulting \c TypeLoc should only be used so long as the
  /// \c TypeLocBuilder is active and has not had more type information
  /// pushed into it.
  TypeLoc getTemporaryTypeLoc(QualType T) {
#ifndef NDEBUG
    assert(LastTy == T && "type doesn't match last type pushed!");
#endif
    return TypeLoc(T, &Buffer[Index]);
  }

  TypeLoc pushImpl2(QualType T, size_t LocalSize, unsigned LocalAlignment) {
  #ifndef NDEBUG
    QualType TLast = TypeLoc(T, nullptr).getNextTypeLoc().getType();
    assert(TLast == LastTy &&
          "mismatch between last type and new type's inner type");
    LastTy = T;
  #endif

    assert(LocalAlignment <= BufferMaxAlignment && "Unexpected alignment");

    // If we need to grow, grow by a factor of 2.
    if (LocalSize > Index) {
      size_t RequiredCapacity = Capacity + (LocalSize - Index);
      size_t NewCapacity = Capacity * 2;
      while (RequiredCapacity > NewCapacity)
        NewCapacity *= 2;
      grow(NewCapacity);
    }

    // Because we're adding elements to the TypeLoc backwards, we have to
    // do some extra work to keep everything aligned appropriately.
    // FIXME: This algorithm is a absolute mess because every TypeLoc returned
    // needs to be valid.  Partial TypeLocs are a terrible idea.
    // FIXME: 4 and 8 are sufficient at the moment, but it's pretty ugly to
    // hardcode them.
    if (LocalAlignment == 4) {
      if (NumBytesAtAlign8 == 0) {
        NumBytesAtAlign4 += LocalSize;
      } else {
        unsigned Padding = NumBytesAtAlign4 % 8;
        if (Padding == 0) {
          if (LocalSize % 8 == 0) {
            // Everything is set: there's no padding and we don't need to add
            // any.
          } else {
            assert(LocalSize % 8 == 4);
            // No existing padding; add in 4 bytes padding
            memmove(&Buffer[Index - 4], &Buffer[Index], NumBytesAtAlign4);
            Index -= 4;
          }
        } else {
          assert(Padding == 4);
          if (LocalSize % 8 == 0) {
            // Everything is set: there's 4 bytes padding and we don't need
            // to add any.
          } else {
            assert(LocalSize % 8 == 4);
            // There are 4 bytes padding, but we don't need any; remove it.
            memmove(&Buffer[Index + 4], &Buffer[Index], NumBytesAtAlign4);
            Index += 4;
          }
        }
        NumBytesAtAlign4 += LocalSize;
      }
    } else if (LocalAlignment == 8) {
      if (NumBytesAtAlign8 == 0) {
        // We have not seen any 8-byte aligned element yet. We insert a padding
        // only if the new Index is not 8-byte-aligned.
        if ((Index - LocalSize) % 8 != 0) {
          memmove(&Buffer[Index - 4], &Buffer[Index], NumBytesAtAlign4);
          Index -= 4;
        }
      } else {
        unsigned Padding = NumBytesAtAlign4 % 8;
        if (Padding == 0) {
          if (LocalSize % 8 == 0) {
            // Everything is set: there's no padding and we don't need to add
            // any.
          } else {
            assert(LocalSize % 8 == 4);
            // No existing padding; add in 4 bytes padding
            memmove(&Buffer[Index - 4], &Buffer[Index], NumBytesAtAlign4);
            Index -= 4;
          }
        } else {
          assert(Padding == 4);
          if (LocalSize % 8 == 0) {
            // Everything is set: there's 4 bytes padding and we don't need
            // to add any.
          } else {
            assert(LocalSize % 8 == 4);
            // There are 4 bytes padding, but we don't need any; remove it.
            memmove(&Buffer[Index + 4], &Buffer[Index], NumBytesAtAlign4);
            Index += 4;
          }
        }
      }

      // Forget about any padding.
      NumBytesAtAlign4 = 0;
      NumBytesAtAlign8 += LocalSize;
    } else {
      assert(LocalSize == 0);
    }

    Index -= LocalSize;

    assert(Capacity - Index == TypeLoc::getFullDataSizeForType(T) &&
          "incorrect data size provided to CreateTypeSourceInfo!");

    return getTemporaryTypeLoc(T);
  }
};

}

#endif