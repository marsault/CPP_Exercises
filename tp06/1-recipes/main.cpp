#include "Material.hpp"
#include "ProgramData.hpp"
#include "lib/Action.hpp"
#include "Recipe.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void print_usage(ProgramData &)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\tm <nom>                                 : Ajoute le materiau donne a l'inventaire"
              << std::endl;
    std::cout
        << "\tl                                       : Affiche les materiaux presents dans l'inventaire"
        << std::endl;
    std::cout << "\tr <m1> [<m2> ...] => <p1> [<p2> ...]    : Enregistre la recette donnee" << std::endl;
    std::cout << "\tt                                       : Affiche les recettes realisables avec "
                 "l'inventaire actuel"
              << std::endl;
    std::cout << "\tp <id>                                  : Tente de produire la recette demandee"
              << std::endl;
    std::cout << "\tq                                       : Ferme le programme" << std::endl;
}

std::deque<std::string> parse_words(const std::string &command)
{
    auto words = std::deque<std::string>{};

    auto str = std::stringstream{command};
    while (str.good())
    {
        str >> words.emplace_back();
    }

    return words;
}

std::string pop_next(std::deque<std::string> &words)
{
    if (words.empty())
    {
        return "";
    }
    else
    {
        auto next = std::move(words.front());
        words.pop_front();
        return next;
    }
}

bool is_valid_name(const std::string &name, bool display_error = true)
{
    bool result = !name.empty();
    for (char c : name)
        result &= (std::isupper(c) || std::islower(c));
    if (!result && display_error)
        std::cerr << "Invalid material name '" << name << "'" << std::endl;
    return result;
}

// std::vector<std::string> consume_names(std::deque<std::string> &words)
// {
//     auto names = std::vector<std::string>{};

//     while (!words.empty())
//     {
//         if (!is_valid_name(words.front()), false)
//         {
//             break;
//         }

//         names.emplace_back(pop_next(words));
//     }

//     return names;
// }

// // returns true if the program should quit
// bool execute_command(ProgramData &data, const std::string &command)
// {
//     auto materials_buffer = std::vector<const Material *>{};
//     auto recipes_buffer = std::vector<const Recipe *>{};

//     auto words = parse_words(command);
//     if (words.empty())
//     {
//         print_usage();
//         return false;
//     }

//     auto action = pop_next(words);
//     if (action == "m")
//     {
//         auto name = pop_next(words);
//         if (!is_valid_name(name))
//         {
//             std::cerr << "'" << name << "' is not a valid material name" << std::endl;
//             print_usage();
//             return false;
//         }

//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 'm' arguments" << std::endl;
//             print_usage();
//             return false;
//         }

//         data.add_material(std::move(name));
//     }
//     else if (action == "list")
//     {
//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 'list' arguments" << std::endl;
//             print_usage();
//             return false;
//         }

//         materials_buffer.clear();
//         data.get_materials(materials_buffer);

//         for (const auto *m : materials_buffer)
//         {
//             std::cout << *m << std::endl;
//         }
//     }
//     else if (action == "new")
//     {
//         auto subaction = pop_next(words);
//         if (subaction == "")
//         {
//             std::cerr << "Action '" << action << "'expects a sub action" << std::endl;
//             print_usage();
//             return false;
//         }
//         if (subaction == "mat")
//         {
//             auto name = pop_next(words);
//             if (!is_valid_name(name))
//             {
//                 std::cerr << "'" << name << "' is not a valid material name" << std::endl;
//                 print_usage();
//                 return false;
//             }
//             if (auto next = pop_next(words); next != "")
//             {
//                 std::cerr << "Unexpected token '" << next << "' while parsing 'm' arguments" << std::endl;
//                 print_usage();
//                 return false;
//             }
//             data.register_material(std::move(name));
//         }
//         else if (action == "rec")
//         {

//             auto materials = consume_names(words);
//             if (materials.empty())
//             {
//                 std::cerr << "No materials have been given" << std::endl;
//                 print_usage();
//                 return false;
//             }

