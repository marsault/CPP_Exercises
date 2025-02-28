#pragma once

#include "Material.hpp"
#include "Recipe.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>

// Contient le résultat de la production d'une recette.
struct ProductionResult
{
    // La recette utilisée.
    const Recipe *recipe = nullptr;

    // La liste des matériaux manquants pour produire la recette.
    std::vector<std::string> missing_materials;
};

// Contient toutes les données utiles au programme.
class ProgramData
{
public:
    // Ajoute un nouveau materiau existant
    void register_material(std::string);

    // Récupère la liste des matériaux présents dans l'inventaire.
    void get_all_possible_materials(std::vector<const Material *> &materials) const;

    // Ajoute un nouveau materiau à l'inventaire.
    void add_material_to_inventory(const Material *material, size_t quantity = 1u);

    // Récupère la liste des matériaux présents dans l'inventaire avec la quantité correspondante
    void get_inventory(std::vector<MaterialAmount> &materials) const;

    // Enregistre un nouveau modèle de recette au répertoire.
    void register_recipe(std::vector<const Material *> materials, const Material *);

    // Enregistre un nouveau modèle de recette au répertoire.
    void get_all_recipes(std::list<const Recipe &> materials);

    // Collecte la liste des recettes réalisables avec les matériaux présents dans l'inventaire.
    void collect_doable_recipes(std::vector<const Recipe *> &recipes) const;

    // Tente de réaliser la recette demandée.
    ProductionResult produce(size_t recipe_id);

    const Material *get_material_by_name(const std::string &name) const;
    const Material *get_material_by_id(size_t) const;

private:
    // Placez vos données ici...
    std::vector<std::unique_ptr<Material>> _all_possible_materials;
    std::vector<Recipe> _registered_recipes;
    std::unordered_map<std::string, Material *> _material_from_name;
    MaterialBag _inventory;
};
