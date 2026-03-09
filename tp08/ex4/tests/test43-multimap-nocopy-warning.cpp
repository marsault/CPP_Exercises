#include "../src/MultiMap.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(
    "Attention aux tests cachés: j'espère que vous avez déplacé les std::string dans Multimap::add "
    "sans que je vous l'ai demandé. ")
{
  // Il faut rajouter la ligne suivante dans Multimap.hpp pour faire passer ce test
  // #define JAI_LU_LE_WARNING_43 true
  REQUIRE(JAI_LU_LE_WARNING_43);
}
