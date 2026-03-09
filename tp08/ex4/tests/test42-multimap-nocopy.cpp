#include "../lib/Tracker.hpp"
#include "../src/MultiMap.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Modifier la classe `MultiMap` de façon à éviter les copies.")
{
  {
    MultiMap multimap;

    auto i0 = multimap.add("Céline", 1);

    multimap.add("Céline", 2);
    REQUIRE(multimap._map1.count("Céline") == 3); // 1+2 = 3 !

    REQUIRE(Tracker::copies() == 0); // Aucune copie n'a été nécessaire
  }

  REQUIRE(Tracker::count() == 0); // Tous les trackers ont été détruits
}
