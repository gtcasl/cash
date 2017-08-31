#include <fstream>
#include "vcd.h"
#include "snodeimpl.h"

using namespace cash::internal;

static std::string fixup_name(std::string name) {
  std::string ret(name);
  ret.erase(std::remove(ret.begin(), ret.end(), '['), ret.end());
  ret.erase(std::remove(ret.begin(), ret.end(), ']'), ret.end());
  return ret;
}

ch_vcdtracer::ch_vcdtracer(
    std::ostream& out,
    const std::initializer_list<const ch_device*>& devices)
  : ch_tracer(out, devices)
{}

void ch_vcdtracer::ensureInitialize() {
  // call parent ensureInitialize()
  ch_tracer::ensureInitialize();

  out_ << "$timescale 1 ns $end" << std::endl;
  for (auto& tap : taps_) {
    auto name = fixup_name(tap.name);
    out_ << "$var reg " << tap.bus.get_size() << ' ' << name << ' '
         << name << " $end" << std::endl;
  }
  out_ << "$enddefinitions $end" << std::endl;
}

void ch_vcdtracer::tick(ch_cycle t) {
  // call default tick()
  ch_simulator::tick(t);
  
  // log net values
  out_ << '#' << t << std::endl;
  for (auto& tap : taps_) {
    const snode& bus = tap.bus;
    if (bus.get_size() > 1)
      out_ << 'b';
    for (int j = bus.get_size()-1; j >= 0; --j) {
      out_ << (bus[j] ? '1' : '0');
    }
    if (bus.get_size() > 1)
      out_ << ' ';
    // remove [] from tap name
    out_ << fixup_name(tap.name) << std::endl;
  }  
}