//             if (auto next = pop_next(words); next != "=>")
//             {
//                 std::cerr << "Unexpected token '" << next << "' while parsing recipe formula" << std::endl;
//                 print_usage();
//                 return false;
//             }

//             auto products = consume_names(words);
//             if (products.empty())
//             {
//                 std::cerr << "No products have been given" << std::endl;
//                 print_usage();
//                 return false;
//             }

//             if (auto next = pop_next(words); next != "")
//             {
//                 std::cerr << "Unexpected token '" << next << "' while parsing 'r' arguments" << std::endl;
//                 print_usage();
//                 return false;
//             }

//             data.register_recipe(std::move(materials), std::move(products));
//         }
//         else
//         {
//             std::cerr << "Unrecognized subaction " << subaction << "of action 'new'" << std::endl;
//             print_usage();
//             return false;
//         }
//     }
//     else if (action == "t")
//     {
//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 't' arguments" << std::endl;
//             print_usage();
//             return false;
//         }

//         recipes_buffer.clear();
//         data.collect_doable_recipes(recipes_buffer);

//         for (const auto *r : recipes_buffer)
//         {
//             std::cout << *r << std::endl;
//         }
//     }
//     else if (action == "p")
//     {
//         auto arg = pop_next(words);
//         auto id = std::atoi(arg.c_str());
//         if (id <= 0)
//         {
//             std::cerr << "'" << arg << "' is not a valid identifier" << std::endl;
//             print_usage();
//             return false;
//         }

//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 't' arguments" << std::endl;
//             print_usage();
//             return false;
//         }

//         auto result = data.produce(id);
//         if (result.recipe == nullptr)
//         {
//             std::cerr << "No recipe is identified with " << id << std::endl;
//             return false;
//         }

//         if (!result.missing_materials.empty())
//         {
//             std::cerr << "Unable to produce '" << *result.recipe
//                       << "' without the following materials :" << std::endl;
//             for (const auto &m : result.missing_materials)
//             {
//                 std::cerr << m << std::endl;
//             }
//         }
//     }
//     else if (action == "load")
//     {
//         auto filename = pop_next(words);
//         if (filename == "")
//         {
//             std::cerr << "No file to load has been given" << std::endl;
//             return false;
//         }
//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 'load' arguments" << std::endl;
//             print_usage;
//             return false;
//         }
//         std::ifstream file{filename + ".txt"};
//         if (!file.is_open())
//         {
//             std::cerr << "Failed to open save '" << filename << "'" << std::endl;
//             print_usage;
//             return false;
//         }
//         unsigned i = 0;
//         for (std::string line; getline(file, line);)
//         {
//             std::cerr << "[Executing line " << ++i << " of file " << filename << "] " << line << std::endl;
//             execute_command(data, line);
//         }
//     }
//     else if (action == "q")
//     {
//         if (auto next = pop_next(words); next != "")
//         {
//             std::cerr << "Unexpected token '" << next << "' while parsing 'q' arguments" << std::endl;
//             print_usage();
//             return false;
//         }
//         return true;
//     }
//     else
//     {
//         std::cerr << "Unknown command '" << action << "'" << std::endl;
//         print_usage();
//         return false;
//     }
//     return false;
// }

// Action 'add mat'
void add_mat(ProgramData &data, std::deque<std::string> args)
{
    if (!is_valid_name(args.front()))
        return;
    const Material *mat = data.get_material_by_name(args.front());
    data.add_material_to_inventory(mat);
}

// Action 'list mat'
void list_mat(ProgramData &data)
{
    std::vector<const Material *> buffer;
    data.get_all_possible_materials(buffer);
    std::cout << "Registered materials: " << (buffer.empty() ? "(empty)" : "") << std::endl;
    for (const auto *m : buffer)
        std::cout << "  - " << *m << std::endl;
}

