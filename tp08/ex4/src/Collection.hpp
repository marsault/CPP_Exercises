// VOUS POUVEZ MODIFIER CE FICHIER
#pragma once

#include "../lib/Tracker.hpp"

#include <vector>

class Collection
{
public:
  Tracker& add_instance();
  void add_null() { _instances.push_back(nullptr); }

  std::vector<Tracker*> _instances;
};