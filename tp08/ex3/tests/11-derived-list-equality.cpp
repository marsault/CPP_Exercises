#include "../src/Base.hpp"
#include "../src/DerivedInt.hpp"
#include "../src/DerivedList.hpp"
#include "../src/DerivedString.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("L'égalité fonctionne sur les DerivedList.")
{
    DerivedList l1;
    Base&       r1 = l1;

    {
        DerivedInt    i42 { 42 };
        DerivedInt    i43 { 43 };
        DerivedString s44 { "quarante quatre" };
        DerivedList   subl {};
        Base&         b42 = i42;
        Base&         b43 = i43;
        Base&         b44 = s44;
        Base&         b45 = subl;
        l1.add(std::move(b42));
        l1.add(std::move(b43));
        subl.add(std::move(b44)); // subl vaut [quarante quatre]
        l1.add(std::move(b45));
    }

    DerivedList l2;
    Base&       r2 = l2;

    {
        DerivedInt    i42 { 42 };
        DerivedInt    i43 { 43 };
        DerivedString s44 { "quarante quatre" };
        DerivedList   subl {};
        Base&         b42 = i42;
        Base&         b43 = i43;
        Base&         b44 = s44;
        Base&         b45 = subl; // subl vaut [quarante quatre]
        l2.add(std::move(b42));
        l2.add(std::move(b43));
        subl.add(std::move(b44));
        l2.add(std::move(b45));
    }

    REQUIRE(l1 == l2);
    REQUIRE(r1 == r2);

    {
        DerivedInt    i42 { 42 };
        DerivedInt    i43 { 43 };
        DerivedString s44 { "quarante quatre" };
        DerivedList   subl {};
        Base&         b42 = i42;
        Base&         b43 = i43;
        Base&         b44 = s44;
        Base&         b45 = subl;
        subl.add(std::move(b44));

        REQUIRE(!(b42 == r1));
        REQUIRE(!(subl == r1));
    }
}
