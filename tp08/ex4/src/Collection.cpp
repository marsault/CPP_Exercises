// VOUS POUVEZ MODIFIER CE FICHIER
#include "Collection.hpp"

Tracker& Collection::add_instance()
{
  _instances.push_back(new Tracker());
  return *(_instances.back());
}