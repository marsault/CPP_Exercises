#pragma once

#include "Material.hpp"
#include "Recipe.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <set>
#include <map>

using MaterialAmount = std::pair<const Material *, size_t>;
using MaterialBag = std::unordered_map<const Material *, size_t, MaterialHasher>;
using RecipeCollection = std::set<Recipe, std::less<>>;

enum class Outcome
{
    SUCCESS,
    FAILURE
};

// Contient le résultat de la production d'une recette.
struct ProductionResult
{
    // La recette utilisée.
    const Recipe *recipe = nullptr;

    // La liste des matériaux manquants pour produire la recette.
    MaterialBag missing_materials;
};

// Contient toutes les données utiles au programme.
class ProgramData
{
public:
    // Ajoute un nouveau materiau existant
    void register_material(std::string);

    // Récupère la liste des matériaux présents dans l'inventaire.
    void get_all_possible_materials(std::vector<const Material *> &) const;

    // Ajoute un nouveau materiau à l'inventaire.
    void add_material_to_inventory(const Material *, size_t = 1u);

    // Récupère la liste des matériaux présents dans l'inventaire avec la quantité correspondante
    void get_inventory(MaterialBag &) const;

    // Enregistre un nouveau modèle de recette au répertoire.
    void register_recipe(std::vector<const Material *>, const Material *);

    // Collecte la liste de toutes les recettes
    void get_all_recipes(std::vector<const Recipe *> &) const;

    // Collecte la liste des recettes réalisables avec les matériaux présents dans l'inventaire.
    void get_doable_recipes(std::vector<const Recipe *> &) const;

    // Tente de réaliser la recette demandée
    // Si c'est possible, renvoie SUCCESS et indique le Material créé dans materials
    // Sinon, renvoie FAILURE et indique les materiaux manquant dans Renvoie SUCCESS si c'est possible et FAILURE sinon
    Outcome produce(const Recipe &recipe, MaterialBag &materials);

    // Réinitialise les données du programmes (vide toutes les structures)
    void reset();

    const Material *get_material_by_name(const std::string &name) const;
    const Recipe *get_recipe_by_id(size_t id) const;
    size_t get_material_count_in_inventory(const Material *material) const;

    void remove_material_from_inventory(const Material *, size_t = 1u);

private:
    // Placez vos données ici...
    std::vector<std::unique_ptr<Material>> _all_possible_materials;
    RecipeCollection _registered_recipes;
    std::unordered_map<std::string, Material *> _material_from_name;
    MaterialBag _inventory;

    MaterialBag missing_material(const MaterialBag &bag) const;
};
