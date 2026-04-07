#include <functional> // std::function
#include <iostream>
#include <map>
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
  virtual ~Entity() = default;
};

class Factory
{
public:
  // exercice 1.1.1: comme Factory::build plus bas renvoie un std::unique_ptr<Entity>, on utilise
  // également ce type de retour ici plutôt qu'un simple Entity
  using Builder = std::function<std::unique_ptr<Entity>()>;

  // version originale:
  // template <typename TDerivedEntity>
  // void register_entity()

  // version modifiée:
  template <typename TDerivedEntity, typename... TArgs> /* 1.3.3: ajout de template variadique*/
  //                   1.1.3: rajout de id    1.1.3: rajout des arguments TArgs
  void register_entity(const std::string& id, TArgs&&... args)
  {
    // exercice 1.1.3: on rajoute à la map la clé id, et la valeur associée est une lambda qui
    // invoquera le constructeur associé
    /*
    _builders.emplace(
        id,
        []()
        {
            return std::make_unique<TDerivedEntity>();
        }
    );
    */
    // exercice 1.3.3: il faut maintenant transmettre les paramètres variadiques au constructeur
    _builders.emplace(id,
                      [&args...]() // ne pas oublier l'expansion ici ...
                      {
                        return std::make_unique<TDerivedEntity>(
                            std::forward<TArgs>(args)...); // ... et là
                      });
  }

  std::unique_ptr<Entity> build(const std::string& id) const
  {
    // exercice 1.1.4: cherchons d'abord id pour éviter les plantages si _builders ne la
    // contient pas
    auto it = _builders.find(id);

    if (it != _builders.end())
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

class House : public Object
{
public:
  explicit House(Person& owner)
      : _owner{owner}
  {}

  void print() const override { std::cout << "House owned by " << _owner.get_name() << std::endl; }

private:
  Person& _owner;
};

int main()
{
  Factory factory;
  // exercice 1.2: la sortie est bien:
  // Object
  // Arbre
  factory.register_entity<Object>("Object");
  factory.register_entity<Tree>("Tree");

  // exercice 1.3.1: le programme ne compilera pas avant d'avoir adapté register_entity
  // une fois l.3.2 terminé, la sortie devient:
  // Object
  // Person named Jean
  // Arbre
  factory.register_entity<Person>("Person", "Jean");


  // exercice 1.3.3: la sortie devient:
  // Object
  // Jean
  // Animal of species dog
  // Animal of species cat
  // Arbre
  factory.register_entity<Animal>("Dog", "dog");
  factory.register_entity<Animal>("Cat", "cat");

  // exercice 1.4: la sortie devient
  // Object
  // Jean
  // Animal of species dog
  // Animal of species cat
  // Arbre
  // House owned by Picsou
  Person proprio("Gripsou");
  factory.register_entity<House>("House", proprio);
  proprio.set_name("Picsou");


  // exercice 1.5: la sortie devient
  // Object
  // Jean
  // Animal of species dog
  // Animal of species cat
  // Arbre
  // House owned by Picsou
  // Animal of species cat named Athanase
  factory.register_entity<Animal>("Athanase", "cat", "Athanase");


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
