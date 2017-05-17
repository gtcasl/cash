#include <fstream>
#include "vcd.h"
#include "snodeimpl.h"

using namespace std;
using namespace cash_internal;

ch_vcdtracer::ch_vcdtracer(const std::string& filename, const std::initializer_list<const ch_device*>& devices) 
  : file_(filename)
  , ch_tracer(file_, devices) 
{}

void ch_vcdtracer::ensureInitialize() {
  // call parent ensureInitialize()
  ch_tracer::ensureInitialize();

  file_ << "$timescale 1 ns $end" << endl;
  for (auto& tap : taps_) {
    file_ << "$var reg " << tap.bus->get_size() << ' ' << tap.name << ' '
         << tap.name << " $end" << endl;
  }
  file_ << "$enddefinitions $end" << endl;
}

void ch_vcdtracer::tick(ch_cycle t) {
  // call default tick()
  ch_simulator::tick(t);
  
  // log net values
  file_ << '#' << t << endl;  
  for (auto& tap : taps_) {
    const snodeimpl& bus = *tap.bus;
    if (bus.get_size() > 1)
      file_ << 'b';
    for (int j = bus.get_size()-1; j >= 0; --j) {
      file_ << (bus[j] ? '1' : '0');
    }
    if (bus.get_size() > 1)
      file_ << ' ';
    file_ << tap.name << endl;
  }  
}
