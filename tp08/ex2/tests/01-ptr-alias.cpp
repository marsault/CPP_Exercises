#include "../lib/Tracker.hpp"
#include "../src/alias.hpp" // Fichier à remplir

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Definir les alias PTR_ALIAS1 et PTR_ALIAS2 dans ../src/alias.hpp.  Il n'y a pas besoin "
          "d'implémenter des classes !")
{
    {
        PTR_ALIAS1 ptr { new Tracker {} };
        auto&      Tracker = *ptr; // Verifie que ptr peut-être déréférencé
        REQUIRE(1 == Tracker::count());
        REQUIRE(0 == Tracker::copies());
    }
    REQUIRE(0 == Tracker::count());
    // Vérifie que le Tracker pointé a bien été détruit.
    // (Il en reste 0 en mémoire)

    {
        PTR_ALIAS2 ptr     = new Tracker {};
        auto&      Tracker = *ptr; // Verifie que ptr peut-être déréférencé
        REQUIRE(1 == Tracker::count());
    }
    REQUIRE(1 == Tracker::count());
    // Vérifie que le Tracker pointé n'a PAS été détruit
    // (Il en reste 1 en mémoire)
}
