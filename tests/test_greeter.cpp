#include "greeter.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Greeter greets correctly") {
    Greeter g;
    REQUIRE(g.greet("Alice") == "Hello, Alice!");
}
