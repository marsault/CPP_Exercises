#pragma once

#include "ActionManager.hpp"
#include "../Material.hpp"
#include "../ProgramData.hpp"
#include "../Recipe.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool is_valid_name(const std::string &name, bool display_error = true)
{
    bool result = !name.empty();
    for (char c : name)
        result &= (std::isupper(c) || std::islower(c));
    if (!result && display_error)
        std::cerr << "Invalid material name '" << name << "'" << std::endl;
    return result;
}

// Action 'help'
void help(const ActionManager &manager)
{
    std::cout << "Liste des commandes:" << std::endl
              << manager;
}

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
    data.get_registered_materials(buffer);
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
void produce(ProgramData &data, std::string arg)
{
    MaterialBag buffer;
    int i = std::stoi(arg);
    const Recipe *recipe = data.get_recipe_by_id(i);
    if (recipe != nullptr)
    {
        switch (data.produce(*recipe, buffer))
        {
        case Outcome::SUCCESS:
            break;
        case Outcome::FAILURE:
            std::cout << "Could not produce: " << *recipe << std::endl;
            std::cout << "Missing materials:" << std::endl;
            for (const MaterialAmount &p : buffer)
            {
                std::cout << "  - " << *(p.first);
                if (p.second > 1)
                    std::cout << " x" << p.second;
                std::cout << std::endl;
            }
        }
    }
}

// Action 'list inv'
void list_inv(ProgramData &data)
{
    MaterialBag buffer;
    data.get_inventory(buffer);
    std::cout << "Inventory: " << (buffer.empty() ? "(empty)" : "") << std::endl;
    for (const MaterialAmount &p : buffer)
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

// Action 'load'
void load(const ActionManager &manager, ProgramData &data, std::deque<std::string> args)
{
    std::ifstream file{args.front() + ".txt"};
    if (!file.is_open())
    {
        std::cerr << "Failed to open save '" << args.front() << "'" << std::endl;
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

// False action 'quit'. This function is never called.
void quit(const ActionManager &manager)
{
}