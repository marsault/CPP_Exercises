#include "../src/PhoneBook.hpp"
#include "../src/PhoneBookEntry.hpp"
#include "../src/PhoneNumber.hpp"

#include <catch2/catch_test_macros.hpp>

bool are_phone_numbers_equal(PhoneNumber pn1, PhoneNumber pn2)
{
    for (auto i = 0; i < 5; ++i)
    {
        if (pn1[i] != pn2[i])
        {
            return false;
        }
    }

    return true;
}

TEST_CASE("Lorsqu'on utilise get_number, la donnée pointée n'est pas désinstanciée par d'éventuelles "
          "insertions dans le PhoneBook")
{
    auto phone_book = PhoneBook {};

    phone_book.add_entry(PhoneBookEntry { "Pauline", PhoneNumber { 1, 64, 12, 66, 73 } });

    // On récupère le numéro de Pauline
    const auto* pauline_phone = phone_book.get_number("Pauline");
    REQUIRE(pauline_phone != nullptr);

    // On ajoute quelques nouvelles entrées
    const auto other_phone = PhoneNumber { 1, 2, 3, 4, 5 };
    phone_book.add_entry(PhoneBookEntry { "Adrien", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Benjamine", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Camille", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Daniel", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Edith", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Geoffroy", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Hugues", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Josiane", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Karine", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Lambert", other_phone });
    phone_book.add_entry(PhoneBookEntry { "Marceau", other_phone });

    REQUIRE(phone_book.get_number("Pauline") == pauline_phone);
}
