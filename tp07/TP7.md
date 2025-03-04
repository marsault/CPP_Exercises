# TP7 - Polymorphisme

## Objectifs

- Définir des classes-filles
- Redéfinir le comportement d'une fonction-membre virtuelle
- Assurer la bonne destruction des instances de classes polymorphes 

## Exercice 1 - Appels polymorphes (20min)

Pour chacun des appels ci-dessous, déterminez le type dynamique et le type statique des instances sur lesquels l'appel est réalisé.  
Déduisez-en la fonction qui sera appelée au moment de l'exécution du programme.

```cpp
#include <iostream>

class Animal
{
public:
    virtual void move() { std::cout << "Moving!" << std::endl; }

    void type() const { std::cout << "Animal" << std::endl; }
};

class Carnivore
{
public:
    void can_eat_meat() const { std::cout << "Yum!" << std::endl; }
    void can_eat_plant() const { std::cout << "Berk!" << std::endl; }
};

class Herbivore
{
public:
    virtual void can_eat_meat() const { std::cout << "Berk!" << std::endl; }
    virtual void can_eat_plant() const { std::cout << "Yum!" << std::endl; }
};

class Bird: public Animal, public Carnivore, public Herbivore
{
public:
    void move() const { std::cout << "Flying!" << std::endl; }
    void type() { std::cout << "Bird" << std::endl; }

    void can_eat_plant() { std::cout << "Miam!" << std::endl; }
};

class Tiger: public Animal, public Carnivore
{
public:
    void move() override { std::cout << "Running!" << std::endl; }
    void type() const { std::cout << "Tiger" << std::endl; }
    
    void can_eat_meat() const { std::cout << "Miam!" << std::endl; }
};

int main()
{
    Tiger tiger;
    Animal& tiger_as_animal = tiger;
    Carnivore& tiger_as_carn = tiger;

    Bird bird;
    Animal& bird_as_animal = bird;
    Herbivore& bird_as_herb = bird;
    Carnivore& bird_as_carn = bird;

    tiger.move();                  // I1
    tiger_as_animal.move();        // I2

    bird.move();                   // I3
    bird_as_animal.move();         // I4

    bird.can_eat_plant();          // I5
    bird_as_herb.can_eat_plant();  // I6
    bird_as_carn.can_eat_plant();  // I7

    tiger.can_eat_plant();         // I8
    tiger.can_eat_meat();          // I9
    tiger_as_carn.can_eat_meat();  // I10

    bird.type();                   // I11
    bird_as_animal.type();         // I12
    tiger_as_animal.type();        // I13

    return 0;
}
```

Solutions: rappelons (cf. cours) que le **type statique** est le type de la variable ou de l’expression, et que son **type dynamique** est le type avec lequel l’objet est construit. De plus, la résolution d’un appel de fonction se fait en 3 étapes:

1. Le compilateur recherche la fonction appelée dans le type statique de l’objet. S’il ne trouve pas la fonction, il remonte dans la classe du parent, et ainsi de suite.
2. Une fois cette fonction trouvée, il regarde si elle est virtuelle ou non.
3. Si oui, alors la résolution de l’appel est finalisée à l’exécution, en utilisant la virtual table du type dynamique de l’objet.
    Si non, alors la résolution de l’appel s’achève pendant la compilation.

Sur base de ces règles:

