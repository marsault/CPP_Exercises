// VOUS POUVEZ MODIFIER CE FICHIER
#include "Collection.hpp"

Tracker& Collection::add_instance()
{
  _instances.push_back(std::make_unique<Tracker>());
  return *(_instances.back());
}