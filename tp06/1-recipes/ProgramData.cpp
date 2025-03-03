#include "ProgramData.hpp"

void ProgramData::register_material(std::string name)
{
    _all_possible_materials.emplace_back(new Material{name});
    _material_from_name[std::move(name)] = _all_possible_materials.back().get();
}

void ProgramData::get_all_possible_materials(std::vector<const Material *> &materials) const
{
    for (auto &ptr : _all_possible_materials)
        materials.emplace_back(ptr.get());
}

void ProgramData::add_material_to_inventory(const Material *mat, size_t quantity)
{
    auto it = _inventory.find(mat);
    if (it == _inventory.end())
    {
        _inventory[mat] = quantity;
        std::cout << "Added " << quantity << " " << *mat << " to inventory" << std::endl;
    }
    else
    {
        it->second += quantity;
        std::cout << "Inventory now contains " << it->second << " " << *mat << std::endl;
    }
}

void ProgramData::get_inventory(std::vector<std::pair<const Material *, size_t>> &materials) const
{
    for (auto &p : _inventory)
        materials.emplace_back(p);
}

const Material *ProgramData::get_material_by_name(const std::string &name) const
{
    auto it = _material_from_name.find(name);
    if (it == _material_from_name.end())
        return nullptr;
    else
        return it->second;
}

void ProgramData::register_recipe(std::vector<const Material *> materials, const Material *product)
{
    MaterialBag materials_as_bag;
    for (auto *m : materials)
    {
        auto it = materials_as_bag.find(m);
        if (it == materials_as_bag.end())
            materials_as_bag[m] = 1u;
        else
            ++(it->second);
    }
    Recipe new_recipe{std::move(materials_as_bag), product};
    std::cout << "Recipe <" << new_recipe << "> was registered" << std::endl;
    _registered_recipes.emplace(new_recipe.id(), std::move(new_recipe));
}

void ProgramData::get_all_recipes(std::vector<const Recipe *> &recipes) const
{
    for (const auto &p : _registered_recipes)
        recipes.push_back(&p.second);
}

void ProgramData::get_doable_recipes(std::vector<const Recipe *> &recipes) const
{
    for (const auto &p : _registered_recipes)
        //                                               vvvvvvvvvvvvv empty material bag
        if (missing_material(p.second.requirements()) != MaterialBag{})
            recipes.push_back(&p.second);
}

size_t ProgramData::get_material_count_in_inventory(const Material *material) const
{
    auto it = _inventory.find(material);
    if (it == _inventory.end())
        return 0;
    else
        return it->second;
}

MaterialBag ProgramData::missing_material(const MaterialBag &bag) const
{
    MaterialBag result;
    for (const auto &p : bag)
    {
        size_t count = get_material_count_in_inventory(p.first);
        if (count < p.second)
            result[p.first] = p.second - count;
    }

    return result;
}

ProductionResult ProgramData::produce(size_t recipe_id)
{
    ProductionResult result;
    return result;
}