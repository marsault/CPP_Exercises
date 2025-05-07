#include "../src/Base.hpp"
#include "../src/DerivedInt.hpp"
#include "../src/DerivedList.hpp"
#include "../src/DerivedString.hpp"

#include <catch2/catch_test_macros.hpp>

class Derived42 : public DerivedInt
{
public:
    Derived42()
        : DerivedInt { 42 }
    {}
    std::string to_string() const { return "6 x 9"; }
};

TEST_CASE("On peut ajouter n'importe quelle classe qui dérive de Base.")
{
    DerivedList l;
    Base&       r = l;

    Derived42     i42; // On utilise la classe Derived42, inconnue dans votre fichier.
    DerivedInt    i43 { 43 };
    DerivedString s44 { "quarante quatre" };
    DerivedList   subl {};
    Base&         b42 = i42;
    Base&         b43 = i43;
    Base&         b44 = s44;
    Base&         b45 = subl;
    l.add(b42);
    l.add(b43);
    subl.add(b44); // subl vaut [quarante quatre]
    l.add(b45);

    REQUIRE(l.is_null() == false); // is_null() teste si la liste est vide.
    REQUIRE(r.is_null() == false);

    std::stringstream ss;
    ss << r;
    REQUIRE(ss.str() == "[42,43,[quarante quatre]]");
}