// Action 'list rec'
void list_rec(ProgramData &data)
{
    std::vector<const Recipe *> buffer;
    data.get_all_recipes(buffer);
    std::cout << "Registered recipes: " << (buffer.empty() ? "(empty)" : "") << std::endl;
    for (const auto *r : buffer)
        std::cout << "  - " << (*r) << std::endl;
}

// Action 'list doable'
void list_doable(ProgramData &data)
{
    std::vector<const Recipe *> buffer;
    data.get_doable_recipes(buffer);
    std::cout << "Doable recipes: " << (buffer.empty() ? "(empty)" : "") << std::endl;
    for (const auto *r : buffer)
        std::cout << "  - " << (*r) << std::endl;
}

// Action 'produce'
void produce(ProgramData &data, std::string arg) {}

// Action 'list inv'
void list_inv(ProgramData &data)
{
    std::vector<std::pair<const Material *, size_t>> buffer;
    data.get_inventory(buffer);
    std::cout << "Inventory: " << (buffer.empty() ? "(empty)" : "") << std::endl;
    for (const auto &p : buffer)
    {
        std::cout << "  - " << *(p.first);
        if (p.second > 1)
            std::cout << " x" << p.second;
        std::cout << std::endl;
    }
}

// Action 'new mat'
void new_mat(ProgramData &data, std::string args)
{
    data.register_material(std::move(args));
}

// Action 'new rec'
void new_rec(ProgramData &data, std::deque<std::string> args)
{
    if (args.empty())
    {
        std::cerr << "No arguments provided to 'new rec'" << std::endl;
        return;
    }

    const Material *product = data.get_material_by_name(args.back());
    if (product == nullptr)
    {
        std::cerr << "Product of recipe (" << args.back() << ") is not registered" << std::endl;
        return;
    }
    args.pop_back();
    if (args.back() != "=>")
    {
        std::cerr << "Expected '=>' instead of '" << args.back() << "'" << std::endl;
        return;
    }
    args.pop_back();

    std::vector<const Material *> materials;
    for (auto &s : args)
    {
        materials.emplace_back(data.get_material_by_name(s));
        if (materials.back() == nullptr)
        {
            std::cerr << "Material " << s << " is not registered" << std::endl;
            return;
        }
    }

    data.register_recipe(std::move(materials), product);
}

// Action 'load'
void load(const ActionManager &manager, ProgramData &data, std::deque<std::string> args)
{
    std::ifstream file{args.front() + ".txt"};
    if (!file.is_open())
    {
        std::cerr << "Failed to open save '" << args.front() << "'" << std::endl;
        print_usage;
        return;
    }
    unsigned i = 0;
    for (std::string line; getline(file, line);)
    {
        std::cout << ">> Executing line " << ++i << " of file " << args.front() << ":" << std::endl
                  << line << std::endl;
        manager.execute_action(data, parse_words(line));
    }
}

int main(int argc, char **argv)
{
    ProgramData data;
    ActionManager manager;
    manager.register_action({"help"}, 0, print_usage);
    manager.register_action({"load"}, 1, load);
    manager.register_action({"new", "mat"}, 1, new_mat);
    manager.register_action({"add", "mat"}, 1, add_mat);
    manager.register_action({"new", "rec"}, -1, new_rec);
    manager.register_action({"list", "mat"}, 0, list_mat);
    manager.register_action({"list", "rec"}, 0, list_rec);
    manager.register_action({"list", "doable"}, 0, list_doable);
    manager.register_action({"list", "inv"}, 0, list_inv);
    manager.register_action({"produce"}, 1, produce);
    while (true)
    {
        std::cout << ">> Entrez une commande :" << std::endl;

        auto command = std::string{};
        while (command.empty())
        {
            std::getline(std::cin, command);
        }
        std::deque<std::string> arguments = parse_words(command);
        if (command == "quit")
            break;
        manager.execute_action(data, arguments);
        std::cout << std::endl;
    }
}