| Appel | Type statique | Type dynamique | Fonction appelée | Affichage |
|-------|---------------|----------------|------------------|-----------|
| I1    | Tiger         | Tiger          | Tiger::move, puisqu'elle existe dans le type statique et n'est pas virtuelle  | Running! |
| I2    | Animal        | Tiger          | Animal::move existe dans le type statique, mais elle est virtuelle, donc ce sera Tiger::move qui la redéfinit    | Running! |
| I3    | Bird          | Bird           | Bird::move, puisqu'elle existe dans le type statique et n'est pas virtuelle                 |  Flying! |
| I4    | Animal        | Bird           | Animal::move existe dans le type statique et est virtuelle; on remarque qu'il existe aussi un Bird::move, mais qui est const et n'est donc pas une redéfinition, donc ce sera Animal::move qui sera appelée | Moving! | <- doute
| I5    | Bird          | Bird           | Bird::can_eat_plant, puisqu'elle existe dans le type statique et n'est pas virtuelle        |  Miam! |
| I6    | Herbivore     | Bird           | Herbivore::can_eat_plant existe et est const dans le type statique,  et est virtuelle; on remarque qu'il existe aussi un Bird::can_eat_plant, mais qui n'est pas const et n'est donc pas une redéfinition, donc ce sera Herbivore::can_eat_plant qui sera appelée | Yum!  | <- doute
| I7    | Carnivore     | Bird           | Carnivore::can_eat_plant, puisqu'elle existe dans le type statique et n'est pas virtuelle | Berk! |
| I8    | Tiger         | Tiger          | Tiger::can_eat_plant n'existe pas, on remonte donc Carnivore qui en contient une, donc ce sera Carnivore::can_eat_plant  | Berk! |
| I9    | Tiger         | Tiger          | Tiger::can_eat_meat, puisqu'elle existe dans le type statique et n'est pas virtuelle  | Miam! |
| I10   | Carnivore     | Tiger          | Carnivore::can_eat_meat, puisqu'elle existe dans le type statique et n'est pas virtuelle   | Yum! |
| I11   | Bird          | Bird           | Bird::type, puisqu'elle existe dans le type statique et n'est pas virtuelle | Bird |
| I12   | Animal        | Bird           | Animal::type, puisqu'elle existe dans le type statique et n'est pas virtuelle                 | Animal |
| I13   | Animal        | Tiger          | Animal::type, puisqu'elle existe dans le type statique et n'est pas virtuelle                 | Animal |


## Exercice 2 - Donjons (1h40)

L'objectif de ce programme est de créer une simulation dans laquelle différentes entités évoluent à l'intérieur d'un donjon et peuvent potentiellement interagir entre elles.

### A. Existant

Une fois de plus, nous vous avons préparé le squelette du programme.

1. Commencez par compiler le programme et lancez-le. Vous devriez voir un rectangle contenant deux `?` qui se déplacent à l'intérieur. 

```b
# Configurer le projet dans un dossier de build
cmake -B <chemin_vers_le_dossier_build> -S <chemin_vers_le_dossier_tp7>

# Compiler le programme
cmake --build <chemin_vers_le_dossier_build> --target tp7-ex2

# Lancer le programme
<chemin_vers_le_dossier_build>/tp7-ex2
```

2. Prenez connaissance du contenu des fichiers pré-existants et répondez aux questions suivantes :
- Dans [Dungeon.cpp](dungeon/Dungeon.cpp), quel est le rôle de la fonction `display` ?
- Dans [Dungeon.cpp](dungeon/Dungeon.cpp), quel est le rôle de la fonction `update` ?
- Quelle variable du `main` porte l'ownership des entités ?

Solutions: 
- `display` affiche la grille passée en paramètre avec son contenu, ainsi que le contenu des logs passés en paramètre;
- `update` met à jour l'état d'une grille en fonction de ce qui s'y est passé: elle appelle la fonction update de chaque entité, remplit la grille via fill_grid, puis déclenche les interactions entre les entités. Ensuite, elle évacue les entités mortes et refait un appel à fill_grid pour la rafraîchir.

### B. Personnage

Vous allez maintenant définir des sous-types d'entités.
Chacun d'entre eux sera représenté par un caractère différent sur la grille.

1. Définissez une classe `Character` qui hérite de `Entity`.
Décommentez l'instruction ci-dessous dans le `main` et vérifiez qu'un troisième `?` apparaît bien dans le coin supérieur gauche de la grille. 
```cpp
all_entities.push_back(std::make_unique<Character>());
```

2. Définissez maintenant un constructeur prenant en paramètre deux entiers `x` et `y`. Vous passerez ces paramètres **au constructeur de la classe de base** afin d'initialiser la position du personnage.  
Adaptez l'instruction du `main` de manière à ce que le personnage apparaisse en `(40, 5)` et testez votre programme.

3. Modifiez la fonction `Entity::get_representation() const` afin que celle-ci puisse être redéfinie dans les classes-filles.
Ajoutez ensuite la redéfinition de cette fonction dans `Character`, afin que les personnages soient représentés par des `O` plutôt que par des `?`. Pensez bien à y ajouter le mot-clef **`override`** pour vous assurez que votre redéfinition est valide.

### C. Pièges et potions

1. Ajoutez la classe `Trap`, qui dérivera elle aussi de `Entity`.
Son constructeur prendra en paramètre la taille de la grille (`width` et `height`) et placera l'entité à une position aléatoire dedans (vous pouvez utiliser la fonction `random_value` pour générer des valeurs).
Arrangez-vous ensuite pour que les pièges soient représentés par des `X` sur la grille.
Pour terminer, décommentez les instructions suivantes du `main` pour tester votre code :
```cpp
all_entities.push_back(std::make_unique<Trap>(width, height));
all_entities.push_back(std::make_unique<Trap>(width, height));
```

