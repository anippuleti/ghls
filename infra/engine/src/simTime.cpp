#include "simTime.hpp"
#include <sstream>
#include <cmath>

namespace ghls {
double round2(double value) {
  return std::round(value * 100.0) / 100.0;
}
}

ghls::SimTime::SimTime() : c_simTime(round2(0.0)), c_simUnits(SimTimeUnit::ns) {}

ghls::SimTime::SimTime(double f_time, SimTimeUnit f_unit) {
  f_time = round2(f_time);
  switch (f_unit) {
    case SimTimeUnit::s:
      c_simTime = f_time * 1e9;
      break;
    case SimTimeUnit::ms:
      c_simTime = f_time * 1e6;
      break;
    case SimTimeUnit::us:
      c_simTime = f_time * 1e3;
      break;
    case SimTimeUnit::ns:
      c_simTime = f_time;
      break;
    case SimTimeUnit::ps:
      c_simTime = f_time / 1e3;
      break;
    default:
      c_simTime = f_time;
      break;
  }
  c_simUnits = SimTimeUnit::ns;
}

std::pair<double, ghls::SimTimeUnit> ghls::SimTime::simTime() const noexcept {
  return {c_simTime, c_simUnits};
}

ghls::SimTimeUnit ghls::SimTime::simTimeUnits() const noexcept {
  return c_simUnits;
}

double ghls::SimTime::simTimeInSec() const noexcept {
  return c_simTime / 1e9;
}

double ghls::SimTime::simTimeInMsec() const noexcept {
  return c_simTime / 1e6;
}

double ghls::SimTime::simTimeInUsec() const noexcept {
  return c_simTime / 1e3;
}

double ghls::SimTime::simTimeInNsec() const noexcept {
  return c_simTime;
}

double ghls::SimTime::simTimeInPsec() const noexcept {
  return c_simTime * 1e3;
}

ghls::SimTime ghls::SimTime::operator+(const SimTime& f_rhs) const
{
  SimTime result = *this;
  result.c_simTime += f_rhs.c_simTime;
  return result;
}

ghls::SimTime ghls::SimTime::operator*(uint64_t f_cycle) const
{
  SimTime result = *this;
  result.c_simTime *= static_cast<double>(f_cycle);
  return result;
}

std::string ghls::conv2str(SimTime f_time, SimTimeUnit f_unit) {
  auto l_timeValue = [] (SimTime f_time, SimTimeUnit f_unit) -> double {
      switch (f_unit) {
        case SimTimeUnit::s:
          return f_time.simTimeInSec();
        case SimTimeUnit::ms:
          return f_time.simTimeInMsec();
        case SimTimeUnit::us:
          return f_time.simTimeInUsec();
        case SimTimeUnit::ns:
          return f_time.simTimeInNsec();
        case SimTimeUnit::ps:
          return f_time.simTimeInPsec();
        default:
          return f_time.simTimeInNsec();
      }
  };
  auto l_unitStr = [](SimTimeUnit l_unit) -> std::string {
    switch (l_unit) {
      case SimTimeUnit::s:
        return "s";
      case SimTimeUnit::ms:
        return "ms";
      case SimTimeUnit::us:
        return "us";
      case SimTimeUnit::ns:
        return "ns";
      case SimTimeUnit::ps:
        return "ps";
      default:
        return "unknown";
    }
  };
  std::ostringstream l_stream;
  l_stream.precision(2);
  l_stream << std::fixed << round2(l_timeValue(f_time, f_unit));
  return l_stream.str() + " " + l_unitStr(f_unit);
}
