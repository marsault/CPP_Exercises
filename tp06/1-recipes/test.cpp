std::vector<std::unique_ptr<Material>> _all_possible_materials;
std::vector<Material> _registered_recipes;
std::map<std::string, std::vector<Material *>> _material_from_name;
std::unordered_map<Material, size_t> _inventory;