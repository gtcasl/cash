#include "vcdtracerimpl.h"
#include "vcdtracer.h"
#include <fstream>
#include "snodeimpl.h"

using namespace cash::internal;

static std::string fixup_name(std::string name) {
  std::string ret(name);
  ret.erase(std::remove(ret.begin(), ret.end(), '['), ret.end());
  ret.erase(std::remove(ret.begin(), ret.end(), ']'), ret.end());
  return ret;
}

void vcdtracerimpl::ensureInitialize() {
  // call parent ensureInitialize()
  tracerimpl::ensureInitialize();

  out_ << "$timescale 1 ns $end" << std::endl;
  for (auto& tap : taps_) {
    auto name = fixup_name(tap.name);
    out_ << "$var reg " << tap.bus.get_size() << ' ' << name << ' '
         << name << " $end" << std::endl;
  }
  out_ << "$enddefinitions $end" << std::endl;
}

void vcdtracerimpl::tick(ch_tick t) {
  // call default tick()
  simulatorimpl::tick(t);
  
  // log tap values
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

///////////////////////////////////////////////////////////////////////////////

ch_vcdtracer::ch_vcdtracer(std::ostream& out,
                           const std::initializer_list<const ch_device*>& devices)
  : ch_tracer(new vcdtracerimpl(out, devices))
{}

ch_vcdtracer::~ch_vcdtracer() {}
