#include "../lib/Tracker.hpp"
#include "../src/StringInstancePair.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("La destruction d'une StringInstancePair provoque la destruction du Tracker")
{
    {
        StringInstancePair p { "Test" };

        REQUIRE(p.get_str() == "Test");
        const auto& i = p.get_tracker();

        REQUIRE(1 == Tracker::count());
    }

    REQUIRE(0 == Tracker::count());
}
