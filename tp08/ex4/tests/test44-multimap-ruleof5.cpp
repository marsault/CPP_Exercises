#include "../src/MultiMap.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(
    "MultiMap est toujours copiable et déplaçable.  Ce test compile probablement dès le début, "
    "mais pas forcément après avoir fait passés ceux d'avant.")
{
  {
    MultiMap multimap1;
    auto i0 = multimap1.add("Céline", 0);
    auto i1 = multimap1.add("Christophe", 11);

    MultiMap multimap2;
    auto i2 = multimap2.add("Clément", 222);
    auto i3 = multimap2.add("Victor", 3333);
    auto i4 = multimap2.add("Anthony", 44444);


    // MultiMap est copiable et affectable par copie
    MultiMap multimap_copy1 = multimap1;
    MultiMap multimap_copy2 = multimap2;
    multimap_copy2 = multimap_copy1;
    REQUIRE(multimap_copy2._map1.count("Céline") == 1);
    REQUIRE(multimap_copy2._map1.count("Anthony") == 0);

    // MultiMap est déplaçable et affectable par déplacement
    MultiMap multimap_moved1 = std::move(multimap1);
    MultiMap multimap_moved2 = std::move(multimap2);
    REQUIRE(multimap1._map1.empty()); // multimap1 est maintenant vide
    REQUIRE(multimap2._map2.empty()); // multimap2 est aussi vide

    multimap_moved2 = std::move(multimap_moved1);
    REQUIRE(multimap_moved2._map1.count("Céline") == 1);
    REQUIRE(multimap_moved2._map1.count("Anthony") == 0);
    REQUIRE(multimap_moved1._map2.empty()); // moved1 est maintenant vide
  }

  // A la fin, il n'y a pas de fuites mémoire
  REQUIRE(Tracker::count() == 0);
}
