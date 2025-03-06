#pragma once

#include "Material.hpp"
#include "Recipe.hpp"
#include "aliases.hpp"
#include <string>

enum class Outcome
{
  SUCCESS,
  FAILURE
};

// Contient toutes les données utiles au programme.
class ProgramData
{
public:
  //===== Partie Matériau =====================================================

  // Déclare un nouveau type de materiau
  void register_material(std::string);

  // Récupère la liste des matériaux présents dans l'inventaire
  void get_registered_materials(std::vector<const Material*>&) const;

  //===== Partie Inventaire ===================================================

  // Recupère un matériau avec le nom donné, ou nullptr si aucun matériau n'a ce nom
  const Material* get_material_by_name(const std::string& name) const;

  // Ajoute un nouveau materiau à l'inventaire
  void add_material_to_inventory(const Material*, int = 1);

  // Récupère la liste des matériaux présents dans l'inventaire avec la quantité
  // correspondante
  void get_inventory(MaterialBag&) const;

  //===== Partie Recette ======================================================

  // Enregistre un nouveau modèle de recette au répertoire
  void register_recipe(std::vector<const Material*>, const Material*);

  // Collecte la liste de toutes les recettes
  void get_all_recipes(std::vector<const Recipe*>&) const;

  // Recupère une recette dont l'identifiant est donné, ou nullptr si aucune recette n'a cet
  // identifiant
  const Recipe* get_recipe_by_id(size_t id) const;

  // Supprime la recette donnée en argument
  void unregister_recipe(const Recipe&);


  //===== Partie Production ===================================================

  // Collecte la liste des recettes réalisables avec les matériaux présents dans
  // l'inventaire
  void get_doable_recipes(std::vector<const Recipe*>&) const;

  // Tente de réaliser la recette demandée
  // Si c'est possible, renvoie SUCCESS
  // Sinon, renvoie FAILURE et indique les materiaux manquants dans le second argument
  Outcome produce(const Recipe& recipe, MaterialBag& materials);


  //
  // Vous aurez besoin d'ajouter des champs et des fonctions auxiliaires !!
};
