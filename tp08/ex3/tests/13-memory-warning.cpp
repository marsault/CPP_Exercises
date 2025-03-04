#include "../src/Base.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("C'est la fin de l'exercice 3."
          "Prenez le temps à vérifier que vous n'avez pas de fuite mémoire."
          "Valgrind est votre ami.")
{
    // Il faut rajouter la ligne suivante dans Base pour faire passer ce test
    // #define JAI_LU_LE_WARNING_13 true
    REQUIRE(JAI_LU_LE_WARNING_13);
}
