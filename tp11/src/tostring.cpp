#include <array>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Définition du type général
template <unsigned N>
struct priority_tag : priority_tag<N - 1>
{};
// Spécialisation de priority_tag pour N=0
template <>
struct priority_tag<0>
{};

priority_tag<10> priority_highest_value;


template <typename T>
std::string to_string(T&& data, priority_tag<0>)
{
  std::stringstream ss;
  ss << "<" << typeid(data).name() << ": " << &data << ">";
  return ss.str();
}

// Ecrire les spécialisations ici
// ...

template <typename T>
std::string to_string(T&& data);

template <>
std::string to_string(std::string& data)
{
  return data;
}

template <>
std::string to_string(std::string&& data)
{
  return data;
}


// Ici, on shadow, on ne spécialise pas
std::string to_string(char const* const& data)
{
  return data;
}


template <typename T>
auto to_string(T&& data, priority_tag<6>) -> decltype(std::to_string(data))
{
  return std::to_string(data);
}

template <typename T>
auto to_string(T&& data, priority_tag<5>) -> decltype(std::declval<std::ostream>() << data,
                                                      std::string{})
{
  std::stringstream ss;
  ss << data;
  return ss.str();
}

template <typename T>
auto to_string(T&& data, priority_tag<6>) -> decltype(data.to_string())
{
  return data.to_string();
}

template <typename T>
auto to_string(T&& data, priority_tag<2>) -> decltype(data.begin(), std::string{})
{
  std::stringstream ss;
  ss << "{";
  bool first = true;
  for (const auto& e : data) {
    if (first)
      first = false;
    else
      ss << ", ";
    ss << to_string(e);
  }
  ss << "}";
  return ss.str();
}

template <typename T, size_t i>
std::string to_string(std::array<T, i>&& data)
{
  std::stringstream ss;
  ss << "[";
  bool first = true;
  for (const auto& e : data) {
    if (first)
      first = false;
    else
      ss << ", ";
    ss << to_string(e);
  }
  ss << "]";
  return ss.str();
}


template <size_t i, typename... Args>
void to_string_tuple(std::stringstream& ss, const std::string& s, const std::tuple<Args...>& tuple)
{
  if constexpr (i < std::tuple_size_v<std::tuple<Args...>>) {
    ss << s << to_string(std::get<i>(tuple));
    to_string_tuple<i + 1>(ss, ", ", tuple);
  }
}

template <typename... Args>
std::string to_string(std::tuple<Args...>&& tuple)
{
  std::stringstream ss;
  to_string_tuple<0u, Args...>(ss, "(", tuple);
  ss << ")";
  return ss.str();
}


template <typename T>
std::string to_string(T&& data)
{
  return to_string(std::forward<T>(data), priority_highest_value);
}


// Vous n'avez rien à modifier en dessous de cette ligne !
class Empty
{};

class Streamable
{
public:
  friend std::ostream& operator<<(std::ostream& out, const Streamable& s)
  {
    return out << "Streamable @" << &s;
  }
};

class Convertible
{
public:
  std::string to_string() const
  {
    std::stringstream ss;
    ss << "Convertible @" << this;
    return ss.str();
  }
};

class Both : public Streamable, public Convertible
{};

template <typename T>
void print_test(std::string type, T&& value)
{
  std::cout << type << std::endl;
  std::cout << "** Error: value is not a std::string" << std::endl;
}

void print_test(std::string type, std::string value)
{
  std::cout << type << std::endl;
  std::cout << " -> " << value << std::endl;
}

int main()
{
  // De base on a l'adresse des objets
  print_test("Vide", to_string(Empty{}));

  // Q1: on veut gérer les chaines de caractères
  std::string truc{"Truc"};
  print_test("std::string (L-value)", to_string(truc));
  print_test("std::string (R-value)", to_string(std::string{"Machin"}));
  print_test("char*", to_string("Bidule"));

  // Q2: Puis les conversions simples fournies par la fonction std::to_string
  print_test("int", to_string(3));

  // Q4: Si un objet présente une fonction de conversion, on l'utilise
  print_test("Convertible", to_string(Convertible{}));

  // Q5: S'il est streamable (en implémentant l'opérateur << sur ostream), idem
  print_test("Streamable", to_string(Streamable{}));

  // Commenter cette ligne si elle bloque la compilation trop tot dans le TP
  print_test("Both", to_string(Both{}));

  // Q6: On s'attaque maintenant aux conteneurs
  print_test("std::vector<int>", to_string(std::vector<int>{1, 2, 3, 4}));
  print_test("std::vector<std::vector<int>>",
             to_string(std::vector<std::vector<int>>{std::vector<int>{0, 1, 2, 3},
                                                     std::vector<int>{4, 5, 6, 7}}));
  print_test("std::list<std::string>", to_string(std::list<std::string>{"Hello", "World", "!"}));

  // Q7: avec une spécialisation pour les std::array
  print_test("std::array<int, 4>", to_string(std::array<int, 4>{1, 2, 3, 4}));

  // Q8: tuple
  print_test("std::tuple<int, std::string, float>",
             to_string(std::tuple<int, std::string, float>{1, "2", 3.f}));


  return 0;
}
