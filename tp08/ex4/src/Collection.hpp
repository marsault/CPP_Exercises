// VOUS POUVEZ MODIFIER CE FICHIER
#pragma once

#include "../lib/Tracker.hpp"

#include <memory>
#include <vector>

class Collection
{
public:
  Tracker& add_instance();
  void add_null() { _instances.push_back(nullptr); }

  std::vector<std::unique_ptr<Tracker>> _instances;
};