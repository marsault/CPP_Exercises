# TP3 - Cycle de vie

## Objectifs

- Dessiner des graphes d'ownership
- Identifier les dangling-references
- Identifier les relations d'ownership et d'agrégations
- Adapter la signature d'une fonction pour améliorer les performances
- Utiliser des références et des pointeurs-observants dans un programme

## Exercice 1 - Graphes d'ownership (50min)

### Cas A - Copie VS Référence

```cpp
#include <array>

class Driver
{};

class Wheel
{};

class Car
{
public:
    Car(Driver& d)
    : driver { d }
    {}

    Driver&            driver;
    std::vector<Wheel> wheels;
};

int main()
{
    auto driver = Driver {};
    {
        auto car = Car { driver };
        for (auto i=0u; i<4u; ++i)
            car.wheels.emplace_back(Wheel{});


        auto& first_wheel = car.wheels.front();
        auto  last_wheel = car.wheels.back();
        // <-- On se place ici pour la question 1.
    }
    // <- On se place ici pour la question 2.
    return 0;
}
```
1. Voici le graphe d'ownership au premier commentaire.

   ![](images/ex1-a.svg)

   Pourquoi n'y a-t-il pas de relation entre `last_wheel` et `wheels[3]` contrairement à `first_wheel` et `wheels[0]` ?

   > Car `last_wheel ` n'est pas une référence donc `last_wheel` est une copie de `wheels[3]`  

2. a. Quels sont les objets qui ont été détruits quand on arrive au deuxième commentaire ?

    > Le contenu de `car`, `wheels`, les éléments de `wheels` et `last_wheel`.

    b. A-t-on des dangling références? Pourquoi ?

    > Non, on en a pas car toutes les références (`car.driver` et `first_wheel`) ont une durée de vie plus courte (`driver`) ou égale (`first_wheel`) à l'objet référencé.

### Cas B - Pointeurs-observants

```cpp
class Worker
{
public:
    const Worker* manager = nullptr; 
};

int main()
{
    Worker cto;
    {
        Worker boss;
        Worker technician;

        cto.manager = &boss;
        technician.manager = &cto;
        // <-- se place ici pour la question 1.
    }
    // <-- se place ici pour la question 3.
    return 0;
}
```



1. Voici le graphe d'ownership au premier commentaire
   ![](images/ex1-b.svg)

   a. Dans le graphe d'ownership, comment distingue-t-on un pointeur d'une référence ?

   > Le pointeur a une case en trait plein pour signifier que c'est une valeur, éventuellement modifiable (et sur lequel on peut faire de l'arithmetique si on veut vraiment avoir des problèmes).

   b. Comment est représenté un pointeur nul ?

    > Il pointe vers un cercle barré.

2. En termes de code, quelles sont les deux différences principales entre un pointeur-observant et une référence ?

    > Les pointeurs peuvent-être réaffecté et peuvent être nuls.

3. a. Quels sont les objets détruits quand on arrive au deuxième commentaire.

      > L'objet dans `cto` et le pointeur `cto.manager`.

   b. A-t-on des dangling pointeurs? lesquels et pourquoi?
    
      > Oui, `technician.manager` est un dangling pointer.  On lui a affecté une cible dont la durée de vie est plus courte que lui.

   c. Essayer de modifier le code précédent en remplacant les pointeurs par des références pour obtenir des dangling references.
      
      > Ce n'est pas possible sans modifier substanciellement le code car on se base sur le fait qu'on peut avoir des pointeurs nuls et les réaffecter plus tard.   
      Ici, on s'est autorisé à avoir `cto.manager` nul jusqu'à la création de `boss` et son affectation via `cto.manager = &boss;`.
      Si `Worker::manager` était une référence, on **aurait du** l'initialiser au moment où un `Worker` est construit donc `boss` doit être construit avant `cto`.
      Si `boss` existe avant `cto`, et que les deux sont des variables locales,
      la durée de vie de `boss` sera plus longue que celle de `cto`.
      On est obligé d'utiliser le tas, comme dans le code ci-dessous. (On est aussi obligé d'utiliser une autre classe `Manager` pour pouvoir créer `boss` qui n'a pas de manager.)

```cpp
class Manager {};

class Worker
{
public:
    Worker(const Manager& m) : manager{m} {}
private:
    const Manager& manager; 
};

int main()
{
   Manager* boss = new Manager{};
   Worker cto {*boss};
   delete boss;
}
```


### Cas C - Insertions dans un `std::vector`

```cpp
#include <memory>
#include <vector>

class Product
{};

class Client
{
public:
    std::vector<Product> products;
};

int main()
{
    {
        auto client = Client {};
        client.products.push_back(Product{});
        client.products.push_back(Product{});

        auto& first_product = client.products.front();
        // <-- Le graphe d'ownership donné se situe ici

        client.products.push_back(Product{});
        // <-- A la question 1, on dessine le graphe ici
    }
    // <--  On se place ici pour la question 6
    return 0;
}
```

