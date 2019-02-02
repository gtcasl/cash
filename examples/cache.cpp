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
    auto wstate = this->update_state(io.way_idx, rstate);
    use_store.write(io.set_idx, wstate, io.update);

    __if (io.update) {
      ch_print("*** PLRU: way_idx={}, rstate={}, wstate={}", io.way_idx, rstate, wstate);
    };

    //--
    auto tree_root = use_bits - 1;
    io.victim_idx = this->get_replace_index(rstate, tree_root);
  }

  ch_bit<log2ceil(Cfg::num_ways)> get_replace_index(const data_t& state, unsigned index) {
    if (2 * index >= Cfg::num_ways) {
      return ch_sel(state[index], get_replace_index(state, index - 2), get_replace_index(state, index - 1));
    } else {
      int k = Cfg::num_ways - 2 * index - 1;
      return ch_sel<ch_bit<log2ceil(Cfg::num_ways)>>(state[index], k, k - 1);
    }
  }

  auto update_state(const ch_bit<Cfg::num_ways>& select, const data_t& state) {
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
    __in (ch_bool)                  readmiss,
    __out (ch_bit<Cfg::block_bits>) rd_data,
    __out (ch_bit<Cfg::maddr_bits>) wb_addr,
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
      ch_asliceref<Cfg::word_bits>(io.rd_data, i) = data_store[i].read(io.index);
      auto wdata = ch_aslice<Cfg::word_bits>(io.wr_data, i);
      auto wenable = io.write && io.data_en[i / Cfg::word_sel] && io.word_en[i % Cfg::word_sel];
      //__if (wenable) {
      //  ch_print(stringf("*** Way: b%d : rd_data={}, wdata={}, wenable={}", i), io.rd_data, wdata, wenable);
      //};
      data_store[i].write(io.index, wdata, wenable);
    }

    //--
    auto tag_wdata = ch_sel(io.readmiss, ch_cat(0_b, 1_b, io.tag), ch_cat(1_b, 1_b, tag));
    ch_bind(dirty, valid, tag) = tag_store.read(io.index);
    tag_store.write(io.index, tag_wdata, io.write);

    //__if (io.write) {
    //  ch_print("*** WagTag: wdata={}, write={}", tag_wdata, io.write);
    //};

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
    auto r_cpu_readdata = io.cpu.readdata.as_reg();
    auto r_cpu_readdatavalid = io.cpu.readdatavalid.as_reg(false);
    auto r_mem_address = io.mem.address.as_reg();
    auto r_mem_read  = io.mem.read.as_reg(false);
    auto r_mem_write = io.mem.write.as_reg(false);
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
    auto cpu_address= ch_sel(state == State::idle, io.cpu.address, r_cpu_address);
    auto index        = ch_slice<Cfg::index_bits>(cpu_address, Cfg::offset_bits);
    auto tag          = ch_slice<Cfg::tag_bits>(cpu_address, Cfg::offset_bits + Cfg::index_bits);
    auto cpu_writeblock= ch_dup<Cfg::data_sel>(r_cpu_writedata);
    auto is_mem_write = ch_orr(r_mem_write_set);
    auto write_data   = ch_sel(is_mem_write, io.mem.readdata, cpu_writeblock);
    auto data_en_cpu  = ch_slice<Cfg::offset_bits>(cpu_address);
    auto data_en_mem  = (1 << Cfg::data_sel) - 1;
    auto data_en      = ch_sel(is_mem_write, data_en_mem, (ch_bit<Cfg::data_sel>(1) << data_en_cpu));
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
    plru.io.set_idx  = index;
    plru.io.update   = (state == State::request);
    auto hit_idx     = ch_delay(hit_set);
    auto invalid_idx = ch_bit<Cfg::num_ways>(1) << ch_delay(ch_pri_enc(~valid_set));
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
          r_cpu_write_set->next = hit_idx;
          state->next = State::write;
        }__else {
          r_cpu_readdata->next = ch_mux(data_en_cpu, ch_hmux(hit_idx, rd_data_set));
          r_cpu_readdatavalid->next = true;
          state->next = State::idle;
        };
      }__else {
        __if (has_invalid) {
          r_mem_address->next = ch_slice<Cfg::maddr_bits>(r_cpu_address, Cfg::offset_bits);
          r_mem_write_set->next = invalid_idx;
          r_mem_read->next = true;
          state->next = State::mfetch;
        }__elif (is_dirty) {
          r_mem_address->next   = ch_hmux(victim_idx, wb_addr_set);
          r_mem_writedata->next = ch_hmux(victim_idx, rd_data_set);
          r_mem_write_set->next = victim_idx;
          r_mem_write->next = true;
          state->next = State::writeback;
        }__else {
          r_mem_address->next = ch_slice<Cfg::maddr_bits>(r_cpu_address, Cfg::offset_bits);
          r_mem_write_set->next = victim_idx;
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
          r_cpu_readdata->next = ch_mux(data_en_cpu, io.mem.readdata);
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

    __if (ch_clock()) {
      ch_print("{0}: state={}, is_hit={}, has_invalid={}, is_dirty={}, hit_idx={}, invalid_idx={}, victim_idx={}, index={}, tag={}, write_data={}, data_en={}, word_en={}, r_mem_write_set={}, mem_rvalid={}, mem_rdata={}, write_data={}, r_cpu_address={}",
               ch_now(), state, is_hit, has_invalid, is_dirty, hit_idx, invalid_idx, victim_idx, index, tag, write_data, data_en, word_en, r_mem_write_set, io.mem.readdatavalid, io.mem.readdata, write_data, r_cpu_address);
    };
  }
};

