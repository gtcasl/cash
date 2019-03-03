#pragma once

#include <cash.h>
#include <htl/decoupled.h>
#include <htl/mux.h>
#include <htl/enc.h>

namespace ch {
namespace htl {
namespace cache {

using namespace ch::logic;

template <unsigned CacheSize,
          unsigned BlockSize,
          unsigned NumWays,
          unsigned AddrBits,
          unsigned DataBits,
          unsigned WordBits>
struct Config {
  static_assert(ispow2(CacheSize), "invalid CacheSize");
  static_assert(ispow2(BlockSize), "invalid BlockSize");
  static_assert(BlockSize*(CacheSize/BlockSize) == CacheSize, "invalid BlockSize");
  static_assert(ispow2(NumWays) && (NumWays <= CacheSize/BlockSize), "invalid NumWays");
  static_assert(ispow2(DataBits) && (DataBits <= BlockSize*8), "invalid DataBits");
  static_assert(ispow2(WordBits) && (WordBits <= DataBits),  "invalid WordBits");

  static constexpr unsigned num_ways   = NumWays;
  static constexpr unsigned addr_bits  = AddrBits;
  static constexpr unsigned data_bits  = DataBits;
  static constexpr unsigned word_bits  = WordBits;

  static constexpr unsigned num_blocks  = CacheSize / BlockSize;
  static constexpr unsigned block_bits  = BlockSize * 8;
  static constexpr unsigned data_sel    = block_bits / data_bits;
  static constexpr unsigned word_sel    = data_bits / word_bits;
  static constexpr unsigned num_sets    = num_blocks / num_ways;
  static constexpr unsigned index_bits  = log2ceil(num_sets);
  static constexpr unsigned offset_bits = log2ceil(data_sel);
  static constexpr unsigned tag_bits    = addr_bits - index_bits - offset_bits;
  static constexpr unsigned maddr_bits  = addr_bits - offset_bits;

  __inout (cpu_req_io, (
    __in (ch_bit<addr_bits>)  address,
    __in (ch_bit<data_bits>)  writedata,
    __in (ch_bit<word_sel>)   worden,
    __in (ch_bool)            read,
    __in (ch_bool)            write,
    __out (ch_bit<data_bits>) readdata,
    __out (ch_bool)           readdatavalid,
    __out (ch_bool)           waitrequest
  ));

  __inout (mem_req_io, (
    __out (ch_bit<maddr_bits>) address,
    __out (ch_bit<block_bits>) writedata,
    __out (ch_bool)            read,
    __out (ch_bool)            write,
    __in (ch_bit<block_bits>)  readdata,
    __in (ch_bool)             readdatavalid,
    __in (ch_bool)             waitrequest
  ));
};

template <typename Cfg>
struct ReplacePLRU {
  __io (
    __in (ch_bit<Cfg::index_bits>) index,
    __in (ch_bool) update,
    __in (ch_bit<Cfg::num_ways>) h_way_idx,
    __out (ch_bit<log2ceil(Cfg::num_ways)>) victim_idx
  );

private:

  static constexpr unsigned use_bits = Cfg::num_ways - 1;
  using data_t = ch_bit<use_bits>;

  ch_bit<log2ceil(Cfg::num_ways)> get_replace_index(const data_t& state, unsigned tree_idx) {
    if (2 * tree_idx >= Cfg::num_ways) {
      return ch_sel(state[tree_idx], get_replace_index(state, tree_idx - 2), get_replace_index(state, tree_idx - 1));
    } else {
      int k = Cfg::num_ways - 2 * tree_idx - 1;
      return ch_sel<ch_bit<log2ceil(Cfg::num_ways)>>(state[tree_idx], k, k - 1);
    }
  }

  auto update_state(const ch_bit<Cfg::num_ways>& h_select, const data_t& state) {
    std::array<data_t, Cfg::num_ways> next_states;
    for (unsigned w = 0; w < Cfg::num_ways; ++w) {
      next_states[w] = state;
      int i = 1;
      for (int j = log2ceil(Cfg::num_ways) - 1; j >= 0; --j) {
        auto b = (w >> j) & 0x1;
        next_states[w][Cfg::num_ways - 1 - i] = !b;
        i = (i << 1) | b;
      }
    }
    return ch_hmux(h_select, next_states);
  }

public:

  void describe() {
    //--
    ch_mem<data_t, Cfg::num_sets> use_store(0); // zero initialized
    auto rstate = use_store.read(io.index);
    auto wstate = this->update_state(io.h_way_idx, rstate);
    use_store.write(io.index, wstate, io.update);

    //--
    io.victim_idx = this->get_replace_index(rstate, use_bits - 1);
  }
};

template <typename Cfg>
struct CacheWay {
  __io (
    __in (ch_bit<Cfg::index_bits>)  index,
    __in (ch_bit<Cfg::tag_bits>)    tag,
    __in (ch_bit<Cfg::block_bits>)  wr_data,
    __in (ch_bit<Cfg::data_sel>)    data_en,
    __in (ch_bit<Cfg::word_sel>)    word_en,
    __in (ch_bool)                  write,
    __in (ch_bool)                  readmiss,
    __out (ch_bit<Cfg::block_bits>) rd_data,
    __out (ch_bit<Cfg::maddr_bits>) wb_addr,
    __out (ch_bool)                 hit,
    __out (ch_bool)                 valid,
    __out (ch_bool)                 dirty
  );

