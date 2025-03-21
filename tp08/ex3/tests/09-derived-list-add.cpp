#include "../src/Base.hpp"
#include "../src/DerivedInt.hpp"
#include "../src/DerivedList.hpp"
#include "../src/DerivedString.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("On peut rajouter des éléments dans une DerivedList.")
{
    DerivedList l;
    Base&       r = l;

    DerivedInt    i42 { 42 };
    DerivedInt    i43 { 43 };
    DerivedString s44 { "quarante quatre" };
    l.add(i42);
    l.add(i43);
    l.add(s44);

    REQUIRE(l.is_null() == false); // is_null() teste si la liste est vide.
    REQUIRE(r.is_null() == false);

    std::stringstream ss;
    ss << r;
    REQUIRE(ss.str() == "[42,43,quarante quatre]");
}