/*template <typename Cfg>
class processor {
  int step_;

  void read(int step, int addr, int value) {

  }

  void write(int step, int addr, int value) {

  }

public:
  processor() : step_(0) {}

  void eval(ch_device<Cache<Cfg>>* cache, ch_tick t) {
    this->read();
  }
};

template <typename Cfg>
class memory {
public:
  void eval(ch_device<Cache<Cfg>>* cache, ch_tick t) {
    //--
  }
};*/

int main() {
  using Cfg = CacheConfig<64, 64, 4, 20, 32, 8>;

  ch_device<Cache<Cfg>> cache;
  ch_tracer tracer(cache);

  cache.io.cpu.address = 0;
  cache.io.cpu.writedata = 0;
  cache.io.cpu.worden = 0;
  cache.io.cpu.read = false;
  cache.io.cpu.write = false;
  cache.io.mem.readdata = 0;
  cache.io.mem.readdatavalid = false;
  cache.io.mem.waitrequest = true;

  tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t             
              << ", cpu_rdata=" << cache.io.cpu.readdata
              << ", cpu_rvalid=" << cache.io.cpu.readdatavalid
              << ", cpu_wait=" << cache.io.cpu.waitrequest
              << ": mem_addr=" << cache.io.mem.address
              << ", mem_wdata=" << cache.io.mem.writedata
              << ", mem_read=" << cache.io.mem.read
              << ", mem_write=" << cache.io.mem.write
              << std::endl;
    switch (t) {
    case 0:
      assert(cache.io.cpu.readdatavalid == false);
      assert(cache.io.cpu.waitrequest == false);
      assert(cache.io.mem.read == false);
      assert(cache.io.mem.write == false);
      break;

    // read miss

    case 2:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 4;
      cache.io.cpu.worden = 0xf;
      cache.io.cpu.read = true;
      break;

    case 4:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.read = false;
      break;

    case 6:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == 2);
      break;

    case 8:
      cache.io.mem.waitrequest = false;
      break;

    case 10:
      cache.io.mem.waitrequest = true;
      break;

    case 12:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 256;
      cache.io.mem.readdatavalid = true;
      break;

    case 14:
      assert(cache.io.cpu.readdatavalid == true);
      assert(cache.io.cpu.readdata == 256);
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;

    // read hit

    case 16:
      cache.io.cpu.address = 4;
      cache.io.cpu.worden = 0xf;
      cache.io.cpu.read = true;
      break;

    case 18:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.read = false;
      break;

    case 20:
      assert(cache.io.cpu.readdatavalid == true);
      assert(cache.io.cpu.readdata == 256);
      break;

    // write hit

    case 22:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 4;
      cache.io.cpu.worden = 0x1;
      cache.io.cpu.writedata = 16;
      cache.io.cpu.write = true;
      break;

    case 24:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.write = false;
      break;

    case 26:
      break;

    // read hit

    case 28:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 4;
      cache.io.cpu.worden = 0xf;
      cache.io.cpu.read = true;
      break;

    case 30:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.read = false;
      break;

    case 32:
      assert(cache.io.cpu.readdatavalid == true);
      assert(cache.io.cpu.readdata == 272);
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.read = false;
      break;

    // write miss

    case 34:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 2 * Cfg::num_sets + 4;;
      cache.io.cpu.worden = 0x1;
      cache.io.cpu.writedata = 16;
      cache.io.cpu.write = true;
      break;

    case 36:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.write = false;
      break;

    case 38:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == (2 * Cfg::num_sets + 4)/2);
      break;

    case 40:
      cache.io.mem.waitrequest = false;
      break;

    case 42:
      cache.io.mem.waitrequest = true;
      break;

    case 44:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 64;
      cache.io.mem.readdatavalid = true;
      break;

    case 46:
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;

    // read miss

    case 48:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 4 * Cfg::num_sets + 4;
      cache.io.cpu.worden = 0xf;
      cache.io.cpu.read = true;
      break;

    case 50:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.read = false;
      break;

    case 52:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == (4 * Cfg::num_sets + 4)/2);
      break;

    case 54:
      cache.io.mem.waitrequest = false;
      break;

    case 56:
      cache.io.mem.waitrequest = true;
      break;

    case 58:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 128;
      cache.io.mem.readdatavalid = true;
      break;

    case 60:
      assert(cache.io.cpu.readdatavalid == true);
      assert(cache.io.cpu.readdata == 128);
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;

    // write miss

    case 62:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 8 * Cfg::num_sets + 4;
      cache.io.cpu.worden = 0x1;
      cache.io.cpu.writedata = 16;
      cache.io.cpu.write = true;
      break;

    case 64:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.write = false;
      break;

    case 66:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == (8 * Cfg::num_sets + 4)/2);
      break;

    case 68:
      cache.io.mem.waitrequest = false;
      break;

    case 70:
      cache.io.mem.waitrequest = true;
      break;

    case 72:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 512;
      cache.io.mem.readdatavalid = true;
      break;

    case 80:
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;

    // write miss with writeback

    case 82:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 16 * Cfg::num_sets + 4;
      cache.io.cpu.worden = 0x1;
      cache.io.cpu.writedata = 16;
      cache.io.cpu.write = true;
      break;

    case 84:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.write = false;
      break;

    case 86:
      assert(cache.io.mem.write == true);
      assert(cache.io.mem.address == 2);
      assert(cache.io.mem.writedata == 272);
      cache.io.mem.waitrequest = false;
      break;

    case 88:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == (16 * Cfg::num_sets + 4)/2);
      cache.io.mem.waitrequest = true;
      break;

    case 90:
      cache.io.mem.waitrequest = false;
      break;

    case 92:
      cache.io.mem.waitrequest = true;
      break;

    case 94:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 1024;
      cache.io.mem.readdatavalid = true;
      break;

    case 96:
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;

    // write miss with no writeback

    case 98:
      assert(cache.io.cpu.waitrequest == false);
      cache.io.cpu.address = 32 * Cfg::num_sets + 4;
      cache.io.cpu.worden = 0x1;
      cache.io.cpu.writedata = 16;
      cache.io.cpu.write = true;
      break;

    case 100:
      cache.io.cpu.address = 0;
      cache.io.cpu.worden = 0;
      cache.io.cpu.write = false;
      break;

    case 102:
      assert(cache.io.mem.read == true);
      assert(cache.io.mem.address == (32 * Cfg::num_sets + 4)/2);
      break;

    case 104:
      cache.io.mem.waitrequest = false;
      break;

    case 106:
      cache.io.mem.waitrequest = true;
      break;

    case 108:
      assert(cache.io.mem.read == false);
      cache.io.mem.readdata = 2048;
      cache.io.mem.readdatavalid = true;
      break;

    case 110:
      cache.io.mem.readdata = 0;
      cache.io.mem.readdatavalid = false;
      break;
    }

    return (t <= 114);
  });

  ch_toVerilog("cache.v", cache);

  tracer.toText("cache.log");
  tracer.toVCD("cache.vcd");
  tracer.toTestBench("cache_tb.v", "cache.v");
  int ret = system("iverilog cache_tb.v -o cache_tb.iv")
          | system("! vvp cache_tb.iv | grep 'ERROR' || false");
  return ret != 0;
}