  void describe() {
    //--
    static constexpr unsigned words_per_block = Cfg::block_bits / Cfg::word_bits;
    std::array<ch_mem<ch_bit<Cfg::word_bits>, Cfg::num_sets>, words_per_block> data_store;
    for (unsigned i = 0; i < words_per_block; ++i) {
      ch_asliceref<Cfg::word_bits>(io.rd_data, i) = data_store[i].read(io.index);
      auto wdata = ch_aslice<Cfg::word_bits>(io.wr_data, i);
      auto wenable = io.write && io.data_en[i / Cfg::word_sel] && io.word_en[i % Cfg::word_sel];
      data_store[i].write(io.index, wdata, wenable);
    }

    //--
    ch_mem<ch_bit<Cfg::tag_bits + 2>, Cfg::num_sets> tag_store(0); // zero initialized
    ch_bool valid, dirty;
    ch_bit<Cfg::tag_bits> tag;
    auto tag_wdata = ch_sel(io.readmiss, ch_cat(0_b, 1_b, io.tag), ch_cat(1_b, 1_b, tag));
    ch_bind(dirty, valid, tag) = tag_store.read(io.index);
    tag_store.write(io.index, tag_wdata, io.write);

    //--
    io.wb_addr = ch_cat(tag, io.index);
    io.hit   = valid && (tag == io.tag);
    io.valid = valid;
    io.dirty = dirty;
  }
};

template <typename Cfg>
struct Cache {
  __io (
    (typename Cfg::cpu_req_io) cpu,
    (typename Cfg::mem_req_io) mem
  );

  __enum (State, (idle, request, write, mfetch, mreply, writeback));

