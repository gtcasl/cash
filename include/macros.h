#pragma once

// macro primitives

#define CH_COMMA ,
#define CH_REM(...) __VA_ARGS__
#define CH_EAT(...)

#define CH_STRINGIZE_(x) #x
#define CH_STRINGIZE(x) CH_STRINGIZE_(x)

#define CH_CONCAT_(x, ...) x ## __VA_ARGS__
#define CH_CONCAT(x, ...) CH_CONCAT_(x, __VA_ARGS__)

// conditional macro

#define CH_IIF_0(x, y) y
#define CH_IIF_1(x, y) x
#define CH_IIF(c) CH_CONCAT(CH_IIF_, c)

#define CH_PAIR_FIRST(a, b) a
#define CH_PAIR_SECOND(a, b) b

// pair macros

#define CH_PAIR(x) CH_REM x
#define CH_PAIR_HEAD_(x, ...) CH_PAIR(x)
#define CH_PAIR_PROBE_(...) (__VA_ARGS__),
#define CH_PAIR_L_(...) CH_PAIR_HEAD_(__VA_ARGS__)
#define CH_PAIR_L(x) CH_PAIR_L_(CH_PAIR_PROBE_ x,)
#define CH_PAIR_R(x) CH_EAT x

// separator macros

#define CH_SEP_COMMA() ,
#define CH_SEP_SEMICOLON() ;
#define CH_SEP_PLUS() +
#define CH_SEP_OR() |
#define CH_SEP_COLON() :
#define CH_SEP_SPACE() /**/
#define CH_SEP_LESS() <
#define CH_SEP_GREATER() >

// MAKE_UNIQUE macro

#define CH_MAKE_UNIQUE(x) CH_CONCAT(x, __COUNTER__)

// increment macro

#define CH_INC(x) CH_INC_ ## x
#define CH_INC_0 1
#define CH_INC_1 2
#define CH_INC_2 3
#define CH_INC_3 4
#define CH_INC_4 5
#define CH_INC_5 6
#define CH_INC_6 7
#define CH_INC_7 8
#define CH_INC_8 9
#define CH_INC_9 10
#define CH_INC_10 11
#define CH_INC_11 12
#define CH_INC_12 13
#define CH_INC_13 14
#define CH_INC_14 15
#define CH_INC_15 16
#define CH_INC_16 17
#define CH_INC_17 18
#define CH_INC_18 19
#define CH_INC_19 20
#define CH_INC_20 21
#define CH_INC_21 22
#define CH_INC_22 23
#define CH_INC_23 24
#define CH_INC_24 25
#define CH_INC_25 26
#define CH_INC_26 27
#define CH_INC_27 28
#define CH_INC_28 29
#define CH_INC_29 30
#define CH_INC_30 31
#define CH_INC_31 32
#define CH_INC_32 33
#define CH_INC_33 34
#define CH_INC_34 35
#define CH_INC_35 36
#define CH_INC_36 37
#define CH_INC_37 38
#define CH_INC_38 39
#define CH_INC_39 40
#define CH_INC_40 41
#define CH_INC_41 42
#define CH_INC_42 43
#define CH_INC_43 44
#define CH_INC_44 45
#define CH_INC_45 46
#define CH_INC_46 47
#define CH_INC_47 48
#define CH_INC_48 49
#define CH_INC_49 50
#define CH_INC_50 51
#define CH_INC_51 52
#define CH_INC_52 53
#define CH_INC_53 54
#define CH_INC_54 55
#define CH_INC_55 56
#define CH_INC_56 57
#define CH_INC_57 58
#define CH_INC_58 59
#define CH_INC_59 60
#define CH_INC_60 61
#define CH_INC_61 62
#define CH_INC_62 63
#define CH_INC_63 64

// NARG macro

#define CH_NARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10,_11,_12,_13,_14,_15,_16, \
                  _17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32, \
                  _33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48, \
                  _49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63, N, ...) N
#define CH_NARG_R() 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48, \
                    47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32, \
                    31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16, \
                    15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CH_NARG_(...) CH_NARG_N(__VA_ARGS__) 
#define CH_NARG(...)  CH_NARG_(__VA_ARGS__, CH_NARG_R())

