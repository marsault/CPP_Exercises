#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <functional> // std::function
#include <map>

// Liste des entitées à construire
std::string desc = R"(Object
Person
Dog
Cat
Tree
House
)";

class Entity
{
public:
    virtual void print() const = 0;
};

class Factory
{
public:
    // exercice 1.1.1: comme Factory::build plus bas renvoie un std::unique_ptr<Entity>, on utilise
    // également ce type de retour ici plutôt qu'un simple Entity
    using Builder = std::function<std::unique_ptr<Entity>()>;

    template <typename TDerivedEntity>
    // void register_entity(const std::string& id)
    void register_entity(const std::string& id) /* 1.1.3: rajout de id */
    {
        // exercice 1.1.3: on rajoute à la map la clé id, et la valeur associée est une lambda qui
        // invoquera le constructeur associé
        _builders.emplace(
            id, 
            []() 
            {
                return std::make_unique<TDerivedEntity>();
            }
        );
    }

    std::unique_ptr<Entity> build(const std::string& id) const 
    { 
        // exercice 1.1.4: cherchons d'abord id pour éviter les plantages si _builders ne la 
        // contient pas
        auto it = _builders.find(id);

        if(it != _builders.end())
            return it->second();

        return nullptr; 
}

private:
    // exercice 1.1.2: les identifiants étant des chaînes, d'après la signature de Factory::build,
    // il nous faudra une map pour réaliser l'association
    std::map<std::string, Builder> _builders;
};

class Object : public Entity
{
public:
    void print() const override { std::cout << "Object" << std::endl; }
};

class Tree : public Object
{
public:
    void print() const override { std::cout << "Tree" << std::endl; }
};

class Person : public Entity
{
public:
    explicit Person(std::string name)
        : _name { std::move(name) }
    {}

    void print() const override { std::cout << _name << std::endl; }

    void               set_name(std::string name) { _name = std::move(name); }
    const std::string& get_name() const { return _name; }

private:
    std::string _name;
};

class Animal : public Entity
{
public:
    explicit Animal(std::string species)
        : _species { std::move(species) }
    {}

    void print() const override { std::cout << _species << std::endl; }

private:
    std::string _species;
};

class House : public Object
{
public:
    explicit House(Person& owner)
        : _owner { owner }
    {}

    void print() const override { std::cout << "House owned by " << _owner.get_name() << std::endl; }

private:
    Person& _owner;
};

int main()
{
    Factory factory;
    // exercice 1.2: la sortie est bien Object, suivi de Tree
    factory.register_entity<Object>("Object");
    factory.register_entity<Tree>("Tree");

    std::vector<std::unique_ptr<Entity>> entities;

    std::stringstream s;
    s << desc;
    while (!s.eof())
    {
        std::string e;
        s >> e;

        entities.emplace_back(factory.build(e));
    }

    for (const auto& e : entities)
    {
        if (e != nullptr)
        {
            e->print();
        }
    }

    return 0;
}
