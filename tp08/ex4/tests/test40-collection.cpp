#include "../lib/Tracker.hpp"
#include "../src/Collection.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(
    "Modifier la classe `Collection` de façon à ce que les éléments dans "
    "`_instances` soient automatiquement détruits avec elle.")
{
  {
    Collection collec;
    {
      Tracker& i0 = collec.add_instance();
      REQUIRE(Tracker::count() == 1);

      collec.add_null();
      collec.add_null();

      Tracker& i3 = collec.add_instance();
      REQUIRE(Tracker::count() == 2);

      collec.add_null();

      REQUIRE(collec._instances.size() == 5u);

      REQUIRE(collec._instances[0] != nullptr);
      REQUIRE(*(collec._instances[0]) == i0);

      REQUIRE(collec._instances[1] == nullptr);
      REQUIRE(collec._instances[2] == nullptr);

      REQUIRE(collec._instances[3] != nullptr);
      REQUIRE(*(collec._instances[3]) == i3);

      REQUIRE(collec._instances[4] == nullptr);

      // Rappel: à la fin d'un bloc, les variables locales
      // (ici i0 et i3) sont détruites.
    }
    REQUIRE(Tracker::count() == 2);
  }
  REQUIRE(Tracker::count() == 0);
}