// FOR_EACH macro

#define CH_FOR_EACH_1(idx, func, arg, sep, ...)      func(arg, idx, __VA_ARGS__)
#define CH_FOR_EACH_2(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_1(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_3(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_2(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_4(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_3(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_5(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_4(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_6(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_5(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_7(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_6(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_8(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_7(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_9(idx, func, arg, sep, x, ...)   func(arg, idx, x) sep() CH_FOR_EACH_8(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_10(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_9(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_11(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_10(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_12(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_11(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_13(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_12(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_14(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_13(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_15(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_14(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_16(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_15(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_17(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_16(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_18(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_17(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_19(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_18(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_20(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_19(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_21(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_20(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_22(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_21(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_23(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_22(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_24(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_23(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_25(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_24(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_26(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_25(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_27(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_26(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_28(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_27(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_29(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_28(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_30(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_29(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_31(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_30(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_32(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_31(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_33(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_32(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_34(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_33(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_35(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_34(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_36(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_35(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_37(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_36(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_38(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_37(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_39(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_38(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_40(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_39(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_41(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_40(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_42(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_41(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_43(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_42(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_44(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_43(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_45(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_44(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_46(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_45(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_47(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_46(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_48(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_47(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_49(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_48(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_50(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_49(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_51(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_50(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_52(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_51(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_53(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_52(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_54(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_53(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_55(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_54(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_56(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_55(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_57(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_56(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_58(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_57(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_59(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_58(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_60(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_59(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_61(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_60(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_62(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_61(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_63(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_62(CH_INC(idx), func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH_64(idx, func, arg, sep, x, ...)  func(arg, idx, x) sep() CH_FOR_EACH_63(CH_INC(idx), func, arg, sep, __VA_ARGS__)

#define CH_FOR_EACH_(N, func, arg, sep, ...) CH_CONCAT(CH_FOR_EACH_, N)(0, func, arg, sep, __VA_ARGS__)
#define CH_FOR_EACH(func, arg, sep, ...) CH_FOR_EACH_(CH_NARG(__VA_ARGS__), func, arg, sep, __VA_ARGS__)

// REVERSE_FOR_EACH macro

