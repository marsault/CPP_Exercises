# TP8 - Révisions


## Objectifs

- Se rappeler les les conditions des TPs notés
- Lancer les tests unitaires
- Revoir les différentes notions du cours

Voir le fichier `TPNote.md` qui décrit le fonctionnement des TP notés. Il est conseillé de se mettre dans les bonnes conditions pour vous entraîner.


## Dans le TP08

### Exercice 1 - Vrai ou Faux (30 min)

Le premier exercice est un vrai ou faux.

Ouvrez le fichier [ex1/src/qcm.hpp](ex1/src/qcm.hpp).  
Vous devez indiquer pour chaque proposition si celle-ci est vraie (`true`) ou fausse (`false`).  
Attention, une réponse incorrecte peut vous retirer des points, donc laissez le champ vide si vous ne savez pas.

Par exemple, si je sais que Victor a les cheveux courts, mais qu'on ne sait pas si Céline a les cheveux longs, :
```cpp
// Question 1
// Victor a les cheveux longs.
#define ANSWER_1 false

// Question 2
// Céline a les cheveux longs.
#define ANSWER_2
```

Si vous exécutez `./run_tests.sh ex1`, le test associé deviendra vert dès lors que vous aurez répondu à toutes les questions (même si vous avez mal répondu).

### Exerices 2 et 3

Dans les exercices 2 et 3, vous devez coder différentes classes et fonctions afin de faire passer les tests unitaires fournis.  
Avec le framework Catch2, les tests unitaires ont la forme suivante :
```cpp
TEST_CASE("Titre du test")
{
  // Des instructions...
  REQUIRE(/** une assertion **/);

  // D'autres instructions...
  REQUIRE(/** une autre assertion **/);
}
```

Dans un premier temps, il faut réussir à implémenter le code permettant au test de **compiler**.  
La seconde étape est d'adapter ce code afin qu'**il se comporte comme attendu** (c'est-à-dire que les conditions spécifiées dans les `REQUIRE` s'évaluent à `true`).

Pour résoudre un test (par exemple [ex2/tests/01-ptr-alias.cpp](ex2/tests/01-ptr-alias.cpp)), il faut créer les fichiers adéquats (par exemple `ex2/src/alias.hpp`) et y écrire le code pour que le test passe.

Une fois que vous pensez avoir terminé, utilisez `./run_tests.sh ex2-01` pour compiler et exécuter ce premier test.
Si vous avez réussi à le faire passer, passez au test suivant, etc.

### Conseils

1. Attention aux régressions ! Relancez régulièrement l'intégralité des tests de l'exercice avec `./run_tests.sh ex2` pour vous assurez que vos dernières modifications n'ont pas cassé un test qui passait précédement.
2. Ne restez pas bloqué trop longtemps sur la même question. La plupart des tests sont indépendants, donc n'hésitez pas à avancer et à revenir sur ceux qui vous posaient problème s'il vous reste du temps à la fin de la séance.


## Exercice 2 - Petit exercices sur la gestion de la mémoire

Le test `ex2-01` demande de trouver deux types qui ont le comportement attendu. Il faut utiliser des alias et il est inutile de créer de nouvelles classes.

Les questions 1X de cet exercice reposent sur la classe [`Tracker`](ex2/lib/Tracker.hpp) qui est fournie.  Prenez le temps de bien lire le code cette classe avant de commencer à coder.
Le but est de coder une classe `StringInstancePair` qui représente une paire (`std::string`, `Tracker`) tout en satisfaisant un certain nombre de contraintes posées par les tests.


## Exercice 3 - Petit exercice sur l'héritage

L'exercice 3 porte sur l'héritage.  On demande de créer une classe `Base` pet puis deux classes `DerivedInt` et `DerivedString` qui hérite de `Base`.

Là encore, les tests imposent des contraintes et le but est de trouver un moyen de les satisfaire dans les code des classes.
Vérifiez bien à chaque test que vous passez encore les tests précédents.

## Exercice 4 - Modification de classes pour enlever les fuites mémoires et copies inutiles.

L'exercice 4 consiste à modifier les classes Collection et Multimap de façon à ce qu'elles ne produisent plus: ni fuite mémoire, ni de copies inutiles et sans introduire de double-désallocation !