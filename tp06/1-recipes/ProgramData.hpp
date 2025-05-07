#pragma once

#include "Material.hpp"
#include "Recipe.hpp"

#include <memory>
#include <string>
#include <vector>

// Contient le résultat de la production d'une recette.
struct ProductionResult
{
    // La recette utilisée.
    const Recipe* recipe = nullptr;

    // La liste des matériaux manquants pour produire la recette.
    std::vector<std::string> missing_materials;
};

// Contient toutes les données utiles au programme.
class ProgramData
{
public:
    // Ajoute un nouveau materiau à l'inventaire.
    void add_material(std::string name);

    // Rébool have_all_materials(const Recipe* recipe)cupère la liste des matériaux présents dans
    // l'inventaire.
    void get_materials(std::vector<const Material*>& materials) const;

    // Enregistre un nouveau modèle de recette au répertoire.
    void register_recipe(std::vector<std::string> materials, std::vector<std::string> products);

    // vérifie si une recette a tous les matériaux dont il a besoin et rempli le vector des matériaux
    // manquants
    bool have_all_materials(const Recipe& recipe, std::vector<std::string>* materials) const;

    // Collecte la liste des recettes réalisables avec les matériaux présents dans l'inventaire.
    void collect_doable_recipes(std::vector<const Recipe*>& recipes) const;

    // Tente de réaliser la recette demandée.
    ProductionResult produce(size_t recipe_id);

    void remove_material(const std::string& name);

private:
    std::vector<std::unique_ptr<Material>> _materials;
    std::vector<std::unique_ptr<Recipe>>   _recipes;
};