#define CH_REVERSE_FOR_EACH_1(func, arg, sep, ...)      func(arg, 0, __VA_ARGS__)
#define CH_REVERSE_FOR_EACH_2(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_1(func, arg, sep, __VA_ARGS__) sep() func(arg, 1, x)
#define CH_REVERSE_FOR_EACH_3(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_2(func, arg, sep, __VA_ARGS__) sep() func(arg, 2, x)
#define CH_REVERSE_FOR_EACH_4(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_3(func, arg, sep, __VA_ARGS__) sep() func(arg, 3, x)
#define CH_REVERSE_FOR_EACH_5(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_4(func, arg, sep, __VA_ARGS__) sep() func(arg, 4, x)
#define CH_REVERSE_FOR_EACH_6(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_5(func, arg, sep, __VA_ARGS__) sep() func(arg, 5, x)
#define CH_REVERSE_FOR_EACH_7(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_6(func, arg, sep, __VA_ARGS__) sep() func(arg, 6, x)
#define CH_REVERSE_FOR_EACH_8(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_7(func, arg, sep, __VA_ARGS__) sep() func(arg, 7, x)
#define CH_REVERSE_FOR_EACH_9(func, arg, sep, x, ...)   CH_REVERSE_FOR_EACH_8(func, arg, sep, __VA_ARGS__) sep() func(arg, 8, x)
#define CH_REVERSE_FOR_EACH_10(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_9(func, arg, sep, __VA_ARGS__) sep() func(arg, 9, x)
#define CH_REVERSE_FOR_EACH_11(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_10(func, arg, sep, __VA_ARGS__) sep() func(arg, 10, x)
#define CH_REVERSE_FOR_EACH_12(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_11(func, arg, sep, __VA_ARGS__) sep() func(arg, 11, x)
#define CH_REVERSE_FOR_EACH_13(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_12(func, arg, sep, __VA_ARGS__) sep() func(arg, 12, x)
#define CH_REVERSE_FOR_EACH_14(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_13(func, arg, sep, __VA_ARGS__) sep() func(arg, 13, x)
#define CH_REVERSE_FOR_EACH_15(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_14(func, arg, sep, __VA_ARGS__) sep() func(arg, 14, x)
#define CH_REVERSE_FOR_EACH_16(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_15(func, arg, sep, __VA_ARGS__) sep() func(arg, 15, x)
#define CH_REVERSE_FOR_EACH_17(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_16(func, arg, sep, __VA_ARGS__) sep() func(arg, 16, x)
#define CH_REVERSE_FOR_EACH_18(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_17(func, arg, sep, __VA_ARGS__) sep() func(arg, 17, x)
#define CH_REVERSE_FOR_EACH_19(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_18(func, arg, sep, __VA_ARGS__) sep() func(arg, 18, x)
#define CH_REVERSE_FOR_EACH_20(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_19(func, arg, sep, __VA_ARGS__) sep() func(arg, 19, x)
#define CH_REVERSE_FOR_EACH_21(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_20(func, arg, sep, __VA_ARGS__) sep() func(arg, 20, x)
#define CH_REVERSE_FOR_EACH_22(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_21(func, arg, sep, __VA_ARGS__) sep() func(arg, 21, x)
#define CH_REVERSE_FOR_EACH_23(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_22(func, arg, sep, __VA_ARGS__) sep() func(arg, 22, x)
#define CH_REVERSE_FOR_EACH_24(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_23(func, arg, sep, __VA_ARGS__) sep() func(arg, 23, x)
#define CH_REVERSE_FOR_EACH_25(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_24(func, arg, sep, __VA_ARGS__) sep() func(arg, 24, x)
#define CH_REVERSE_FOR_EACH_26(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_25(func, arg, sep, __VA_ARGS__) sep() func(arg, 25, x)
#define CH_REVERSE_FOR_EACH_27(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_26(func, arg, sep, __VA_ARGS__) sep() func(arg, 26, x)
#define CH_REVERSE_FOR_EACH_28(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_27(func, arg, sep, __VA_ARGS__) sep() func(arg, 27, x)
#define CH_REVERSE_FOR_EACH_29(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_28(func, arg, sep, __VA_ARGS__) sep() func(arg, 28, x)
#define CH_REVERSE_FOR_EACH_30(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_29(func, arg, sep, __VA_ARGS__) sep() func(arg, 29, x)
#define CH_REVERSE_FOR_EACH_31(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_30(func, arg, sep, __VA_ARGS__) sep() func(arg, 30, x)
#define CH_REVERSE_FOR_EACH_32(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_31(func, arg, sep, __VA_ARGS__) sep() func(arg, 31, x)
#define CH_REVERSE_FOR_EACH_33(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_32(func, arg, sep, __VA_ARGS__) sep() func(arg, 32, x)
#define CH_REVERSE_FOR_EACH_34(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_33(func, arg, sep, __VA_ARGS__) sep() func(arg, 33, x)
#define CH_REVERSE_FOR_EACH_35(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_34(func, arg, sep, __VA_ARGS__) sep() func(arg, 34, x)
#define CH_REVERSE_FOR_EACH_36(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_35(func, arg, sep, __VA_ARGS__) sep() func(arg, 35, x)
#define CH_REVERSE_FOR_EACH_37(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_36(func, arg, sep, __VA_ARGS__) sep() func(arg, 36, x)
#define CH_REVERSE_FOR_EACH_38(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_37(func, arg, sep, __VA_ARGS__) sep() func(arg, 37, x)
#define CH_REVERSE_FOR_EACH_39(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_38(func, arg, sep, __VA_ARGS__) sep() func(arg, 38, x)
#define CH_REVERSE_FOR_EACH_40(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_39(func, arg, sep, __VA_ARGS__) sep() func(arg, 39, x)
#define CH_REVERSE_FOR_EACH_41(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_40(func, arg, sep, __VA_ARGS__) sep() func(arg, 40, x)
#define CH_REVERSE_FOR_EACH_42(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_41(func, arg, sep, __VA_ARGS__) sep() func(arg, 41, x)
#define CH_REVERSE_FOR_EACH_43(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_42(func, arg, sep, __VA_ARGS__) sep() func(arg, 42, x)
#define CH_REVERSE_FOR_EACH_44(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_43(func, arg, sep, __VA_ARGS__) sep() func(arg, 43, x)
#define CH_REVERSE_FOR_EACH_45(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_44(func, arg, sep, __VA_ARGS__) sep() func(arg, 44, x)
#define CH_REVERSE_FOR_EACH_46(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_45(func, arg, sep, __VA_ARGS__) sep() func(arg, 45, x)
#define CH_REVERSE_FOR_EACH_47(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_46(func, arg, sep, __VA_ARGS__) sep() func(arg, 46, x)
#define CH_REVERSE_FOR_EACH_48(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_47(func, arg, sep, __VA_ARGS__) sep() func(arg, 47, x)
#define CH_REVERSE_FOR_EACH_49(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_48(func, arg, sep, __VA_ARGS__) sep() func(arg, 48, x)
#define CH_REVERSE_FOR_EACH_50(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_49(func, arg, sep, __VA_ARGS__) sep() func(arg, 49, x)
#define CH_REVERSE_FOR_EACH_51(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_50(func, arg, sep, __VA_ARGS__) sep() func(arg, 50, x)
#define CH_REVERSE_FOR_EACH_52(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_51(func, arg, sep, __VA_ARGS__) sep() func(arg, 51, x)
#define CH_REVERSE_FOR_EACH_53(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_52(func, arg, sep, __VA_ARGS__) sep() func(arg, 52, x)
#define CH_REVERSE_FOR_EACH_54(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_53(func, arg, sep, __VA_ARGS__) sep() func(arg, 53, x)
#define CH_REVERSE_FOR_EACH_55(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_54(func, arg, sep, __VA_ARGS__) sep() func(arg, 54, x)
#define CH_REVERSE_FOR_EACH_56(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_55(func, arg, sep, __VA_ARGS__) sep() func(arg, 55, x)
#define CH_REVERSE_FOR_EACH_57(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_56(func, arg, sep, __VA_ARGS__) sep() func(arg, 56, x)
#define CH_REVERSE_FOR_EACH_58(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_57(func, arg, sep, __VA_ARGS__) sep() func(arg, 57, x)
#define CH_REVERSE_FOR_EACH_59(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_58(func, arg, sep, __VA_ARGS__) sep() func(arg, 58, x)
#define CH_REVERSE_FOR_EACH_60(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_59(func, arg, sep, __VA_ARGS__) sep() func(arg, 59, x)
#define CH_REVERSE_FOR_EACH_61(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_60(func, arg, sep, __VA_ARGS__) sep() func(arg, 60, x)
#define CH_REVERSE_FOR_EACH_62(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_61(func, arg, sep, __VA_ARGS__) sep() func(arg, 61, x)
#define CH_REVERSE_FOR_EACH_63(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_62(func, arg, sep, __VA_ARGS__) sep() func(arg, 62, x)
#define CH_REVERSE_FOR_EACH_64(func, arg, sep, x, ...)  CH_REVERSE_FOR_EACH_63(func, arg, sep, __VA_ARGS__) sep() func(arg, 63, x)

#define CH_REVERSE_FOR_EACH_(N, func, arg, sep, ...) CH_CONCAT(CH_REVERSE_FOR_EACH_, N)(func, arg, sep, __VA_ARGS__)
#define CH_REVERSE_FOR_EACH(func, arg, sep, ...) CH_REVERSE_FOR_EACH_(CH_NARG(__VA_ARGS__), func, arg, sep, __VA_ARGS__)

#define CH_FIRST_ARG_(N, ...) N
#define CH_FIRST_ARG(...) CH_FIRST_ARG_(__VA_ARGS__, ignore)

#define CH_VA_ARGS_MAP(x) x(0) \
                          x(0, 1) \
                          x(0, 1, 2) \
                          x(0, 1, 2, 3) \
                          x(0, 1, 2, 3, 4) \
                          x(0, 1, 2, 3, 4, 5) \
                          x(0, 1, 2, 3, 4, 5, 6 ) \
                          x(0, 1, 2, 3, 4, 5, 6, 7) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30) \
                          x(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
