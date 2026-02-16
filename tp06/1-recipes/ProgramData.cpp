#include "ProgramData.hpp"
#include <iostream>

void ProgramData::register_material(std::string name) {
  auto &x = _registered_materials.emplace_back(new Material{name});
  _material_from_name[std::move(name)] = x.get();
}

void ProgramData::get_registered_materials(
    std::vector<const Material *> &materials) const {
  for (auto &ptr : _registered_materials)
    materials.emplace_back(ptr.get());
}

void ProgramData::add_material_to_inventory(const Material *mat, int quantity) {
  auto it = _inventory.find(mat);
  if (it == _inventory.end()) {
    _inventory[mat] = quantity;
    std::cout << "Added " << quantity << " " << *mat << " to inventory"
              << std::endl;
  } else {
    it->second += quantity;
    std::cout << "Inventory now contains " << it->second << " " << *mat
              << std::endl;
  }
}

void ProgramData::remove_material_from_inventory(const Material *mat,
                                                 size_t quantity) {
  auto it = _inventory.find(mat);
  if (it == _inventory.end() || it->second < quantity)
    std::cout << "Could not remove " << quantity << " " << *mat
              << " from inventory (not enough)." << std::endl;
  else
    std::cout << "Removed " << quantity << " " << *mat << " from inventory"
              << std::endl;
}

void ProgramData::get_inventory(MaterialBag &materials) const {
  for (auto &p : _inventory)
    materials.emplace(p);
}

const Material *
ProgramData::get_material_by_name(const std::string &name) const {
  auto it = _material_from_name.find(name);
  if (it == _material_from_name.end())
    return nullptr;
  else
    return it->second;
}

const Recipe *ProgramData::get_recipe_by_id(size_t id) const {
  auto it = _registered_recipes.find(id);
  if (it == _registered_recipes.end())
    return nullptr;
  else
    return &(*it);
}

void ProgramData::register_recipe(std::vector<const Material *> materials,
                                  const Material *product) {
  MaterialBag materials_as_bag;
  for (auto *m : materials) {
    auto it = materials_as_bag.find(m);
    if (it == materials_as_bag.end())
      materials_as_bag[m] = 1u;
    else
      ++(it->second);
  }
  Recipe new_recipe{std::move(materials_as_bag), product};
  std::cout << "Recipe <" << new_recipe << "> was registered" << std::endl;
  _registered_recipes.emplace(std::move(new_recipe));
}

void ProgramData::get_all_recipes(std::vector<const Recipe *> &recipes) const {
  for (const auto &p : _registered_recipes)
    recipes.push_back(&p);
}

void ProgramData::get_doable_recipes(
    std::vector<const Recipe *> &recipes) const {
  for (const auto &p : _registered_recipes)
    if (missing_material(p.requirements()).empty())
      recipes.push_back(&p);
}

size_t
ProgramData::get_material_count_in_inventory(const Material *material) const {
  auto it = _inventory.find(material);
  if (it == _inventory.end())
    return 0u;
  else
    return it->second;
}

MaterialBag ProgramData::missing_material(const MaterialBag &bag) const {
  MaterialBag result;
  for (const auto &p : bag) {
    size_t count = get_material_count_in_inventory(p.first);
    if (count < p.second)
      result[p.first] = p.second - count;
  }
  return result;
}

Outcome ProgramData::produce(const Recipe &recipe, MaterialBag &materials) {
  MaterialBag missing = missing_material(recipe.requirements());
  if (!missing.empty()) {
    materials = missing;
    return Outcome::FAILURE;
  }
  for (const auto &p : recipe.requirements())
    remove_material_from_inventory(p.first, p.second);
  add_material_to_inventory(recipe.product());
  return Outcome::SUCCESS;
}
