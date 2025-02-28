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

void ProgramData::register_recipe(std::vector<const Material *> materials, const Material *)
{
}

void ProgramData::collect_doable_recipes(std::vector<const Recipe *> &recipes) const
{
}

ProductionResult ProgramData::produce(size_t recipe_id)
{
    ProductionResult result;
    return result;
}