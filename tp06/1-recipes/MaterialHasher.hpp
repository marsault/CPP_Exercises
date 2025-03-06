#include "Material.hpp"

#include <memory>
#include <string>

class MaterialHasher
{
public:
    size_t operator()(const Material *m) const
    {
        std::hash<std::string> hasher;
        return _hasher(m->name());
    };
    size_t operator()(const std::unique_ptr<Material> &m) const
    {
        std::hash<std::string> hasher;
        return _hasher(m->name());
    };
    size_t operator()(const std::string &m) const
    {
        std::hash<std::string> hasher;
        return _hasher(m);
    };

private:
    std::hash<std::string> _hasher;
};
