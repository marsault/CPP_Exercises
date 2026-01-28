# Conditions de TP Noté

Dans ce fichier sont décrites les conditions dans lesquels se dérouleront les TP notés.

### Documentation

Vous aurez accès à différentes ressources pour vous débloquez si nécessaire pendant la séance :
- [le cours en ligne](https://monge.univ-eiffel.fr/~marsault/cpp/cours/),
- [un miroir local de cppreference](https://monge.univ-eiffel.fr/~marsault/cpp/cours/ref/en/)
  * vous pouvez aussi accéder à cette documentation avec la commande `devhelp`

Il est recommandé de ne pas utiliser internet lors de ce TP **pour vous mettre en condition de TP noté**.

### Archive 

Vous trouverez dans `${HOME}/SUJET` deux fichiers:
- une archive qui sera appelé `tpn1.zip`, `tpn2.zip`, etc.
- un script `prepare_station.py`

**Pour vous mettre en condition de TP noté**, créer un répertoire `SUJET` dans votre HOME et placez-y 
- le fichier `tp3.zip` 
- le fichier `prepare_station.py`
Ils se trouvent dans `large-files` sur le dépôt git

## Lancer le script `prepare_station.py`

Avant le début de l'examen, on vous demandera de prendre place à vos machines, de vous connecter, d'ouvrir un terminal dans répertoire `${HOME}/SUJET` et de lancer la commande:
```bash
python3 prepare_station.py
```

Ce script: 
- extrait l'archive dans `${HOME}/SUJET`
- copie la base de code dans `${HOME}/EXAM`
- configure VS Codium
- lance CMAke depuis le répertoire `/tmp/CPP/build`.  Attention, il faudra donc ce mettre dans ce répertoire pour lancer les commandes de compilations de de test.
- Compile la bibliothèque Catch2 qu'on utilise pour les tests unitaires.

Tout ceci a pour but d'éviter (une partie des) **lags habituels du mode exam**.

Si vous fermez VS Codium ou que vous devez relancer CMake pendant le TP noté, il faudra le relancer avec la commande `prepare_station.py`

## Contenu du dossier

Le dossier du TP noté sera extrait dans `${HOME}/EXAM/`.  Il ne faudra travailler que dans ce répertoire, les autres répertoires ne nous serons pas visibles après.

Il sera structuré à peu près de la même manière que le dossier de ce TP4.
- `cmake`: Dossier contenant des fichiers de configuration pour CMake. **A ne pas modifier.**
- `ex<N>`: le code de l'exercice n°N
  - `src`: Dossier où coder. Il y aura parfois du code fourni et vous devrez le modifier.
    - `sandbox.cpp`: Un fichier spécial, que vous pouvez utiliser pour compiler un binaire `ex<N>-sandbox` pour tester votre code indépendamment du système de test.  Ce fichier ne sera pas considéré par la correction.
  - `tests`: Dossier où se trouve les fichiers contenant les **tests unitaires** à faire passer.
   **A ne pas modifier.**
  - `lib`: Ce dossier optionnel comprend des fichiers de code fournit.
   **A ne pas modifier.**
  - `extern`: contient des librairies externes, notamment la librairie Catch2 pour les tests unitaires.
- `CMakeLists.txt`: le fichier de configuration pour CMake. **A ne pas modifier.**
- `TPN<x>.md` et/ou `TPN<x>.pdf`: le sujet du TP noté.

Pour résumer:
- Vous devrez coder dans le répertoire `src` de chaque exercice.
- Vous devrez consulter les répertoires `lib` et `tests` de chaque exercice, mais il ne faudra en aucun cas modifier les fichiers.  Si vous arrivez à faire passer un test en le réécrivant, vous n'aurez pas les points !
- Vous n'avez pas à vous préoccupez des autres fichiers, ils sont là pour faire en sorte que tout fonctionne.

## Lancer les tests 

### Lancer plusieurs tests avec `run_tests.sh`

Enfin, vous pouvez compiler les tests et les exécuter à partir du script `run_tests.sh` généré dans votre dossier de `/tmp/CPP_EXAM/build`
```sh
# Lance la compilation et l'exécution de tous les tests unitaires
./run_tests.sh

# Lance la compilation et l'exécution des tests contenant le pattern donné
./run_tests.sh <pattern>

# Par exemple
./run_tests.sh ex2      # => tous les tests de l'exercice 2
./run_tests.sh ex2-1    # => exercice 2, tests 10 à 19
./run_tests.sh ex2-23   # => exercice 2, test 23 uniquement
```

Le script `run_tests.sh` a quelques options utiles:

```sh
./run_tests.sh -h   # l'option -h affiche l'aide

./run_tests.sh -q   # l'option -q n'affiche pas la sortie des tests, 
                       # elle est utile pour avoir une résumé de ce qu'on a fait
                       # (pas de non-regression)

./run_tests.sh -s   # l'option -s : le programme s'arrête au premier test échoué
                       # elle est utile quand on progresse dans un exercice
```


### Compiler et lancer un test unique avec `make`

On peut compiler et lancer un test spécifique directement avec make:
```sh
make ex2-01-phone-number     # Compile le test 01-phone-number de l'exercice 2

make run-ex2-01-phone-number # Lance le test et fait une backup des sources s'il est réussi  (voir ci-dessous)

./ex2-01-phone-number        # Lance le test, mais ne fait **pas** de backup  
                             # des sources
```
(On rappelle que dans un terminal, on peut utiliser `TAB` pour completer le nom des cibles de make.)


### Sauvegarde automatique

Chaque fois que vous réussirez à faire passer un test unitaire, les fichiers-sources concernés seront sauvegardés dans le dossier [backup](backup).  
Ainsi, si vous vous rendez compte que vos dernières modifications ont cassé votre code, vous pourrez retrouver la dernière version fonctionnelle de vos fichiers dans ce dossier.