2. Les pièges sont des entités immobiles du dongeon.
Modifiez le code des classes afin que `Character::update` continue de déplacer les personnages de façon aléatoire et que `Trap::update` ne produise aucun effet sur les pièges.

3. Sur le même modèle que `Trap`, définissez une classe `Potion`.
Comme les pièges, les potions sont des entités immobiles et posées initialement à des endroits aléatoires de la carte.
Elles seront représentées par le symbole `$` sur la grille.

4. Refactorisez votre code afin que `Potion` et `Trap` héritent toutes les deux d'une classe `Item`, elle-même héritant de `Entity`, et placez le code en commun dans `Item`.

5. Maintenant que toutes les classes possibles d'entités ont été implémentées, nous souhaitons empêcher l'instanciation directe du type `Entity`.
Pour cela, vous allez retirer l'implémentation de `Entity::get_representation` et rendre cette fonction virtuelle pure.
Une fois vos changements faits, le compilateur devrait vous empêcher de compiler votre programme à cause des `std::make_unique<Entity>(...)` dans le `main`. Remplacez ces appels afin de créer des `Character` à la place.

### D. Interactions

Lorsque deux entités se retrouvent sur la même case, elles peuvent interagir entre elles.
Ce comportement est géré par la fonction `trigger_interactions` de [Dungeon.cpp](dungeon/Dungeon.cpp).

1. Implémentez le minimum de code permettant de décommenter les deux lignes commentées dans la fonction `trigger_interactions`.

2. Lorsqu'un personnage rencontre un piège, il "perd une vie". Sa représentation passe alors de `O` à `o`.
S'il rencontre un deuxième piège, il "meurt" et sa représentation devient alors ` `.
Pour mettre en place ce comportement, vous redéfinirez la fonction `interact_with` dans `Character`. Afin de savoir si l'entité avec laquelle vous intéragissez est un `Trap`, vous devrez utiliser un [dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast) :
```cpp
const auto* trap = dynamic_cast<Trap*>(&entity);
if (trap != nullptr)
{
    // entity est bien une instance de Trap
}
```

3. Testez votre programme.
Pour augmentez la probabilité d'interactions, n'hésitez pas à réduire la taille de la grille ou à ajouter des éléments en plus à l'aide d'une boucle.

4. Faites maintenant le nécessaire pour que les potions "restorent la vie" des personnages : la représentation d'un personnage passera alors de `o` à `O`.

### E. Destructions

Les entités doivent être supprimées du programme une fois qu'elles ne sont plus censées exister sur la grille.
Voici les règles de gestion pour chacune des entités :
- `Character` : un personnage doit être supprimé dès lorsqu'il a perdu ses deux vies.
- `Trap`: un piège doit être détruit dès lorsqu'il rentre en contact avec un personnage.
- `Potion` : une potion doit être supprimée lorsqu'elle est consommée par un personnage qui n'a pas toutes ses vies.

1. Rajoutez une nouvelle fonction virtuelle `should_destroy` dans `Entity` qui permettra de savoir si une entité doit être supprimée du programme ou pas. Par défaut, elle renverra toujours `false`.
Modifiez ensuite la condition dans la fonction `remove_dead_entities` de [Dungeon.cpp](dungeon/Dungeon.cpp) afin que les entités concernées puissent être supprimées du programme.

2. Implémentez la redéfinition de votre fonction dans `Character` afin d'obtenir le comportement attendu, puis testez.

3. Pour faire disparaître les `Item` de la grille, ajoutez leur un attribut `is_consumed` de type booléen ainsi qu'une fonction publique `consume` qui passe cet attribut à `true`.
Appelez cette fonction à l'endroit approprié, et utilisez la valeur de `is_consumed` pour définir l'implémentation de `should_destroy` dans les instances d'`Item`.

4. Ajoutez un destructeur spécifique à la classe `Character` afin de logger dans la console qu'un personnage est mort. Vous écrirez dans la variable globale `logger` (voir [Logger.hpp](dungeon/Logger.hpp)) plutôt que dans `std::cout`. Cela permettra d'afficher les logs en dessous de la grille.
On attendra quelque chose comme : `"A character died at position (5, 7)"`.
Si votre destructeur n'est pas appelé, demandez-vous sur quel est le type statique de l'objet détruit et ce qu'il se passe au cours de la résolution de l'appel.

5. **(Bonus)** Faites en sorte que les entités qui sortent de la grille soient aussi supprimées.
