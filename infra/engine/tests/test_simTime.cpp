#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../src/simTime.hpp"

using namespace ghls;

TEST_CASE("SimTime default constructor initializes to zero") {
  SimTime t;
  auto [l_val, l_unit] = t.simTime();
  REQUIRE(l_val == 0.0);
  REQUIRE(l_unit == SimTimeUnit::ns);
}

TEST_CASE("SimTime conversions for all units") {
  struct TestCase {
    double value;
    SimTimeUnit unit;
    double expectedSec, expectedMsec, expectedUsec, expectedNsec, expectedPsec;
  };

  std::vector<TestCase> cases = {
    {1.0, SimTimeUnit::s,    1.0,    1e3,    1e6,    1e9,    1e12},
    {1.0, SimTimeUnit::ms,   1e-3,   1.0,    1e3,    1e6,    1e9},
    {1.0, SimTimeUnit::us,   1e-6,   1e-3,   1.0,    1e3,    1e6},
    {1.0, SimTimeUnit::ns,   1e-9,   1e-6,   1e-3,   1.0,    1e3},
    {1.0, SimTimeUnit::ps,   1e-12,  1e-9,   1e-6,   1e-3,   1.0},
    {2.5, SimTimeUnit::s,    2.5,    2.5e3,  2.5e6,  2.5e9,  2.5e12},
    {0.5, SimTimeUnit::ms,   0.5e-3, 0.5,    0.5e3,  0.5e6,  0.5e9},
    {100, SimTimeUnit::us,   100e-6, 100e-3, 100.0,  100e3,  100e6},
    {1000, SimTimeUnit::ns,  1000e-9,1000e-6,1000e-3,1000.0, 1000e3},
    {1e6, SimTimeUnit::ps,   1e-6,   1e-3,   1.0,    1e3,    1e6}
  };

  for (const auto& l_case : cases) {
    SimTime l_t(l_case.value, l_case.unit);
    CAPTURE(l_case.value, l_case.unit);
    REQUIRE(l_t.simTimeInSec() == Catch::Approx(l_case.expectedSec));
    REQUIRE(l_t.simTimeInMsec() == Catch::Approx(l_case.expectedMsec));
    REQUIRE(l_t.simTimeInUsec() == Catch::Approx(l_case.expectedUsec));
    REQUIRE(l_t.simTimeInNsec() == Catch::Approx(l_case.expectedNsec));
    REQUIRE(l_t.simTimeInPsec() == Catch::Approx(l_case.expectedPsec));
  }
}

TEST_CASE("conv2str produces correct string") {
  SimTime l_t(1.5, SimTimeUnit::ms);
  REQUIRE(conv2str(l_t, ghls::SimTimeUnit::ms) == "1.50 ms");
  SimTime l_t2(2.0, SimTimeUnit::us);
  REQUIRE(conv2str(l_t2, ghls::SimTimeUnit::us) == "2.00 us");
  SimTime l_t3(0.000123, SimTimeUnit::s);
  REQUIRE(conv2str(l_t3, ghls::SimTimeUnit::s) == "0.00 s");
}

