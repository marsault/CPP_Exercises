#include "../lib/Tracker.hpp"
#include "../src/StringInstancePair.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("La copy d'une StringInstancePair provoque la copie du tracker")
{
    {
        StringInstancePair p1 { "Test" };
        const auto&        i1 = p1.get_tracker();
        const auto&        s1 = p1.get_str();
        StringInstancePair p2 { p1 };
        const auto&        i2 = p2.get_tracker();
        const auto&        s2 = p2.get_str();

        REQUIRE(2 == Tracker::count());
        REQUIRE(1 == Tracker::copies());

        REQUIRE(s1 == s2);   // Les chaines dans p1 et p2 sont égales
        REQUIRE(&s1 != &s2); // ....mais stocké dans des endroits différentts

        REQUIRE(i1.id() == i2.id()); // L'instance dans p2 est bien une copie de i1.
        REQUIRE(&i1 != &i2);         // Les Tracker sont stockés dans des endroits différents.
    }

    // Toutes les instances construites ont été détruites.
    REQUIRE(Tracker::count() == 0);
}
