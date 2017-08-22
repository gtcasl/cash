#include <fstream>
#include "vcd.h"
#include "snodeimpl.h"

using namespace std;
using namespace cash::detail;

ch_vcdtracer::ch_vcdtracer(
    std::ostream& out,
    const std::initializer_list<const ch_device*>& devices)
  : ch_tracer(out, devices)
{}

void ch_vcdtracer::ensureInitialize() {
  // call parent ensureInitialize()
  ch_tracer::ensureInitialize();

  out_ << "$timescale 1 ns $end" << endl;
  for (auto& tap : taps_) {
    out_ << "$var reg " << tap.bus.get_size() << ' ' << tap.name << ' '
         << tap.name << " $end" << endl;
  }
  out_ << "$enddefinitions $end" << endl;
}

void ch_vcdtracer::tick(ch_cycle t) {
  // call default tick()
  ch_simulator::tick(t);
  
  // log net values
  out_ << '#' << t << endl;
  for (auto& tap : taps_) {
    const snode& bus = tap.bus;
    if (bus.get_size() > 1)
      out_ << 'b';
    for (int j = bus.get_size()-1; j >= 0; --j) {
      out_ << (bus[j] ? '1' : '0');
    }
    if (bus.get_size() > 1)
      out_ << ' ';
    out_ << tap.name << endl;
  }  
}
