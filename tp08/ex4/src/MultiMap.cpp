// VOUS POUVEZ MODIFIER CE FICHIER
#include "MultiMap.hpp"

Tracker* MultiMap::add(std::string str, int i)
{
  Tracker* ic = new Tracker();
  _map1.emplace(std::move(str), ic);
  _map2.emplace(i, ic);
  return ic;
}