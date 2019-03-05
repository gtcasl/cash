#include <htl/cache.h>
#include "common.h"

using namespace ch::htl::cache;

TEST_CASE("cache", "[cache]") {
  SECTION("basic", "[basic]") {
    TESTX([]()->bool {
      //  blocks=64, ways=4, sets=16
      using Cfg = Config<512, 8, 4, 20, 32, 8>;

      auto cpu_address = [&](uint32_t tag, uint32_t index, uint32_t offset)  {
        return offset | (index << Cfg::offset_bits) | (tag << (Cfg::offset_bits + Cfg::index_bits));
      };

      auto mem_address = [&](uint32_t tag, uint32_t index, uint32_t offset)  {
        return cpu_address(tag, index, offset) / Cfg::data_sel;
      };

      ch_device<Cache<Cfg>> cache;

      ch_toVerilog("cache.v", cache);

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
        /*std::cout << "t" << t
                  << ", cpu_rdata=" << cache.io.cpu.readdata
                  << ", cpu_rvalid=" << cache.io.cpu.readdatavalid
                  << ", cpu_wait=" << cache.io.cpu.waitrequest
                  << ": mem_addr=" << cache.io.mem.address
                  << ", mem_wdata=" << cache.io.mem.writedata
                  << ", mem_read=" << cache.io.mem.read
                  << ", mem_write=" << cache.io.mem.write
                  << std::endl;*/
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
          cache.io.cpu.address = cpu_address(1,1,0);
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
          assert(cache.io.mem.address == mem_address(1,1,0));
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
          cache.io.cpu.address = cpu_address(1,1,0);
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
          cache.io.cpu.address = cpu_address(1,1,0);
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
          cache.io.cpu.address = cpu_address(1,1,0);
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
          cache.io.cpu.address = cpu_address(2,1,0);
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
          assert(cache.io.mem.address == mem_address(2,1,0));
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
          cache.io.cpu.address = cpu_address(3,1,0);
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
          assert(cache.io.mem.address == mem_address(3,1,0));
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
          cache.io.cpu.address = cpu_address(4,1,0);
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
          assert(cache.io.mem.address == mem_address(4,1,0));
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
          cache.io.cpu.address = cpu_address(5,1,0);
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
          assert(cache.io.mem.address == mem_address(5,1,0));
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
          cache.io.cpu.address = cpu_address(6,1,0);
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
          assert(cache.io.mem.address == mem_address(6,1,0));
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

      tracer.toText("cache.log");
      tracer.toVCD("cache.vcd");
      tracer.toTestBench("cache_tb.v", "cache.v");
      int ret = system("iverilog cache_tb.v -o cache_tb.iv")
              | system("! vvp cache_tb.iv | grep 'ERROR' || false");
      return (0 == ret);
    });
  }
}
