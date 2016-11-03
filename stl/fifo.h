#pragma once

#include "bitv.h"

namespace chdl {

namespace stl {

template <unsigned ADDR, unsigned WIDTH>
CHDL_OUT(ch_bit<WIDTH>, ch_logic, ch_logic) ch_fifo(
  const ch_bit<WIDTH>& din,
  const ch_logic& push,
  const ch_logic& pop) {
  
  ch_bit<WIDTH> dout;
  ch_logic empty;
  ch_logic full;
  
  ch_mem<WIDTH, ADDR> mem;
  ch_bit<ADDR+1> rd_ptr, wr_ptr;
  ch_bit<ADDR> rd_addr(ch_slice<ADDR>(rd_ptr));
  ch_bit<ADDR> wr_addr(ch_slice<ADDR>(wr_ptr));

  ch_logic reading(pop && !empty);
  ch_logic writing(push && (!full || pop));  
  
  rd_ptr = ch_reg(ch_select(reading, rd_ptr + 1, rd_ptr));
  wr_ptr = ch_reg(ch_select(writing, wr_ptr + 1, wr_ptr));
  
  empty = (wr_ptr == rd_ptr);
  full  = (wr_addr == rd_addr) && (wr_ptr[ADDR] != rd_ptr[ADDR]);
  dout  = mem.read(rd_addr);
  mem.write(wr_addr, din, writing);
  
  CHDL_RET(dout, empty, full);
}

}
}