![](images/ex1-c.svg)

Lors d'une insertion, si le buffer mémoire réservé par `std::vector` n'a pas la place de contenir le nouvel élément, alors le contenu du tableau est réalloué dans un tout nouveau buffer de taille suffisante.
Chaque élément est déplacé de son ancienne adresse mémoire vers la nouvelle.

1. Recopier ce graphe et représenter avec une couleur différente les transitions dans le graphe d'ownership après le dernier `push_back` si celui-ci déclenchait une réallocation mémoire.


![](images/ex1-c-depl.svg)




2. Quel problème relève-t-on dans le graphe ?

    > `first_product` est maintenant une dangling reference car `products[0]` a été déplacé.

3. Modifiez le code ci-dessus afin que `Client::products` contienne des pointeurs.

    > Voici le code avec les changements sont mis en évidence.
    ```cpp
    class Product
    {};

    class Client
    {
    public:
        //                 v
        std::vector<Product*> products;
    };

    int main()
    {
        {
            auto client = Client {};
            //                        vvv
            client.products.push_back(new Product{});
            client.products.push_back(new Product{});
            //                        ^^^
            //                    vv                       v
            auto& first_product = *(client.products.front());

            client.products.push_back(new Product{});
            //                        ^^^
        }
        return 0;
    }
    ```

4. Redessinez le graphe d'ownership de la question 1 avec la transition, mais en prennant en compte vos changements dans le code.  

![](images/ex1-c-indir.svg)

5. Avez-vous toujours le problème relevé à la question 2 ?

    > Non car seul les pointeurs ont bougé avec la réallocation, pas les objets pointés. En particulier, `first_product` est toujours une référence vers l'objet pointé par le premier élément de `client.products`.

6. Suivant votre réponse à la question 3, ceci a potentiellement créé un autre problème qui se révèle quand on arrive au troisième commentaire.

    > Les objets pointés par les éléments de `Client::products` ne sont jamais désinstanciés.  On le voit sur le graphe car aucune flèche en trait plein  n'arrive vers eux.

7. Si besoin, modifier le code dans `Client` pour le résoudre.

    > On veut que `Client` continue d'own les objets pointés par les pointeurs dans `products`.
    ```c++
    class Client
    {
    public:
        std::vector<Product*> products;

        // Ajout du destructeur de Client
        ~Client() { 
            for (auto ptr : products)
                delete ptr;
        }
    };



## Exercice 2 - La meilleure signature (15min)

1. Remplacez les `XX` par les bons types, de manière à ce que le programme compile et affiche `10 42`.

```cpp
#include <iostream>

XX add(XX a, XX b)  // int add(int a, int b)
{
    return a + b;
}

XX add_to(XX a, XX b) // void add_to(int& a, int b)  
{
    a += b;
}

int main()
{
    int x = 10;
    int y = add(x, x);
    add_to(y, 22);
    std::cout << x << " " << y << std::endl;
    return 0;
}
```



2. Modifiez si besoin les types dans les prototypes des fonctions ci-dessous pour que le passage soit le plus efficace et le plus sécurisé possible.  
Vous pouvez vous aider des commentaires pour comprendre comment les fonctions utilisent leurs paramètres.
```cpp
// Return the number of occurrences of 'a' found in string 's'.
int count_occurrences(char a, std::string s);

// Solution:
// -> int count_occurences(char a,  const std::string& s)
//                         ^^^^^^   ^^^^^^^^^^^^^^^^^^
//     une copie coûte moins cher | ici on utilise une référence pour
//              que de référencer | éviter une copie et const car
//                                | on a pas besoin de modifier


// Update function of a rendering program.
// - dt (delta time) is read by the function to know the time elapsed since the last frame.
// - stores in *b whether anything actually changed.
void update_loop(const float& dt, bool* b);

// Solution:
// En C++, ce n'est pas très usuel de renvoyer 
// des valeurs dans un argument passé en 
// référence et encore plus quand l'argument
// est passé en pointeur
// vvvv
// bool update_loop(float dt)
//                  ^^^^
//    une copie coûte moins cher qu'une référence


// Return whether all numbers in 'values' are positive.
// If there are negative values in it, fill the array 'negative_indices_out' with the indices
// of these values and set its size in 'negative_count_out'.
// ex: auto res = are_all_positive({ 1, -2, 3, -4 }, negative_indices, negative_count);
//    -> res is false, since not all values are positive
//    -> negative_indices contains { 1, 3 } because values[1] = -2 and values[3] = -4
//    -> negative_count is 2
bool are_all_positives(std::vector<int> values, int negative_indices_out[], size_t& negative_count_out);

// Solution:
// std::vector<size_t> are_all_positives(std::vector<int> values);
// ^^^^^^^^^^^^^^^^^^^
// Ici le prototype de base renvoie pleins d'informations n'importe comment 
// alors que tout est contenu dans un simple std::vector


