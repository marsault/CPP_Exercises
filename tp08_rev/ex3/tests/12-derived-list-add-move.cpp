#include "../src/Base.hpp"
#include "../src/DerivedInt.hpp"
#include "../src/DerivedList.hpp"
#include "../src/DerivedString.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("On peut déplacer l'objet ajouté quand on add.")
{
    DerivedList l1;
    Base&       r1 = l1;

    DerivedInt    i42 { 42 };
    DerivedInt    i43 { 43 };
    DerivedString s44 { "quarante quatre" };
    DerivedList   subl {};
    Base&         b42 = i42;
    Base&         b43 = i43;
    Base&         b44 = s44;
    Base&         b45 = subl;
    l1.add(b42);
    l1.add(b43);
    subl.add(b44); // subl vaut [quarante quatre]
    l1.add(b45);   // l vaut [42,43,[quarante quatre]]

    DerivedList l2;
    l2.add(std::move(r1)); // On déplace l1 dans l2 à travers sa reference r1
    std::stringstream ss2;
    ss2 << l2;
    REQUIRE(ss2.str() == "[[42,43,[quarante quatre]]]");

    REQUIRE(l1.is_null() == true); // l1 est maintenant vide
    std::stringstream ss1;
    ss1 << l1;
    REQUIRE(ss1.str() == "[]");
}
