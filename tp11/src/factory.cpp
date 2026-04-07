#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Liste des entitées à construire
std::string desc = R"(Object
Person
Dog
Inexistent
Cat
Tree
House
Athanase)";

class Entity
{
public:
  virtual void print() const = 0;
};

class Factory
{
public:
  // using Builder =

  template <typename TDerivedEntity>
  void register_entity(std::string)
  {}

  std::unique_ptr<Entity> build(std::string) const { return nullptr; }

private:
  // ...
};

class Object : public Entity
{
public:
  void print() const override { std::cout << "Object" << std::endl; }
};

class Tree : public Object
{
public:
  void print() const override { std::cout << "Arbre" << std::endl; }
};

class Person : public Entity
{
public:
  explicit Person(std::string name)
      : _name{std::move(name)}
  {}

  void print() const override { std::cout << "Person named " << _name << std::endl; }

  void set_name(std::string name) { _name = std::move(name); }
  const std::string& get_name() const { return _name; }

private:
  std::string _name;
};

class Animal : public Entity
{
public:
  explicit Animal(std::string species)
      : _species{std::move(species)}
  {}

  explicit Animal(std::string species, std::string name)
      : _species{std::move(species)}
      , _name{std::move(name)}
  {}

  void print() const override
  {
    std::cout << "Animal of species " << _species;
    if (_name != "")
      std::cout << " named " << _name;
    std::cout << std::endl;
  }

private:
  std::string _species;
  std::string _name;
};

int main()
{
  Factory factory;
  // factory.register_entity<Object>("Object");
  // ...


  // Vous n'avez rien à modifier en dessous de cette ligne !
  std::vector<std::pair<std::string, std::unique_ptr<Entity>>> entities;

  std::stringstream s;
  s << desc;
  while (!s.eof()) {
    std::string e;
    s >> e;

    auto o = factory.build(e);
    entities.emplace_back(std::move(e), std::move(o));
  }

  for (const auto& e : entities) {
    std::cout << "In:  " << e.first << std::endl;
    std::cout << "Out: ";
    if (e.second != nullptr)
      e.second->print();
    else
      std::cout << "nullptr" << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
