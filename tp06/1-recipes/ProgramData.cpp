#include "ProgramData.hpp"
#include <iostream>


void ProgramData::register_material(std::string name)
{
  std::cout << "Feature is not yet implemented (register_material)" << std::endl;
}

void ProgramData::get_registered_materials(std::vector<const Material*>& materials) const
{
  std::cout << "Feature is not yet implemented (get_registered_materials)" << std::endl;
}

void ProgramData::add_material_to_inventory(const Material* mat, int quantity)
{
  std::cout << "Feature is not yet implemented (add_material_to_inventory)" << std::endl;
}

void ProgramData::get_inventory(MaterialBag& materials) const
{
  std::cout << "Feature is not yet implemented (get_inventory)" << std::endl;
}

const Material* ProgramData::get_material_by_name(const std::string& name) const
{
  std::cout << "Feature is not yet implemented (get_material_by_name)" << std::endl;
  return nullptr;
}


// ============================================================================
// = Partie Recette ===========================================================
// ============================================================================

void ProgramData::register_recipe(std::vector<const Material*> materials,
                                  const Material* product)
{
  std::cout << "Feature is not yet implemented (register_recipe)" << std::endl;
}

void ProgramData::get_all_recipes(std::vector<const Recipe*>& recipes) const
{
  std::cout << "Feature is not yet implemented (get_all_recipes)" << std::endl;
}

const Recipe* ProgramData::get_recipe_by_id(size_t id) const
{
  std::cout << "Feature is not yet implemented (get_recipe_by_id)" << std::endl;
  return nullptr;
}

void ProgramData::unregister_recipe(const Recipe&)
{
  std::cout << "Feature is not yet implemented (unregister_recipe)" << std::endl;
}


// ============================================================================
// = Partie Production ========================================================
// ============================================================================


void ProgramData::get_doable_recipes(std::vector<const Recipe*>& recipes) const
{
  std::cout << "Feature is not yet implemented (get_doable_recipes)" << std::endl;
}

Outcome ProgramData::produce(const Recipe& recipe, MaterialBag& materials)
{
  std::cout << "Feature is not yet implemented (produce)" << std::endl;
  return Outcome::FAILURE;
}
