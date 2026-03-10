#include "../lib/Tracker.hpp"
#include "../src/MultiMap.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(
    "Modifier la classe `MultiMap` de façon à ce que les `Tracker` soient "
    "automatiquement détruits avec elle.")
{
  {
    MultiMap multimap;
    {
      auto i0 = multimap.add("Céline", 0);
      auto i1 = multimap.add("Christophe", 11);
      auto i2 = multimap.add("Clément", 222);
      auto i3 = multimap.add("Victor", 3333);
      auto i4 = multimap.add("Youssef", 44444);

      /* CHECKING map1 */
      REQUIRE(multimap._map1.count("Céline") == 1u);
      REQUIRE(*multimap._map1["Céline"] == *i0);

      REQUIRE(multimap._map1.count("Christophe") == 1u);
      REQUIRE(*multimap._map1["Christophe"] == *i1);

      REQUIRE(multimap._map1.count("Clément") == 1u);
      REQUIRE(*multimap._map1["Clément"] == *i2);

      REQUIRE(multimap._map1.size() == 5u);

      /* Checking map2 */
      REQUIRE(multimap._map2.count(222) == 1u);
      REQUIRE(*multimap._map2[222] == *i2);

      REQUIRE(multimap._map2.count(3333) == 1u);
      REQUIRE(*multimap._map2[3333] == *i3);

      REQUIRE(multimap._map2.count(44444) == 1u);
      REQUIRE(*multimap._map2[44444] == *i4);

      REQUIRE(multimap._map2.size() == 5u);

      // Rappel: à la fin d'un bloc, les variables locales
      // (ici i0,i1,i2,i3,i4) sont détruites.
    }

    // Les Tracker sont toujours en mémoire car dans `multimap`
    REQUIRE(Tracker::count() == 5);

    // Ici, c'est multimap qui est détruite.
  }
  REQUIRE(Tracker::count() == 0);
}
