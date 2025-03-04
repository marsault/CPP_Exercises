#include "../src/Base.hpp"
#include "../src/DerivedInt.hpp"
#include "../src/DerivedList.hpp"
#include "../src/DerivedString.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(
    "Il existent une classe DerivedList, qui dérive de base, et qui contient un ensemble de base.  Pour que "
    "ça compile, il faudra peut-être que vous ajoutiez des placeholfer pour certaines fonctions virtuelles.")
{
    DerivedList l;
    Base&       r = l;

    REQUIRE(l.is_null() == true); // is_null() teste si la liste est vide.
    REQUIRE(r.is_null() == true);

    std::stringstream ss;
    ss << r;
    REQUIRE(ss.str() == "[]");
}
