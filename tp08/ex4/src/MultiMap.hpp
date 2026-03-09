// VOUS POUVEZ MODIFIER CE FICHIER
#pragma once

#include "../lib/Tracker.hpp"

#include <map>
#include <string>

class MultiMap
{
public:
  Tracker* add(std::string str, int i);


  // Normalement ces données devraient être private mais poru simplifier les tests, on les laisse
  // public.
  std::map<std::string, Tracker*> _map1;
  std::map<int, Tracker*> _map2;
};