TEST_CASE("SimTime operator+ exhaustive tests") {
  SECTION("Same units addition") {
    SECTION("seconds + seconds") {
      SimTime t1(1.0, SimTimeUnit::s);
      SimTime t2(2.0, SimTimeUnit::s);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(3.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(3e9));
    }

    SECTION("milliseconds + milliseconds") {
      SimTime t1(100.0, SimTimeUnit::ms);
      SimTime t2(50.0, SimTimeUnit::ms);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(150.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(150e6));
    }

    SECTION("microseconds + microseconds") {
      SimTime t1(1000.0, SimTimeUnit::us);
      SimTime t2(500.0, SimTimeUnit::us);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(1500.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1500e3));
    }

    SECTION("nanoseconds + nanoseconds") {
      SimTime t1(1e6, SimTimeUnit::ns);
      SimTime t2(5e5, SimTimeUnit::ns);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1.5e6));
    }

    SECTION("picoseconds + picoseconds") {
      SimTime t1(1e9, SimTimeUnit::ps);
      SimTime t2(5e8, SimTimeUnit::ps);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInPsec() == Catch::Approx(1.5e9));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1.5e6));
    }
  }

  SECTION("Mixed units addition") {
    SECTION("seconds + milliseconds") {
      SimTime t1(1.0, SimTimeUnit::s);
      SimTime t2(500.0, SimTimeUnit::ms);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.5));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1.5e9));
    }

    SECTION("milliseconds + microseconds") {
      SimTime t1(10.0, SimTimeUnit::ms);
      SimTime t2(500.0, SimTimeUnit::us);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(10.5));
      REQUIRE(result.simTimeInUsec() == Catch::Approx(10500.0));
    }

    SECTION("microseconds + nanoseconds") {
      SimTime t1(100.0, SimTimeUnit::us);
      SimTime t2(50000.0, SimTimeUnit::ns);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(150.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(150000.0));
    }

    SECTION("nanoseconds + picoseconds") {
      SimTime t1(1000.0, SimTimeUnit::ns);
      SimTime t2(500000.0, SimTimeUnit::ps);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1500.0));
      REQUIRE(result.simTimeInPsec() == Catch::Approx(1500000.0));
    }

    SECTION("seconds + nanoseconds") {
      SimTime t1(1.0, SimTimeUnit::s);
      SimTime t2(123456789.0, SimTimeUnit::ns);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.123456789));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1123456789.0));
    }

    SECTION("picoseconds + seconds") {
      SimTime t1(1e12, SimTimeUnit::ps);
      SimTime t2(1.0, SimTimeUnit::s);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(2.0));
      REQUIRE(result.simTimeInPsec() == Catch::Approx(2e12));
    }

    SECTION("milliseconds + picoseconds") {
      SimTime t1(5.0, SimTimeUnit::ms);
      SimTime t2(1e9, SimTimeUnit::ps);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(6.0));
    }
  }

  SECTION("Zero value additions") {
    SECTION("zero + non-zero") {
      SimTime t1(0.0, SimTimeUnit::ns);
      SimTime t2(100.0, SimTimeUnit::ms);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(100.0));
    }

    SECTION("non-zero + zero") {
      SimTime t1(50.0, SimTimeUnit::us);
      SimTime t2(0.0, SimTimeUnit::s);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(50.0));
    }

    SECTION("zero + zero") {
      SimTime t1(0.0, SimTimeUnit::ns);
      SimTime t2(0.0, SimTimeUnit::ms);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(0.0));
    }
  }

  SECTION("Fractional values") {
    SECTION("fractional seconds") {
      SimTime t1(1.5, SimTimeUnit::s);
      SimTime t2(0.25, SimTimeUnit::s);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.75));
    }

    SECTION("fractional milliseconds") {
      SimTime t1(2.75, SimTimeUnit::ms);
      SimTime t2(1.25, SimTimeUnit::ms);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(4.0));
    }

    SECTION("fractional mixed units") {
      SimTime t1(1.5, SimTimeUnit::ms);
      SimTime t2(250.5, SimTimeUnit::us);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(1.7505));
      REQUIRE(result.simTimeInUsec() == Catch::Approx(1750.5));
    }
  }

  SECTION("Large values") {
    SECTION("large nanoseconds") {
      SimTime t1(1e9, SimTimeUnit::ns);
      SimTime t2(5e8, SimTimeUnit::ns);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1.5e9));
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.5));
    }

    SECTION("large picoseconds") {
      SimTime t1(1e12, SimTimeUnit::ps);
      SimTime t2(5e11, SimTimeUnit::ps);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInPsec() == Catch::Approx(1.5e12));
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.5));
    }
  }

  SECTION("Very small values") {
    SECTION("small picoseconds") {
      SimTime t1(1.0, SimTimeUnit::ps);
      SimTime t2(0.5, SimTimeUnit::ps);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInPsec() == Catch::Approx(1.5));
    }

    SECTION("small nanoseconds") {
      SimTime t1(0.01, SimTimeUnit::ns);
      SimTime t2(0.01, SimTimeUnit::ns);
      SimTime result = t1 + t2;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(0.02));
    }
  }

  SECTION("Chained operator+") {
    SimTime t1(100.0, SimTimeUnit::ns);
    SimTime t2(200.0, SimTimeUnit::ns);
    SimTime t3(300.0, SimTimeUnit::ns);
    SimTime result = t1 + t2 + t3;
    REQUIRE(result.simTimeInNsec() == Catch::Approx(600.0));
  }

  SECTION("Self-addition") {
    SimTime t1(50.0, SimTimeUnit::us);
    SimTime result = t1 + t1;
    REQUIRE(result.simTimeInUsec() == Catch::Approx(100.0));
  }

  SECTION("All unit combinations") {
    struct TestCase {
      double lhs_value;
      SimTimeUnit lhs_unit;
      double rhs_value;
      SimTimeUnit rhs_unit;
      double expected_ns;
    };

    std::vector<TestCase> cases = {
      // s combinations
      {1.0, SimTimeUnit::s, 1.0, SimTimeUnit::s, 2e9},
      {1.0, SimTimeUnit::s, 1.0, SimTimeUnit::ms, 1.001e9},
      {1.0, SimTimeUnit::s, 1.0, SimTimeUnit::us, 1.000001e9},
      {1.0, SimTimeUnit::s, 1.0, SimTimeUnit::ns, 1e9 + 1.0},
      {1.0, SimTimeUnit::s, 1000.0, SimTimeUnit::ps, 1e9 + 1.0},
      // ms combinations
      {1.0, SimTimeUnit::ms, 1.0, SimTimeUnit::s, 1.001e9},
      {1.0, SimTimeUnit::ms, 1.0, SimTimeUnit::ms, 2e6},
      {1.0, SimTimeUnit::ms, 1.0, SimTimeUnit::us, 1.001e6},
      {1.0, SimTimeUnit::ms, 1.0, SimTimeUnit::ns, 1e6 + 1.0},
      {1.0, SimTimeUnit::ms, 1000.0, SimTimeUnit::ps, 1e6 + 1.0},
      // us combinations
      {1.0, SimTimeUnit::us, 1.0, SimTimeUnit::s, 1.000001e9},
      {1.0, SimTimeUnit::us, 1.0, SimTimeUnit::ms, 1.001e6},
      {1.0, SimTimeUnit::us, 1.0, SimTimeUnit::us, 2e3},
      {1.0, SimTimeUnit::us, 1.0, SimTimeUnit::ns, 1e3 + 1.0},
      {1.0, SimTimeUnit::us, 1000.0, SimTimeUnit::ps, 1e3 + 1.0},
      // ns combinations
      {1.0, SimTimeUnit::ns, 1.0, SimTimeUnit::s, 1e9 + 1.0},
      {1.0, SimTimeUnit::ns, 1.0, SimTimeUnit::ms, 1e6 + 1.0},
      {1.0, SimTimeUnit::ns, 1.0, SimTimeUnit::us, 1e3 + 1.0},
      {1.0, SimTimeUnit::ns, 1.0, SimTimeUnit::ns, 2.0},
      {1.0, SimTimeUnit::ns, 1000.0, SimTimeUnit::ps, 2.0},
      // ps combinations
      {1000.0, SimTimeUnit::ps, 1.0, SimTimeUnit::s, 1e9 + 1.0},
      {1000.0, SimTimeUnit::ps, 1.0, SimTimeUnit::ms, 1e6 + 1.0},
      {1000.0, SimTimeUnit::ps, 1.0, SimTimeUnit::us, 1e3 + 1.0},
      {1000.0, SimTimeUnit::ps, 1.0, SimTimeUnit::ns, 2.0},
      {1.0, SimTimeUnit::ps, 1.0, SimTimeUnit::ps, 0.002},
    };

    for (const auto& tc : cases) {
      SimTime lhs(tc.lhs_value, tc.lhs_unit);
      SimTime rhs(tc.rhs_value, tc.rhs_unit);
      SimTime result = lhs + rhs;
      CAPTURE(tc.lhs_value, tc.lhs_unit, tc.rhs_value, tc.rhs_unit);
      REQUIRE(result.simTimeInNsec() == Catch::Approx(tc.expected_ns));
    }
  }
}

