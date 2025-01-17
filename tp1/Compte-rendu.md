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

1. cf TP

2. La phase de build (compilation) consiste à compiler le fichier en ajoutant les symboles présentes (variable, fonctions, ...) dans la table des symboles et les inclut dans un fichier binaire.
La phase de link (édition des liens) consiste à regrouper depuis les fichiers-objet fournis les instructions nécessaires à son exécution.

3. a. error: 'qqchose' was not declared in this scope  -> il ne sait pas comment l'interpréter pour le traduire en assembleur. (phase build)
b. error: 'qqchose' is not a member of 'std' -> qqchose ne fait pas partie de std ou on n'a pas inclut les headers nécessaires. (phase link)

4. Référence indéfinie, lors de la phase de link, il n'y a pas la définition de la fonction print_hello().
```
g++ -std=c++17 -o hello main.cpp
/usr/bin/ld : /tmp/ccAWngLH.o : dans la fonction « main » :
main.cpp:(.text+0x5) : référence indéfinie vers « print_hello() »
collect2: error: ld returned 1 exit status
```