#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class Scripts
{
public:
    Scripts();
    const std::vector<std::string> &Scripts::operator[](const std::string &script_name);
    std::vector<std::string> names();

private:
    std::unordered_map<std::string, std::vector<std::string>> _script_map;
};