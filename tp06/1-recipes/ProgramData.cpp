#include "ProgramData.hpp"

#include "Material.hpp"

#include <algorithm>
#include <iostream>

void ProgramData::add_material(std::string name) {
    auto material = std::make_unique<Material>(std::move(name));
    std::cout << *material << " was created" << std::endl;
    _materials.emplace_back(std::move(material));
}

void ProgramData::get_materials(std::vector<const Material*>& materials) const {
    for (const auto& elem : _materials)
    {
        materials.emplace_back(elem.get());
    }
}

void ProgramData::register_recipe(std::vector<std::string> materials, std::vector<std::string> products) {
    auto product = std::make_unique<Recipe>(std::move(materials), std::move(products));
    std::cout << "Recip <" << *product << "> has been registered" << std::endl;
    _recipes.emplace_back(std::move(product));
}

void ProgramData::remove_material(const std::string& name) {
    auto it = std::find_if(_materials.begin(), _materials.end(),
                           [&name](const std::unique_ptr<Material>& material) { return *material == name; });
    if (it != _materials.end())
    {
        _materials.erase(it);
    }
}

ProductionResult ProgramData::produce(size_t recipe_id) {
    ProductionResult result;
    for (const auto& recipe : _recipes)
    {
        if ((*recipe).get_id() == recipe_id)
        {
            result.recipe = recipe.get();
        }
    }
    if (result.recipe == nullptr)
    {
        return result;
    }
    if (!have_all_materials(*(result.recipe), &(result.missing_materials)))
    {
        return result;
    }
    for (const auto& material : result.recipe->get_materials())
    {
        remove_material(material);
    }
    for (const auto& material : result.recipe->get_products())
    {
        add_material(material);
    }
    return result;
}

bool ProgramData::have_all_materials(const Recipe& recipe, std::vector<std::string>* materials) const {
    auto result           = true;
    auto recipe_materials = recipe.get_materials();
    for (const auto& material : recipe_materials)
    {
        bool isFoud = false;
        for (const auto& this_material : _materials)
        {
            if (*this_material == material)
            {
                isFoud = true;
                break;
            }
        }
        if (!isFoud)
        {
            if (materials == nullptr)
            {
                return false;
            }
            materials->emplace_back(material);
            result = false;
        }
    }
    return result;
}

void ProgramData::collect_doable_recipes(std::vector<const Recipe*>& recipes) const {
    for (const auto& recipe : _recipes)
    {
        // std::vector<std::string&> missing_materials;
        if (have_all_materials(*recipe, nullptr))
        {
            recipes.emplace_back(recipe.get());
        }
    }
}