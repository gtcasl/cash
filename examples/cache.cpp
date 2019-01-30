#include <cash.h>
#include <htl/decoupled.h>
#include <htl/mux.h>
#include <htl/enc.h>

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;
using namespace ch::htl;

template <unsigned NumBlocks,
          unsigned BlockBits,
          unsigned NumWays,
          unsigned AddrBits,
          unsigned DataBits,
          unsigned WordBits>
struct CacheConfig {
  static_assert(ispow2(NumBlocks), "invalid NumBlocks");
  static_assert(ispow2(BlockBits), "invalid BlockBits");
  static_assert(ispow2(NumWays) && (NumWays <= NumBlocks),   "invalid NumWays");
  static_assert(ispow2(DataBits) && (DataBits <= BlockBits), "invalid DataBits");
  static_assert(ispow2(WordBits) && (WordBits <= DataBits),  "invalid WordBits");

  static constexpr unsigned num_blocks = NumBlocks;
  static constexpr unsigned block_bits = BlockBits;
  static constexpr unsigned num_ways   = NumWays;
  static constexpr unsigned addr_bits  = AddrBits;
  static constexpr unsigned data_bits  = DataBits;
  static constexpr unsigned word_bits  = WordBits;

  static constexpr unsigned data_sel    = block_bits / data_bits;
  static constexpr unsigned word_sel    = data_bits / word_bits;
  static constexpr unsigned num_sets    = num_blocks / num_ways;  
  static constexpr unsigned index_bits  = log2ceil(num_sets);
  static constexpr unsigned offset_bits = log2ceil(data_sel);
  static constexpr unsigned tag_bits    = addr_bits - index_bits - offset_bits;
  static constexpr unsigned baddr_bits  = addr_bits - offset_bits;  

  __inout (cpu_req_io, (
    __in (ch_bit<addr_bits>)  address,
    __in (ch_bit<data_bits>)  writedata,
    __in (ch_bit<word_sel>)   word_en,
    __in (ch_bool)            read,
    __in (ch_bool)            write,
    __out (ch_bit<data_bits>) readdata,
    __out (ch_bool)           readdatavalid,
    __out (ch_bool)           waitrequest
  ));

