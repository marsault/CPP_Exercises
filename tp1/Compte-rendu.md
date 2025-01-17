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

