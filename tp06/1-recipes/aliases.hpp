#pragma once

#include <vector>
#include <utility>
#include <set>
#include <unordered_map>

class Material;
class Recipe;
class MaterialHasher;

using MaterialAmount = std::pair<const Material *, size_t>;
using MaterialBag = std::unordered_map<const Material *, size_t, MaterialHasher>;
using RecipeCollection = std::set<Recipe, std::less<>>;