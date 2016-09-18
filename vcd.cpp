#include <fstream>
#include "vcd.h"
#include "busimpl.h"

using namespace std;
using namespace chdl_internal;

ch_vcdtracer::ch_vcdtracer(const std::string& filename) : m_file(filename) {}

ch_vcdtracer::~ch_vcdtracer() {
  this->close();
}

void ch_vcdtracer::ensureInitialize() {
  if (m_initialized)
    return;

  // call default ensureInitialize()
  ch_simulator::ensureInitialize();

  m_file << "$timescale 1 ns $end" << endl;
  for (auto& tap : m_taps) {
    m_file << "$var reg " << tap.bus->get_size() << ' ' << tap.name << ' '
         << tap.name << " $end" << endl;
  }
  m_file << "$enddefinitions $end" << endl;

  m_initialized = true;
}

void ch_vcdtracer::tick(ch_cycle t) {
  // call default tick()
  ch_simulator::tick(t);
  
  // log net values
  m_file << '#' << t << endl;  
  for (auto& tap : m_taps) {
    const busimpl& bus = *tap.bus;
    if (bus.get_size() > 1)
      m_file << 'b';
    for (int j = bus.get_size()-1; j >= 0; --j) {
      m_file << (bus.get_bit(j) ? '1' : '0');
    }
    if (bus.get_size() > 1)
      m_file << ' ';
    m_file << tap.name << endl;
  }  
}

void ch_vcdtracer::close() {
  m_file.close();
}
