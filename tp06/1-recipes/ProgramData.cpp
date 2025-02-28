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

void ProgramData::add_material(std::string name)
{
    const Material *mat = get_material_by_name(name);
    auto it = _inventory.find(mat);
    if (it == _inventory.end())
        _inventory[mat] = 1;
    else
        ++(it->second);
}

void ProgramData::get_inventory(MaterialBag &materials) const
{
}

void ProgramData::register_recipe(std::vector<std::string> materials, std::vector<std::string> products)
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