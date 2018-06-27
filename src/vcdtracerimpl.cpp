#include "vcdtracerimpl.h"
#include "vcdtracer.h"
#include "ioimpl.h"
#include <fstream>

using namespace ch::internal;

static std::string fixup_name(std::string name) {
  std::string ret(name);
  ret.erase(std::remove(ret.begin(), ret.end(), '['), ret.end());
  ret.erase(std::remove(ret.begin(), ret.end(), ']'), ret.end());
  return ret;
}

vcdtracerimpl::vcdtracerimpl(std::ostream& out, const ch_device_list& devices)
  : tracerimpl(out, devices) {
  // initialize
  this->initialize();
}

vcdtracerimpl::vcdtracerimpl(const std::string& file, const ch_device_list& devices)
  : tracerimpl(file, devices) {
  // initialize
  this->initialize();
}

void vcdtracerimpl::initialize() {
  out_ << "$timescale 1 ns $end" << std::endl;
  for (auto& tap : io_traces_) {
    auto name = fixup_name(tap.name);
    out_ << "$var reg " << tap.node->size() << ' ' << name << ' '
         << name << " $end" << std::endl;
  }
  out_ << "$enddefinitions $end" << std::endl;
}

void vcdtracerimpl::eval(ch_tick t) {
  // call default tick()
  simulatorimpl::eval(t);
  
  // log tap values
  out_ << '#' << t << std::endl;
  for (auto& trace : io_traces_) {
    if (trace.node->size() > 1)
      out_ << 'b';
    for (int j = trace.node->size()-1; j >= 0; --j) {
      out_ << (trace.node->value()[j] ? '1' : '0');
    }
    if (trace.node->size() > 1)
      out_ << ' ';
    // remove [] from tap name
    out_ << fixup_name(trace.name) << std::endl;
  }

  for (auto& trace : sc_traces_) {
    out_ << trace.name << " = " << trace.node->data() << std::endl;

    if (trace.node->size() > 1)
      out_ << 'b';
    for (int j = trace.node->size()-1; j >= 0; --j) {
      out_ << (trace.node->data()[j] ? '1' : '0');
    }
    if (trace.node->size() > 1)
      out_ << ' ';
    // remove [] from tap name
    out_ << fixup_name(trace.name) << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////


ch_vcdtracer::ch_vcdtracer(std::ostream& out,
                           const ch_device_list& devices)
  : ch_tracer(new vcdtracerimpl(out, devices))
{}

ch_vcdtracer::ch_vcdtracer(const std::string& file,
                           const ch_device_list& devices)
  : ch_tracer(new vcdtracerimpl(file, devices))
{}

ch_vcdtracer::ch_vcdtracer(const ch_vcdtracer& tracer) : ch_tracer(tracer) {}

ch_vcdtracer::ch_vcdtracer(ch_vcdtracer&& tracer) : ch_tracer(std::move(tracer)) {}

ch_vcdtracer::~ch_vcdtracer() {}

ch_vcdtracer& ch_vcdtracer::operator=(const ch_vcdtracer& tracer) {
  ch_tracer::operator=(tracer);
  return *this;
}

ch_vcdtracer& ch_vcdtracer::operator=(ch_vcdtracer&& tracer) {
  ch_tracer::operator=(std::move(tracer));
  return *this;
}
