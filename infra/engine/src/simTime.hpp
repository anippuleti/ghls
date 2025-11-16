
#pragma once
#include <utility>
#include <string>

namespace ghls {

// Definition of time units used in simulation
// seconds, milliseconds, microseconds, nanoseconds, picoseconds
enum class SimTimeUnit { s, ms, us, ns, ps };

class SimTime {
 public:
  SimTime();
  SimTime(double f_time, SimTimeUnit f_unit);

  SimTime operator+(const SimTime& f_rhs) const;
  SimTime operator*(uint64_t f_cycle) const;

  std::pair<double, SimTimeUnit> simTime() const noexcept;
  SimTimeUnit simTimeUnits() const noexcept;
  double simTimeInSec() const noexcept;
  double simTimeInMsec() const noexcept;
  double simTimeInUsec() const noexcept;
  double simTimeInNsec() const noexcept;
  double simTimeInPsec() const noexcept;
 private:
  double c_simTime;
  SimTimeUnit c_simUnits;
};

std::string conv2str(SimTime f_time, SimTimeUnit f_unit = SimTimeUnit::ns);

}  // namespace ghls
