# TP5 - Copie et déplacement

## Objectifs

- Identifier les l-values et les r-values
- Comprendre le mécanisme du déplacement
- Définir un constructeur de copie
- Définir un constructeur de déplacement
- Définir un opérateur d'assignation par copie
- Définir un opérateur d'assignation par déplacement

## Exercice 1 - L-value ou R-value ? (30 min)

1. Identifiez si les expressions ci-dessous sont des l-values ou des r-values et justifiez.  

a. `i` est un `int`  
```cpp
4          // => r-value
4 + i      // => r-value
i          // => l-value
i = 4      // => l-value
i == 4     // => r-value
```

b. `vec` est un `std::vector<char>`
```cpp
vec[5]                          
// => l-value

vec                             
// => l-value

vec.pop_back()                  
// => rien ! (retourne void)

std::vector { 'a', 'b', 'c' }   
// => r-value

vec.emplace_back('d')              
// => l-value

std::move(vec)                  
// => r-value
```

c. `ptr` est un pointeur de `int`
```cpp
ptr + 3     
// => r-value

*(ptr + 3)  
// => l-value

*ptr + 3    
// => r-value
```

d. `str` est une `std::string`
```cpp
std::string { "aaaa" }  
// => r-value

str                     
// => l-value

str + "aaaa"            
// => r-value

str += "aaaa"           
// => l-value
```

2. Supposons que vous ayiez l'instruction : `auto inst = Class { expr };`.  
Quelles sont les deux conditions pour que le constructeur de copie soit appelé ?  
Même question pour le constructeur de déplacement ?

Solution: 
- `expr` doit être de type `Class&` ou `const Class&`
- La classe `Class` doit effectivement avoir un constructeur de copie (possiblement avec une implémentation par défaut)

## Exercice 2 - Minimisons les copies du tp02 (45 min)

Cet exercice est simple. Nous avons repris une solution du tp02 (un peu amélioré) dans lequel quasiment toutes les fonctions passent leurs argument par valeur. Il n'y a donc aucune fuite mémoire, mais le code fait des copies (notamment de `Card`) sans arrêt.\
Votre mission est de faire en sorte qu'il continue de fonctionner pareil, mais sans jamais ne faire aucune copie de `Card` et sans créer de fuite mémoire.

Onn utilise la classe `Tracker` pour suivre les copies au fil du code.

1. Ouvrez le fichier `Tracker.hpp` et lisez le.  

2. Pour chacun des 6 premiers constructeurs/opérateurs/Destructeurs de `Tracker`, écrivez leur nom en commentaire au dessus.

3. Quelle est la règle des `0/3/5` et est-ce que `Tracker` la suit?

Pour traquer les instances de `Card`, on utilise le fait que `Card` possède un attribut de type `Tracker`, qui sera donc:
- construit quand une `Card` est construite;
- copié quand une `Card` est copiée;
- déplacé quand une `Card` est déplacée.

Pour ne pas casser notre exercice, faire en sorte que `Card` continue de suivre la règle des 0!

Regarder maintenant le `main.cpp`.  Il y a des appels à `assert_no_copy` et `assert_mem_count` qui vérifient le nombre de copie et de `Card` en mémoire à la fin du code. Vous pouvez rajouter des `assert_no_copy` et des `assert_mem_count` pour vous aider à débugguer la mémoire. 
Hormis cela, vous n'avez la plupart du temps qu'à modifier les prototypes des fonctions et comment elles sont appelées.

4. A vos claviers: 
   - `mkdir build && cd build && cmake ..` pour faire le Makefile
   - `make ex2 && ./ex2 10` pour compiler et lancer 10 tours de bataille.

## Exercice 3 - Implémentations de listes chaînées 