  void describe() {
    // declare output registers
    auto r_cpu_readdata  = io.cpu.readdata.as_reg();
    auto r_cpu_readdatavalid = io.cpu.readdatavalid.as_reg(false);
    auto r_mem_address   = io.mem.address.as_reg();
    auto r_mem_read      = io.mem.read.as_reg(false);
    auto r_mem_write     = io.mem.write.as_reg(false);
    auto r_mem_writedata = io.mem.writedata.as_reg();

    //--
    std::array<ch_module<CacheWay<Cfg>>, Cfg::num_ways> ways;
    ch_module<ReplacePLRU<Cfg>> plru;
    ch_reg<State> state(State::idle);
    std::array<ch_bit<Cfg::block_bits>, Cfg::num_ways> rd_data_set;
    std::array<ch_bit<Cfg::maddr_bits>, Cfg::num_ways> wb_addr_set;
    ch_bit<Cfg::num_ways> hit_set, valid_set, dirty_set;
    ch_reg<ch_bit<Cfg::addr_bits>> r_cpu_address;
    ch_reg<ch_bit<Cfg::data_bits>> r_cpu_writedata;
    ch_reg<ch_bit<Cfg::word_sel>> r_cpu_worden;
    ch_reg<ch_bool> r_cpu_write;
    ch_reg<ch_bit<Cfg::num_ways>> r_mem_write_set(false), r_cpu_write_set(false);

    //--
    auto cpu_address  = ch_sel(state == State::idle, io.cpu.address, r_cpu_address);
    auto offset       = ch_slice<Cfg::offset_bits>(cpu_address);
    auto index        = ch_slice<Cfg::index_bits>(cpu_address, Cfg::offset_bits);
    auto tag          = ch_slice<Cfg::tag_bits>(cpu_address, Cfg::offset_bits + Cfg::index_bits);
    auto cpu_writeblock= ch_dup<Cfg::data_sel>(r_cpu_writedata);
    auto is_mem_write = ch_orr(r_mem_write_set);
    auto write_data   = ch_sel(is_mem_write, io.mem.readdata, cpu_writeblock);    
    auto data_en_mem  = (1 << Cfg::data_sel) - 1;
    auto data_en      = ch_sel(is_mem_write, data_en_mem, (ch_bit<Cfg::data_sel>(1) << offset));
    auto word_en_mem  = (1 << Cfg::word_sel) - 1;
    auto word_en      = ch_sel(is_mem_write, word_en_mem, r_cpu_worden);

    // bind cache ways
    for (unsigned i = 0; i < Cfg::num_ways; ++i) {
      auto& way = ways[i];
      way.io.index   = index;
      way.io.tag     = tag;
      way.io.wr_data = write_data;
      way.io.data_en = data_en;
      way.io.word_en = word_en;
      way.io.write   = ch_sel(r_mem_write_set[i], io.mem.readdatavalid, r_cpu_write_set[i]);
      way.io.readmiss= ~r_cpu_write;

      rd_data_set[i] = way.io.rd_data;
      wb_addr_set[i] = way.io.wb_addr;
      hit_set[i]     = way.io.hit;
      valid_set[i]   = way.io.valid;
      dirty_set[i]   = way.io.dirty;
    }

    // bind replacement module
    plru.io.index      = index;
    plru.io.update     = (state == State::request);
    auto h_hit_idx     = ch_delay(hit_set);
    auto h_invalid_idx = ch_bit<Cfg::num_ways>(1) << ch_delay(ch_pri_enc(~valid_set));
    auto h_victim_idx  = ch_bit<Cfg::num_ways>(1) << ch_delay(plru.io.victim_idx);
    auto is_hit        = ch_orr(h_hit_idx);
    auto has_invalid   = ch_delay(~ch_andr(valid_set));
    auto is_dirty      = ch_orr(ch_delay(dirty_set) & h_victim_idx);
    __if (is_hit) {
      plru.io.h_way_idx = h_hit_idx;
    }__elif (has_invalid) {
      plru.io.h_way_idx = h_invalid_idx;
    }__else {
      plru.io.h_way_idx = h_victim_idx;
    };

    //--
    __switch (state)
    __case (State::idle) {
      r_cpu_readdatavalid->next = false;
      __if (io.cpu.read || io.cpu.write) {
        //--
        r_cpu_address->next   = io.cpu.address;
        r_cpu_writedata->next = io.cpu.writedata;
        r_cpu_worden->next    = io.cpu.worden;
        r_cpu_write->next     = io.cpu.write;
        //--
        state->next = State::request;
      };
    }
    __case (State::request) {
      __if (is_hit) {
        __if (r_cpu_write) {
          r_cpu_write_set->next = h_hit_idx;
          state->next = State::write;
        }__else {
          r_cpu_readdata->next = ch_mux(offset, ch_hmux(h_hit_idx, rd_data_set));
          r_cpu_readdatavalid->next = true;
          state->next = State::idle;
        };
      }__else {
        __if (has_invalid) {
          r_mem_address->next = ch_slice<Cfg::maddr_bits>(r_cpu_address, Cfg::offset_bits);
          r_mem_write_set->next = h_invalid_idx;
          r_mem_read->next = true;
          state->next = State::mfetch;
        }__elif (is_dirty) {
          r_mem_address->next   = ch_hmux(h_victim_idx, wb_addr_set);
          r_mem_writedata->next = ch_hmux(h_victim_idx, rd_data_set);
          r_mem_write_set->next = h_victim_idx;
          r_mem_write->next = true;
          state->next = State::writeback;
        }__else {
          r_mem_address->next = ch_slice<Cfg::maddr_bits>(r_cpu_address, Cfg::offset_bits);
          r_mem_write_set->next = h_victim_idx;
          r_mem_read->next = true;
          state->next = State::mfetch;
        };
      };
    }
    __case (State::write) {
      r_cpu_write_set->next = 0;
      state->next = State::idle;
    }
    __case (State::mfetch) {
      __if (!io.mem.waitrequest) {
        r_mem_read->next = false;
        state->next = State::mreply;
      };
    }
    __case (State::mreply) {
      __if (io.mem.readdatavalid) {
        __if (r_cpu_write) {
          r_cpu_write_set->next = r_mem_write_set;
          state->next = State::write;
        }__else {
          r_cpu_readdata->next = ch_mux(offset, io.mem.readdata);
          r_cpu_readdatavalid->next = true;
          state->next = State::idle;
        };
        r_mem_write_set->next = 0;
      };
    }
    __case (State::writeback) {
      __if (!io.mem.waitrequest) {
        r_mem_write->next = false;
        r_mem_address->next = ch_slice<Cfg::maddr_bits>(r_cpu_address, Cfg::offset_bits);
        r_mem_read->next = true;
        state->next = State::mfetch;
      };
    };

    //--
    io.cpu.waitrequest = (state != State::idle);

    /*__if (ch_clock()) {
      ch_println("{0}: state={}, is_hit={}, has_invalid={}, is_dirty={}, hit_idx={}, invalid_idx={}, victim_idx={}, index={}, tag={}, write_data={}, data_en={}, word_en={}, r_mem_write_set={}, mem_rvalid={}, mem_rdata={}, write_data={}, r_cpu_address={}",
               ch_now(), state, is_hit, has_invalid, is_dirty, hit_idx, invalid_idx, victim_idx, index, tag, write_data, data_en, word_en, r_mem_write_set, io.mem.readdatavalid, io.mem.readdata, write_data, r_cpu_address);
    };*/
  }
};

}
}
}
