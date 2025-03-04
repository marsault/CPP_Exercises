#include "../lib/Tracker.hpp"
#include "../src/StringInstancePair.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Il existe une classe StringInstancePair avec deux getters")
{
    StringInstancePair p { "Test" };
    REQUIRE(1 == Tracker::count());

    REQUIRE(p.get_str() == "Test");
    Tracker i = p.get_tracker();
}
