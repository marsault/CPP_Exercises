# TP1: Introduction

## Exercice 1:

1. à 3.
```
g++ -std=c++17 -o bonjour main.cpp  
$ ./bonjour
Entre ton nom: Dounya
Bonjour Palluche La Falluche !
$ ./bonjour
Entre ton nom: tototatatititutublabliblu #plus de 20 caractères
Bonjour Palluche La Falluche !
```

4. Il faut utiliser std::string. Avec plus de 20 caractères cela conserve les 20 caractères entrés et ignore les autres.

```
g++ -std=c++17 -o hello main2.cpp
$ ./hello
Entre ton nom: Dounya
Dounya
$ ./hello
Entre ton nom: tototititututatablabliblu
tototititututatablab
```

## Exerccie 2:

1. Le code initialise un tableau dynamique d'entiers, on commence par afficher ses éléments, on le parcours et on y ajoute le double de ces entiers pour les afficher après modification. Mais on utilise des chaines de caractères.

2. à 10.
```
g++ -std=c++17 -o values main.cpp
$ ./values
Le tableau contient les valeurs : 1 3 3 7
 1 3 3 7 2 0 -1208008672 43808
$ g++ -std=c++17 -o value main2.cpp
$ ./value
Le tableau contient les valeurs : 1 3 3 7
 1 3 3 7 2 0 708886560 44090

 g++ -std=c++17 -o value main2.cpp
$ ./value
Le tableau contient les valeurs :
First element: 1
Last element: 7
 1 3 3 7
 1 3 3 7 2 6 6 14

 ./value
4 5 6 9 7 0
Le tableau contient les valeurs :
First element: 4
Last element: 7
 4 5 6 9 7
 4 5 6 9 7 8 10 12 18 14

 ./value         
4 8 23 -5 0
Le tableau contient les valeurs :
First element: 4
Last element: 8
 4 8
 4 8 8 16

 ./value
4 7 8 5 "Dounya" 4 0
Ceci n'est pas un entier !
Le tableau contient les valeurs :
First element: 4
Last element: 0
```

## Exercice 3:

