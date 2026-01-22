#pragma once

#include <utility> // pair
#include <vector>

class Material;
class Recipe;

using MaterialBag = std::vector<std::pair<const Material*, size_t>>;
using RecipeCollection = std::vector<Recipe>;