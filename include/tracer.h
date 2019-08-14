#pragma once

#include "simulator.h"

namespace ch {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  ch_tracer() {}

  ch_tracer(const std::vector<device_base>& devices);

  template <typename... Devices>
  ch_tracer(const device_base& first, const Devices&... more)
    : ch_tracer(std::vector<device_base>{first, (more)...})
  {}

  ch_tracer(const ch_tracer& other);

  ch_tracer(ch_tracer&& other);

  ~ch_tracer();

  ch_tracer& operator=(const ch_tracer& other);

  ch_tracer& operator=(ch_tracer&& other);

  void toText(std::ofstream& out);

  void toText(const std::string& file) {
    std::ofstream out(file);
    toText(out);
  }

  void toVCD(std::ofstream& out);

  void toVCD(const std::string& file) {
    std::ofstream out(file);
    toVCD(out);
  }

  void toTestBench(std::ofstream& out,
                   const std::string& moduleFileName,
                   bool passthru = false);

  void toTestBench(const std::string& file,
                   const std::string& moduleFileName,
                   bool passthru = false) {
    std::ofstream out(file);
    toTestBench(out, moduleFileName, passthru);
  }

  void toVerilator(std::ofstream& out,
                   const std::string& moduleTypeName);

  void toVerilator(const std::string& file,
                   const std::string& moduleTypeName) {
    std::ofstream out(file);
    toVerilator(out, moduleTypeName);
  }

  void toSystemC(std::ofstream& out,
                   const std::string& moduleTypeName);

  void toSystemC(const std::string& file,
                   const std::string& moduleTypeName) {
    std::ofstream out(file);
    toSystemC(out, moduleTypeName);
  }

protected:

  ch_tracer(simulatorimpl* impl);
};

}
}

