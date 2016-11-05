#include <fstream>
#include "vcd.h"
#include "snodeimpl.h"

using namespace std;
using namespace chdl_internal;

ch_vcdtracer::ch_vcdtracer(const std::string& filename, const std::initializer_list<const ch_device*>& devices) 
  : m_file(filename)
  , ch_tracer(m_file, devices) 
{}

void ch_vcdtracer::ensureInitialize() {
  // call parent ensureInitialize()
  ch_tracer::ensureInitialize();

  m_file << "$timescale 1 ns $end" << endl;
  for (auto& tap : m_taps) {
    m_file << "$var reg " << tap.bus->get_size() << ' ' << tap.name << ' '
         << tap.name << " $end" << endl;
  }
  m_file << "$enddefinitions $end" << endl;
}

void ch_vcdtracer::tick(ch_cycle t) {
  // call default tick()
  ch_simulator::tick(t);
  
  // log net values
  m_file << '#' << t << endl;  
  for (auto& tap : m_taps) {
    const snodeimpl& bus = *tap.bus;
    if (bus.get_size() > 1)
      m_file << 'b';
    for (int j = bus.get_size()-1; j >= 0; --j) {
      m_file << (bus[j] ? '1' : '0');
    }
    if (bus.get_size() > 1)
      m_file << ' ';
    m_file << tap.name << endl;
  }  
}
