#include "Scripts.hpp"

Scripts::Scripts()
{
    _script_map["mat1"] = {"new mat Eau",
                           "new mat Sirop",
                           "list mat"};

    _script_map["mat2"] = {"new mat Eau",
                           "add mat Eau",
                           "add mat Eau",
                           "new mat Sirop",
                           "add mat Eau",
                           "add mat Sirop",
                           "list inv"};

    _script_map["rec"] = {"new mat Eau",
                          "new mat Sirop",
                          "list mat"};

    _script_map["prod"] = {"new mat Paille",
                           "new mat Bois"
                           "new mat Pierre"
                           "new mat Maison",
                           "new rec Paille Paille Paille Paille => Maison",
                           "new rec Bois Bois Bois => Maison",
                           "new rec Pierre Pierre => Maison",
                           "add mat Paille",
                           "add mat Paille",
                           "add mat Paille",
                           "add mat Paille",
                           "add mat Paille",
                           "add mat Paille",
                           "add mat Bois",
                           "add mat Bois",
                           "list doable"};
}

const std::vector<std::string> &Scripts::operator[](const std::string &script_name)
{
    static std::vector<std::string> empty_cmd;

    auto it = _script_map.find(script_name);
    if (it == _script_map.end())
        return empty_cmd;
}

std::vector<std::string> Scripts::names()
{
    std::vector<std::string> result;
    for (auto &p : _script_map)
    {
        result.push_back(p.first);
    }
    return result;
}