// Concatenate 'str1' and 'str2' and return the result.
// The input parameters are not modified by the function.
std::string concatenate(char* str1, char* str2);

//Solution:
// std::string concatenate(const std::string& str1, const std::string& str2);
// Sans raison valable, on n'utilise pas les types C
```

## Exercice 3 - Gestion des resources (55min)

Vous allez créer un logiciel permettant de gérer les salariés de votre entreprise.

Dans votre logiciel, vous devez connaître pour chaque salarié :
- son nom et prénom,
- son salaire mensuel,
- les autres salariés dont il est manager.

Chaque salarié travaille pour un seul et unique département (la R&D, le marketing, etc).

En tant que chef d'entreprise, vous voulez utiliser ce logiciel pour réaliser les actions suivantes :
1. lister tous les salariés,
2. lister tous les départements,
3. lister les personnes appartenant à un département précis,
4. lister tous les managers,
5. lister les subordonnés d'un manager,
6. embaucher un nouveau salarié,
7. licencier un salarié,
8. changer un salarié de département,
9. augmenter le salaire d'une personne,
10. afficher la somme totale payée pour les salaires par département.

### 1. Architecture (15min)

Dans votre programme, vous aurez les classes suivantes :
- `HRSoftSystem` : représente le système et toutes les données sur lesquelles il opère
- `Employee` : représente un employé
- `Department` : représente un département

On vous propose trois architectures différentes pour le programme :

**Architecture A**

![](images/ex3-a.svg)

**Architecture B**

![](images/ex3-b.svg)

**Architecture C**

![](images/ex3-c.svg)

Pour chacune d'entre elles, vous indiquerez les opérations que le programme devrait effectuer pour satisfaire chacun des besoins cités plus haut, sans jamais introduire de dangling-reference.


### 3. Implémentation du système (30min)

La fonction `main` de `hrsoft-tests` se trouve à l'intérieur de [HRSoftTests.cpp](3-hrsoft/HRSoftTests.cpp).  
Ce programme instancie les mêmes données que celles présentées dans les schémas de la partie 1.

1. Commencez par prendre connaissance de [HRSoftTests.cpp](3-hrsoft/HRSoftTests.cpp) ainsi que des fichiers contenus dans le dossier [HRSoft](3-hrsoft/HRSoft).  
Pour quelle raison le programme utilise-t-il des `std::list` plutôt que des `std::vector` pour stocker les départements et les employés ?  
Si vous ne trouvez pas, remplacez les `list` par des `vector` et lancez le programme en mode Debug pour observer le comportement.
En particulier, utilisez le debugger pour surveiller le contenu de `rd_dpt`.

2. Implémentez la fonction `print_employees` dans la classe `Department` (notez que `operator<<` est déjà fourni pour `Employee`).  
Faites de même pour `print_all_departments` et `print_all_employees` dans la classe `HRSoftSystem`.  
Décommentez les instructions correspondantes dans [HRSoftTests.cpp](3-hrsoft/HRSoftTests.cpp) pour vérifier que tout fonctionne.

3. Implémentez maintenant le contenu de la fonction `Employee::add_subordinate` et définissez la fonction-membre `print_subordinates`.  
Vérifiez que tout fonctionne après avoir décommenté les instructions correspondantes dans le `main`.

4. Définissez maintenant la fonction `remove_employee` de la classe `System`. N'hésitez pas à ajouter d'autres fonctions dans les autres classes si vous en avez besoin.  
Prenez bien garde à ne pas laisser de pointeurs-observants sur l'employé retiré du système.
Décommentez les dernières instructions du `main` pour vous assurer que tout fonctionne.

### 4. (Bonus) Implémentation de HRSoft (1h30)

1. Dans l'onglet CMake, modifiez la cible d'exécution pour `hrsoft`. La fonction `main` de ce programme se trouve à l'intérieur de `3-hrsoft/HRSoftMain.cpp`.

2. Finalisez l'implémentation du programme afin qu'il supporte tous les besoins demandés :
    - la commande `"d market"` permet d'ajouter un département `market`,
    - la commande `"l"` lister tous les départements,
    - la commande `"e dep toto 1250 tata"` permet d'ajouter un employé `toto` payé 1250€ ayant pour manager `tata` au département `dep`,
    - la commande `"k"` permet de lister tous les salariés,
    - la commande `"f toto"` permet de supprimer l'employé nommé `toto`,
    - la commande `"n market"` permet de lister tous les salariés du département `market`,
    - la commande `"m"` permet de lister tous les managers,
    - la commande `"m tata"` permet de lister tous les subordonnés de `tata`,
    - la commande `"t toto r&d"` permet de transférer l'employé `toto` au département `r&d`,
    - la commande `"r toto 200"` permet d'augmenter le salaire de `toto` de 200€,
    - la commande `"s"` permet d'afficher pour chaque département la somme des salaires des employés qu'il contient.

Notez bien que les fonctions `parse_name` et `parse_salary` permettent de récupérer les arguments entrés par l'utilisateur.
