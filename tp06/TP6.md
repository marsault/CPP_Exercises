# TP6 - bibliothèque standard

## Objectifs

- Se familiariser avec l'utilisation des `unique_ptr`
- Manipuler des pointeurs-observants

## Exercice - Recettes (2h)

Vous allez créer un programme qui vous permet de fabriquer des objets à partir de matériaux suivant une recette.
Par exemple, je pourrais avoir la recette "Caillou Bâton => Marteau", qui nécessite d'utiliser un caillou et un bâton pour produire un marteau.

Certaines recettes implique l'usage d'outils.
Ceux-ci sont considérés comme des matériaux, au même titre que les autres, mais sont restitués à la fin de la recette : "Caillou Marteau => Sable Marteau".

### A. Existant

Le squelette du programme est déjà implémenté.

1. Commencez par le compiler et lancez-le afin de vous familiariser avec son fonctionnement (vous ne devriez pas avoir besoin de lire le code pour cette étape).
Vous devriez rapidement constater qu'à part le parsing des commandes utilisateur, ce programme ne semble pas faire grand chose.

```b
# Configurer le projet dans un dossier de build
cmake -B <chemin_vers_le_dossier_build> -S <chemin_vers_le_dossier_tp6>

# Compiler le programme
cmake --build <chemin_vers_le_dossier_build> --target ex1

# Lancer le programme
<chemin_vers_le_dossier_build>/ex1
```

