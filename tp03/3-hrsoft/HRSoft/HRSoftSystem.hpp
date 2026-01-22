#pragma once

#include <list>
#include <string>

#include "Department.hpp"

class HRSoftSystem
{
public:
  Department& add_department(const std::string& name)
  {
    return _departments.emplace_back(name);
  }

private:
  std::list<Department> _departments;
};