TEST_CASE("SimTime operator* exhaustive tests") {
  SECTION("Multiplication with different units") {
    SECTION("seconds * scalar") {
      SimTime t1(2.0, SimTimeUnit::s);
      SimTime result = t1 * 3;
      REQUIRE(result.simTimeInSec() == Catch::Approx(6.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(6e9));
    }

    SECTION("milliseconds * scalar") {
      SimTime t1(10.0, SimTimeUnit::ms);
      SimTime result = t1 * 5;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(50.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(50e6));
    }

    SECTION("microseconds * scalar") {
      SimTime t1(100.0, SimTimeUnit::us);
      SimTime result = t1 * 10;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(1000.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1000e3));
    }

    SECTION("nanoseconds * scalar") {
      SimTime t1(1000.0, SimTimeUnit::ns);
      SimTime result = t1 * 7;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(7000.0));
    }

    SECTION("picoseconds * scalar") {
      SimTime t1(500.0, SimTimeUnit::ps);
      SimTime result = t1 * 4;
      REQUIRE(result.simTimeInPsec() == Catch::Approx(2000.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(2.0));
    }
  }

  SECTION("Multiplication with zero") {
    SECTION("zero time * non-zero scalar") {
      SimTime t1(0.0, SimTimeUnit::ns);
      SimTime result = t1 * 100;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(0.0));
    }

    SECTION("non-zero time * zero scalar") {
      SimTime t1(100.0, SimTimeUnit::ms);
      SimTime result = t1 * 0;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(0.0));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(0.0));
    }

    SECTION("zero time * zero scalar") {
      SimTime t1(0.0, SimTimeUnit::us);
      SimTime result = t1 * 0;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(0.0));
    }
  }

  SECTION("Multiplication with one") {
    SECTION("time * 1") {
      SimTime t1(123.45, SimTimeUnit::ms);
      SimTime result = t1 * 1;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(123.45));
      REQUIRE(result.simTimeInNsec() == Catch::Approx(123.45e6));
    }
  }

  SECTION("Large scalar multiplications") {
    SECTION("nanoseconds * large scalar") {
      SimTime t1(1.0, SimTimeUnit::ns);
      SimTime result = t1 * 1000000;
      REQUIRE(result.simTimeInNsec() == Catch::Approx(1e6));
      REQUIRE(result.simTimeInMsec() == Catch::Approx(1.0));
    }

    SECTION("microseconds * large scalar") {
      SimTime t1(1.0, SimTimeUnit::us);
      SimTime result = t1 * 1000;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(1000.0));
      REQUIRE(result.simTimeInMsec() == Catch::Approx(1.0));
    }

    SECTION("milliseconds * large scalar") {
      SimTime t1(1.0, SimTimeUnit::ms);
      SimTime result = t1 * 1000;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(1000.0));
      REQUIRE(result.simTimeInSec() == Catch::Approx(1.0));
    }
  }

  SECTION("Fractional time values") {
    SECTION("fractional seconds * scalar") {
      SimTime t1(1.5, SimTimeUnit::s);
      SimTime result = t1 * 2;
      REQUIRE(result.simTimeInSec() == Catch::Approx(3.0));
    }

    SECTION("fractional milliseconds * scalar") {
      SimTime t1(2.75, SimTimeUnit::ms);
      SimTime result = t1 * 4;
      REQUIRE(result.simTimeInMsec() == Catch::Approx(11.0));
    }

    SECTION("fractional microseconds * scalar") {
      SimTime t1(0.5, SimTimeUnit::us);
      SimTime result = t1 * 10;
      REQUIRE(result.simTimeInUsec() == Catch::Approx(5.0));
    }
  }

  SECTION("Chained operator*") {
    SimTime t1(10.0, SimTimeUnit::ns);
    SimTime result = t1 * 2 * 3 * 5;
    REQUIRE(result.simTimeInNsec() == Catch::Approx(300.0));
  }

  SECTION("Mixed operations with operator+") {
    SimTime t1(10.0, SimTimeUnit::us);
    SimTime t2(5.0, SimTimeUnit::us);
    SimTime result = (t1 * 2) + (t2 * 3);
    REQUIRE(result.simTimeInUsec() == Catch::Approx(35.0));
  }

  SECTION("All units with various scalars") {
    struct TestCase {
      double time_value;
      SimTimeUnit unit;
      uint64_t scalar;
      double expected_ns;
    };

    std::vector<TestCase> cases = {
      // Seconds
      {1.0, SimTimeUnit::s, 1, 1e9},
      {1.0, SimTimeUnit::s, 2, 2e9},
      {0.5, SimTimeUnit::s, 10, 5e9},
      {2.5, SimTimeUnit::s, 4, 10e9},
      // Milliseconds
      {1.0, SimTimeUnit::ms, 1, 1e6},
      {10.0, SimTimeUnit::ms, 5, 50e6},
      {0.5, SimTimeUnit::ms, 100, 50e6},
      {2.5, SimTimeUnit::ms, 8, 20e6},
      // Microseconds
      {1.0, SimTimeUnit::us, 1, 1e3},
      {100.0, SimTimeUnit::us, 10, 1e6},
      {0.5, SimTimeUnit::us, 1000, 500e3},
      {2.5, SimTimeUnit::us, 40, 100e3},
      // Nanoseconds
      {1.0, SimTimeUnit::ns, 1, 1.0},
      {1000.0, SimTimeUnit::ns, 5, 5000.0},
      {0.5, SimTimeUnit::ns, 100, 50.0},
      {2.5, SimTimeUnit::ns, 400, 1000.0},
      // Picoseconds
      {1.0, SimTimeUnit::ps, 1, 0.001},
      {1000.0, SimTimeUnit::ps, 10, 10.0},
      {500.0, SimTimeUnit::ps, 20, 10.0},
      {2.5, SimTimeUnit::ps, 4000, 10.0},
      // Edge cases with larger base values
      {1.0, SimTimeUnit::s, 1000, 1000e9},
      {1.0, SimTimeUnit::ps, 1000000, 1000.0},
      {1.0, SimTimeUnit::ms, 1000000, 1000000e6},
    };

    for (const auto& tc : cases) {
      SimTime t(tc.time_value, tc.unit);
      SimTime result = t * tc.scalar;
      CAPTURE(tc.time_value, tc.unit, tc.scalar);
      REQUIRE(result.simTimeInNsec() == Catch::Approx(tc.expected_ns));
    }
  }

  SECTION("Maximum uint64_t value handling") {
    SECTION("small time * max uint64_t") {
      SimTime t1(1.0, SimTimeUnit::ps);
      uint64_t max_val = UINT64_MAX;
      SimTime result = t1 * max_val;
      // Result should be approximately max_val / 1000 nanoseconds
      REQUIRE(result.simTimeInPsec() == Catch::Approx(static_cast<double>(max_val)));
    }
  }

  SECTION("Verify original time unchanged") {
    SimTime t1(10.0, SimTimeUnit::ms);
    SimTime result = t1 * 5;
    REQUIRE(t1.simTimeInMsec() == Catch::Approx(10.0));
    REQUIRE(result.simTimeInMsec() == Catch::Approx(50.0));
  }
}