2.  Voici les fichiers que vous aurez à modifier (et d'autres fichiers seront éventuellement à ajouter.)
    a. Ouvrez le fichier [`ProgramData.hpp`](./1-recipes/ProgramData.hpp) : il contient la classe `ProgramData`, dont chacune des fonctions est appelée par l'une des commandes utilisateur.

    b. Ouvrez maintenant le fichier [`ProgramData.cpp`](./1-recipes/ProgramData.cpp).
    Pourquoi le programme ne fait rien ?

    c. Le fichier [`aliases.hpp`](./1-recipes/aliases.hpp) contient des définitions de types qui servent d'interface entre le frontend (qui vous est donné) et le backend (que vous devez écrire.)  Vous aurez sans doute à les modifier.

    d. Les fichiers [`Material.hpp`](./1-recipes/Material.hpp) et [`Recipe.hpp`](./1-recipes/Recipe.hpp) contiennent des coquilles vident de classes que vous aurez à remplir.


3. Finalement, le programme contient aussi des fichiers que vous n'aurez pas à modifier.\
    a. le fichier [`main.cpp`](./1-recipes/main.cpp) contient la boucle principale du programme.
    
    b. Le fichier [`lib/Actions.hpp`](./1-recipes/lib/Actions.hpp) contient le code des fonctions qui sont appelés par les différentes actions.

    c. Le fichier [`lib/ActionManager.hpp`](./1-recipes/lib/ActionManager.hpp) contient la structure de données permettant de gérer les actions.  **Vous n'avez a priori pas besoin de comprendre comment il fonctionne.**

### B. Matériau

Pour le restant de l'exercice, n'hésitez pas à ajouter les fonctions-membres qui vous vous sembleraient pertinentes, même si on ne vous les demande pas explicitement.

1. Ajouter dans `Material` un attribut `_name` de type `std::string`, qui sera initialisé par un constructeur.
2. Modifiez le contenu de l'`operator<<` acceptant un `Material` afin d'afficher son nom.
3. Faites en sorte qu'à la construction d'un `Material`, on affiche : `"<name> was created"` et qu'à sa destruction, on affiche `"<name> was destroyed"`.
4. Implémentez le contenu de la fonction `ProgramData::register_material` qui permet de déclarer un nouveau matériau. Vous ajouterez un nouvel attribut attribut `ProgramData::_registered_materials` à la classe qui sera un tableau dynamique.\
Relisez le fichier `ProgramData.hpp`. On remarque que l'interface utilise des `const * Material` comme identifiant des matériaux.  A l'intérieur de `_registered_materials`, on stockera donc chaque materiau dans un`std::unique_ptr<Material>` pour garder chaque `Material` à un emplacement fixe en mémoire.\
Pour résumer, `_registered_materials` sera de type `std::vector<std::unique_ptr<Material>>`.
5. Lancez le programme et testez l'action `new mat <name>` plusieurs fois d'affilée, puis quitter le programme avec `quit`.
Assurez-vous via les logs du programme que chaque `Material` créé est détruit une seule et unique fois.
6. Implémentez ensuite la fonction `ProgramData::get_registered_materials`, qui remplit le tableau en paramètre avec les matériaux enregistrés.
Vous pouvez utiliser la fonction-membre `get` de `unique_ptr` pour récupérer un pointeur-observant sur son contenu.
7. Vous pouvez utiliser l'action `load` pour lancer des scripts d'actions stockés dans des fichiers.  Par exemple, testez l'action `load mat`.
Nous fournissons quatre scripts (`mat`, `inv`, `rec` et `prod`) correspondant aux quatre parties de cet exercice.
Pour créer vos propres scripts, utilisez un fichier  `<name>.txt` qui se trouve dans `build`, puis lancez le avec l'action `load`.


### C. Inventaire

1. Implémentez les fonctions `ProgramData::get_material_by_name` et `ProgramData::add_material_to_inventory` qui sont utilisés.\
Pour stocker l'inventaire  on utilisera un attribut `ProgramData::_inventory` de type `MaterialBag` (Rappel: ce type est défini dans `aliases.hpp`).
2. Pour que `ProgramData::get_material_by_name` soit plus efficace, ajouter un attribut `ProgramData::_material_from_name` qui permet d'indexer.
Quel type de la STL doit-on choisir?
3. Implémentez la fonction `ProgramData::get_inventory` qui collecte tous les matériaux dans l'inventaire dans le `MaterialBag` donné en argument.
4. Testez votre code avec l'action `load inv`, éventuellement avec `valgrind` s'il est installé sur votre machine.

### D. Recette

1. Dans la classe `Recipe` trois attributs:
   - `_requirements` de type `MaterialBag`
   -  `_product` de type `const Material&`, et
   - `_id` de type `size_t`.\
     Ce dernier sera un identifiant unique qui correspondra au numéro de la recette (la première recette ayant pour identifiant `1` et non `0`).
2. Implémentez le contenu de l'`operator<<` pour `Recipe`. Celui-ci affichera l'idenfiant de la recette ainsi que sa formule.
Par exemple : `"(1) Eau Sirop => Grenadine"`
3. Implémentez `ProgramData::register_recipe`. 
   On utilisera pour cela un nouvel attribut `ProgramData::_registered_recipes` de type `std::set<Recipe>`.
   A la fin de l'ajout, affichez dans la console `"Recipe <...> has been registered"`
4. Testez que la commande `add rec` fonctionne.
5. Implémentez la fonction `ProgramData::get_all_recipes` et testez que la commande `list rec` fonctionne correctment.
6. Ajoutez plusieurs recettes et listez les.  Que remarque-t-on sur l'ordre d'affichage?  Est-ce que ça aurait été pareil avec un `std::unordered_set<Recipe>` ? avec `std::vector<Recipe>`?
7. Implémentez la fonction `ProgramData::get_recipe_by_id`.  Pour ce faire, regarder les versions (3,4) de [std::set::find](https://en.cppreference.com/w/cpp/container/set/find).
8. Implémentez `ProgramData::unregister_recipe` et testez que cela fonctionne avec l'action `del rec`.
Affichez dans la console `"Recipe <...> is not longer registered"`.
9. Testez votre code avec l'action `load scriptD`, éventuellement avec `valgrind` s'il est installé sur votre machine.


### E. Production

1. Implémentez maintenant `ProgramData::collect_doable_recipes`, qui remplit le tableau passé en paramètre avec des pointeurs-observants sur les recettes dont les matériaux requis sont disponibles dans l'inventaire.
Il est recommandé 
    - de modifier le type `MaterialBag` pour qu'écrire `collect_doable_recipes` ne soit pas horrible
    - de vérifier avec votre chargé de TP que le type que vous avez choisi est le bon
    - de faire des fonctions auxilliaires bien pensées.
2. Testez que la commande `list doable` fonctionne correctement, notamment avec des recettes qui nécessitent plusieurs fois le même matériau (on pourra repartir du script `rec`).
3. Implémentez maintenant le contenu de la fonction `ProgramData::produce`, qui tente de réaliser la recette donnée en argument.
    - S'il n'y a pas assez de matériau: l'inventaire n'est pas modifié.
    - S'il y a assez de matériaux dans l'inventaire: ceux nécessaires sont retirés de l'inventaire et le nouveau matériau créé est ajouté à l'inventaire.
4. Vérifiez que la commande `prod` fonctionne correctement.
5. Testez votre code avec l'action `load scriptE`, éventuellement avec `valgrind` s'il est installé sur votre machine.

## Exercice 2 - CopyablePtr (90 min, bonus) 

Dans cet exercice vous allez implémenter votre propre variante du ` std::unique_ptr`.  
Cela vous permettra de mieux comprendre comment fonctionnent les unique_ptr.

Avant de commencer à coder, voici les instructions pour configurer le projet CMake, compiler le programme et le lancer :
```b
# Configurer le projet dans un dossier de build
cmake -B <chemin_vers_le_dossier_build> -S <chemin_vers_le_dossier_tp6>

# Compiler le programme
cmake --build <chemin_vers_le_dossier_build> --target ex2

# Lancer le programme
<chemin_vers_le_dossier_build>/ex2
```

Vous allez définir une classe `CopyablePtr` qui permettra de stocker une instance de `Object` allouée dynamiquement.  
Contrairement à `std::unique_ptr`, votre classe supportera la copie et allouera dans ce cas une nouvelle instance d'`Object` pour contenir la copie.  

La classe `Object` est prédéfinie de manière à logger chacune des opérations liées à sa durée de vie ou à son contenu.  
Pour chacune des questions, vous décommenterez les instructions associées dans le `main` et vérifierez que vous avez la sortie attendue.  
Si vous ajoutez des fichiers, pensez à modifier le [CMakeLists.txt](CMakeLists.txt).

### A. Fonctions de base

1. Décommentez l'instruction correspondant à la question 1 dans le fichier [main.cpp](2-ptr/main.cpp).  
Vérifiez que le programme compile et qu'il affiche : `"Debut des tests`.

2. Définissez une classe `CopyablePtr` dans le dossier [2-ptr](2-ptr).    
Ajoutez-lui un attribut de type `Object*` ainsi qu'un opérateur d'égalité dont la seconde opérande sera de type `std::nullptr_t` (il s'agit du type du littéral `nullptr`). Cet opérateur vérifiera si l'attribut est null.

3. Ajoutez un constructeur acceptant un paramètre de type entier.  
Celui-ci allouera dynamiquement une instance d'`Object` avec `new`, initialisée avec la valeur passée en paramètre.  Assurez-vous également que les instructions de la question précédente compilent toujours.

4. Vous allez maintenant implémenter l'opérateur de déréférencement, qui vous permettra d'accéder au contenu de votre smart-pointer.  
Voici sa signature : `CopyablePtr::operator*() const`.  
Assurez-vous que cette opération n'engendre aucune copie ou déplacement de `Object` lors du retour de la fonction.

5. Implémentez un operateur d'affectation pour le type `nullptr_t`, qui permettra de vider le pointeur sans provoquer de fuite de mémoire.  
La signature est : `CopyablePtr::operator=(std::nullptr_t)`.

### B. Constructeurs de copie et déplacement

1. Ajoutez un constructeur de copie à votre classe.  
Ce constructeur allouera un nouvel `Object` à partir de l'`Object` contenu dans le pointeur passé en paramètre.

2. Assurez-vous que votre constructeur est aussi capable de copier un `CopyablePtr` vide.

3. Vous allez maintenant implémentez le constructeur de déplacement.
Attention, pour cette opération, on ne veut pas qu'un nouvel `Object` soit alloué.
On souhaite simplement que le pointeur-nu du `CopyablePtr` passé en paramètre soit "transféré" dans le `CopyablePtr` généré par le constructeur.

### C. Affectation par copie

1. On souhaite maintenant gérer la réaffectation par copie des `CopyablePtr`.  
Définissez l'opérateur adéquat et assurez-vous que le code fonctionne comme attendu.

2. Vérifiez maintenant que si le `CopyablePtr` contenait déjà un `Object`, celui-ci est bien détruit avant qu'une nouvelle instance soit créée.  

3. Enfin, assurez-vous que la réaffectation d'un `CopyablePtr` par lui-même ne produise pas d'effets indésirables.

### D. Affectation par déplacement

1. De la même manière que pour la construction par déplacement, vous allez implémenter un opérateur d'affectation par déplacement qui n'allouera aucun nouvel `Object`.  
Le pointeur-nu contenu dans l'instance passé en paramètre sera "volé" par l'instance courante, après avoir détruit l'`Object` que celle-ci contenait préalablement.

2. Vérifiez que la réaffectation d'un `CopyablePtr` par lui-même n'a pas d'effet.

### E. Destruction

Implémentez le destructeur de la classe afin de corriger les fuites de mémoire présentes dans votre programme.  
Utilisez `valgrind` pour vérifier que votre programme ne présente aucun problème de mémoire.