  __inout (mem_req_io, (
    __out (ch_bit<addr_bits>)  address,
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
    __in (ch_bit<Cfg::index_bits>) set_idx,
    __in (ch_bool) update,
    __in (ch_bit<Cfg::num_ways>) way_idx,
    __out (ch_bit<log2ceil(Cfg::num_ways)>) victim_idx
  );

  static constexpr unsigned use_bits = Cfg::num_ways - 1;
  using data_t = ch_bit<use_bits>;

  void describe() {
    // allocate use-bit store
    ch_mem<data_t, Cfg::num_sets> use_store(0); // zero initialized

    //--
    auto rstate = use_store.read(io.set_idx);
    auto wstate = ch_delay(this->update_state(io.way_idx, rstate));
    use_store.write(io.set_idx, wstate, io.update);

    //--
    io.victim_idx = this->get_replace_index(rstate, Cfg::num_ways - 2);
  }

  ch_bit<log2ceil(Cfg::num_ways)> get_replace_index(const data_t& state, unsigned index) {
    if (2 * index > Cfg::num_ways) {
      return ch_sel(state[index], get_replace_index(state, index - 2), get_replace_index(state, index - 1));
    } else {
      int k = Cfg::num_ways - 2 * index - 1;
      return ch_sel<ch_bit<log2ceil(Cfg::num_ways)>>(state[index], k, k - 1);
    }
  }

  auto update_state(const ch_bit<Cfg::num_ways>& select, const data_t& state) {
    std::array<data_t, Cfg::num_ways> next_states;
    for (unsigned w = 0; w < Cfg::num_ways; ++w) {
      auto next_state = state.clone();
      int i = 1;
      for (int j = log2ceil(Cfg::num_ways) - 1; j >= 0; --j) {
        auto b = (w >> j) & 0x1;
        next_state[Cfg::num_ways - 1 - i] = !b;
        i = (i << 1) | b;
      }
      next_states[w] = next_state;
    }
    return ch_hmux(select, next_states);
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
    __in (ch_bool)                  invalidate,
    __out (ch_bit<Cfg::block_bits>) rd_data,
    __out (ch_bit<Cfg::baddr_bits>) wb_addr,
    __out (ch_bool)                 hit,
    __out (ch_bool)                 valid,
    __out (ch_bool)                 dirty
  );

  void describe() {
    static constexpr unsigned tag_bits = Cfg::tag_bits + 2; // valid + dirty
    static constexpr unsigned words_per_block = Cfg::block_bits / Cfg::word_bits;

    //--
    std::array<ch_mem<ch_bit<Cfg::word_bits>, Cfg::num_sets>, words_per_block> data_store;
    ch_mem<ch_bit<tag_bits>, Cfg::num_sets> tag_store(0); // zero initialized
    ch_bool valid, dirty;
    ch_bit<Cfg::tag_bits> tag;

    //--
    for (unsigned i = 0; i < words_per_block; ++i) {
      ch_sliceref<Cfg::word_bits>(io.rd_data, i * Cfg::word_bits) = data_store[i].read(io.index);
      auto wdata = ch_slice<Cfg::word_bits>(io.wr_data, i * Cfg::word_bits);
      auto wenable = io.write && io.data_en[i / Cfg::word_sel] && io.word_en[i % Cfg::word_sel];
      data_store[i].write(io.index, wdata, wenable);
    }

    //--
    auto tag_wdata = ch_sel(io.invalidate, ch_cat(0_b, 1_b, io.tag), ch_cat(1_b, 1_b, tag));
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

  __enum (State, (idle, request, fetch, update, writeback));

  void describe() {
    // declare output registers
    auto cpu_readdata = io.cpu.readdata.as_reg();
    auto cpu_readdatavalid = io.cpu.readdatavalid.as_reg(false);
    auto mem_address = io.mem.address.as_reg();
    auto mem_read  = io.mem.read.as_reg(false);
    auto mem_write = io.mem.write.as_reg(false);
    auto mem_writedata = io.mem.writedata.as_reg();

    //--
    std::array<ch_module<CacheWay<Cfg>>, Cfg::num_ways> ways;
    ch_module<ReplacePLRU<Cfg>> plru;
    ch_reg<State> state(State::idle);
    std::array<ch_bit<Cfg::block_bits>, Cfg::num_ways> rd_data;
    ch_bit<Cfg::num_ways> hit_set, valid_set, dirty_set;
    ch_reg<ch_bit<Cfg::num_ways>> r_mem_write_set(false), r_cpu_write_set(false);

    //--
    auto index        = ch_slice<Cfg::index_bits>(io.cpu.address, Cfg::offset_bits);
    auto tag          = ch_slice<Cfg::tag_bits>(io.cpu.address, Cfg::offset_bits + Cfg::index_bits);
    auto cpu_writedata= ch_dup<Cfg::data_sel>(io.cpu.writedata);
    auto is_mem_write = ch_orr(r_mem_write_set);
    auto write_data   = ch_sel(is_mem_write, io.mem.readdata, cpu_writedata);
    auto data_en_cpu  = ch_slice<Cfg::offset_bits>(io.cpu.address);
    auto data_en_mem  = (1 << Cfg::offset_bits) - 1;
    auto data_en      = ch_bit<Cfg::data_sel>(1) << ch_sel(is_mem_write, data_en_mem, data_en_cpu);
    auto word_en_mem  = (1 << Cfg::word_sel) - 1;
    auto word_en      = ch_sel(is_mem_write, word_en_mem, io.cpu.word_en);

    // bind cache ways
    for (unsigned i = 0; i < Cfg::num_ways; ++i) {
      auto& way = ways[i];
      way.io.index   = index;
      way.io.tag     = tag;
      way.io.wr_data = write_data;
      way.io.data_en = data_en;
      way.io.word_en = word_en;
      way.io.write   = ch_sel(r_mem_write_set[i], io.mem.readdatavalid, r_cpu_write_set[i]);

      rd_data[i]   = way.io.rd_data;
      hit_set[i]   = way.io.hit;
      valid_set[i] = way.io.valid;
      dirty_set[i] = way.io.dirty;
    }

    // bind replacement module
    plru.io.set_idx = index;
    plru.io.update  = (state == State::request);
    auto hit_idx     = ch_delay(hit_set);
    auto invalid_idx = ch_delay(this->to_invalid_index(valid_set));
    auto victim_idx  = ch_bit<Cfg::num_ways>(1) << ch_delay(plru.io.victim_idx);
    auto is_hit      = ch_orr(hit_idx);
    auto has_invalid = ch_delay(~ch_andr(valid_set));
    auto is_dirty    = ch_orr(ch_delay(dirty_set) & victim_idx);

    __if (is_hit) {
      plru.io.way_idx = hit_idx;
    }__elif (has_invalid) {
      plru.io.way_idx = invalid_idx;
    }__else {
      plru.io.way_idx = victim_idx;
    };

    //--
    __switch (state)
    __case (State::idle) {
      __if (io.cpu.read || io.cpu.write) {
        state->next = State::request;
      };
    }
    __case (State::request) {
      __if (is_hit && io.cpu.read) {
        cpu_readdata->next = ch_mux(data_en_cpu, ch_hmux(hit_idx, rd_data));
        cpu_readdatavalid->next = true;
        state->next = State::idle;
      }__elif (is_hit && io.cpu.write) {
        r_cpu_write_set->next = hit_idx;
      }__else {
        __if (!io.mem.waitrequest) {
          __if (has_invalid) {
            mem_address->next = 0;
            mem_read->next = true;
            state->next = State::fetch;
          }__elif (is_dirty) {
            mem_address->next = 0;
            mem_writedata->next = 0;
            mem_write->next = true;
            state->next = State::writeback;
          }__else {
            mem_address->next = 0;
            mem_write->next = false;
            state->next = State::fetch;
          };
        };
      };
    }
    __case (State::fetch) {
      //--
    }
    __case (State::update) {
      //--
    }
    __case (State::writeback) {
      //--
    };

    //--
    io.cpu.waitrequest = (state != State::idle);
  }

  auto to_invalid_index(const ch_bit<Cfg::num_ways>& valid_set) {
    return ch_bit<Cfg::num_ways>(1) << ch_pri_enc(~valid_set);
  }
};

int main() {
  using Cfg = CacheConfig<64, 512, 8, 20, 32, 8>;
  ch_device<Cache<Cfg>> cache;

  //ch_tracer tracer(cache);
  //tracer.run();

  //std::cout << "result:" << std::endl;
  //std::cout << "cout = " << cache.io.cout << std::endl;
  //std::cout << "out = "  << cache.io.out << std::endl;

  //assert(cache.io.out == 1);
  //assert(cache.io.cout == 1);

  //ch_toVerilog("cache.v", cache);
  //ch_toFIRRTL("cache.fir", cache);

  //tracer.toText("cache.log");
  //tracer.toVCD("cache.vcd");
  //tracer.toTestBench("cache_tb.v", "cache.v");
  //int ret = system("iverilog cache_tb.v -o cache_tb.iv")
  //        | system("! vvp cache_tb.iv | grep 'ERROR' || false");
  //return ret != 0;
  return 0;
}
