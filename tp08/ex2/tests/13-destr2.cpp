#include "../lib/Tracker.hpp"
#include "../src/StringInstancePair.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("La destruction d'une StringInstancePair provoque une destruction de tous les Tracker "
          "construits.")
{
    {
        StringInstancePair p1 { "Test" };
        StringInstancePair p2 = std::move(p1);
    }
    REQUIRE(0 == Tracker::count());
}
