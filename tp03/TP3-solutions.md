Voici les réponses aux questions ne demandant pas (beaucoup) de code.

# Exercice 1 - Graphes d'ownership

## Cas A - Copie VS Référence

1. Pourquoi n'y a-t-il pas de relation entre `last_wheel` et `wheels[3]` contrairement à `first_wheel` et `wheels[0]` ?

    - La ligne `auto& first_wheel = car.wheels.front();` initialise une référence `first_wheel` au début de `car.wheels`, ce qui justifie la présence de la flèche en pointillé de `first_wheel` vers `car.wheels`. En revanche, la ligne `auto  last_wheel = car.wheels.back();` initialise une *copie*  `first_wheel` du dernier élément de `car.wheels`; il n'y a donc aucune raison d'avoir un lien entre les deux variables.

## Cas B - Pointeurs-observants

1. Dans le graphe d'ownership, comment distingue-t-on un pointeur d'une référence ?
    - la flèche représentant un pointeur est continue, tandis qu'elle est pointillée pour les références;
1. Comment est représenté un pointeur nul ?
    - un X encerclé;
1. En termes de code, quelles sont les deux différences principales entre un pointeur-observant et une référence ?
    1. un pointeur peut être initialisé à une valeur vide (`nullptr`), alors qu'une référence **doit** se référer à un objet existant;
    1. on peut changer la destination d'un pointeur (c'est-à-dire le faire pointer vers autre chose que l'adresse initiale) en cours de route, alors que la référence est toujours une référence au même objet que lors de son initialisation.
    
## Cas C - Insertions dans un std::vector

Lors d'une insertion, si le buffer mémoire réservé par `std::vector` n'a pas la place de contenir le nouvel élément, alors le contenu du tableau est réalloué dans un tout nouveau buffer de taille suffisante. Chaque élément est déplacé de son ancienne adresse mémoire vers la nouvelle.

1.    Essayez de représenter les transitions dans le graphe d'ownership après le dernier `push_back` si celui-ci déclenchait une réallocation mémoire.
        - (TODO: à dessiner): une nouvelle case `products[2]` apparaît après  `products[1]`; une flèche continue de `products` vers  `products[2]` est créée; et comme les données sont déplacées, la fin de la flèche pointillée issue de `first_product` continue à pointer vers **l'ancienne adresse** de  `products[0]`;
1.    Quel problème relève-t-on dans le graphe ?
        - une "dangling reference", c'est-à-dire une référence qui pointe dans le vide (à savoir `first_product`) comme expliqué ci-dessus;
1.    Modifiez le code ci-dessus afin que `products` contienne des pointeurs ownants. Pensez à ajouter un destructeur à `Client` pour libérer la mémoire allouée dynamiquement.
        - `products` devient un `std::vector<Product*>` dans `Client`. Dans le `main`, il faut donc maintenant faire `push_back` de `new Product{}`. Enfin, les pointeurs de notre `struct Client` étant maintenant ownants, le constructeur à rajouter doit parcourir les pointeurs de `products` un à un pour veiller à libérer les données correspondantes via un `delete`. On obtient maintenant ceci:
        
            ```cpp
            #include <memory>
            #include <vector>

            struct Product
            {};

            struct Client
            {
                std::vector<Product*> products;
                ~Client() {
                    for (auto* prod: products)
                        delete prod;
                };
            };

            int main()
            {
                auto client = Client {};

                client.products.push_back(new Product{});
                client.products.push_back(new Product{});

                auto* first_product = client.products.front();
                client.products.push_back(new Product{});
                
                return 0;
            }
            ```
1.    Redessinez le graphe d'ownership de la question 1, mais en prenant en compte vos changements dans le code.
        - (TODO: à dessiner)
1.    Avez-vous toujours le problème relevé à la question 2 ?
        - TODO expliquer

## Exercice 2 - La meilleure signature (15min)

1. Remplacez les `XX` par les bons types, de manière à ce que le programme compile et affiche `10 42`.

    - `add` ne modifie ni `a` ni `b`, qui d'après le `main` sont des entiers; on peut donc au choix leur donner le type `int`{:.cpp}, ou le type `const int&`{:.cpp}. La fonction renvoyant une somme de deux entiers, son type de retour peut simplement être `int`{:.cpp}. En revanche, la fonction `add_to` doit modifier `a`: son type doit donc être `int&`{:.cpp}. Comme pour `add`, le type `b` sera `int`{:.cpp} ou `const int&`{:.cpp}. Enfin, la fonction ne renvoyant rien, son type de retour doit être `void`{:.cpp}.

        ```cpp
        #include <iostream>

        int add(const int& a, const int& b)
        {
            return a + b;
        }

        XX add_to(XX a, XX b)
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

2. Modifiez si besoin les types des paramètres dans les fonctions ci-dessous pour que le passage soit le plus efficace et le plus sécurisé possible. Aidez-vous des commentaires pour comprendre comment les fonctions utilisent leurs paramètres.

    - `count_a_occurrences`: l'énumération ne nécessite pas de modifier la chaîne, et l'absence de référence implique une copie. On va donc modifier la signature en `int count_a_occurrences(const std::string& s);`{:.cpp}.
    - `update_loop`: pas de changement à faire; on aurait éventuellement pu écrire seulement `float`{:.cpp} pour `dt`.
    - `are_all_positives`: `values` n'a pas à être modifié, on le passe donc en référence constante pour éviter les copies inutiles par la même occasion. `negative_indices_out` est un tableau statique et est donc automatiquement passé par référence, il n'y a donc pas d'autre modification à faire. On obtient: `bool are_all_positives(const std::vector<int>& values, int negative_indices_out[], size_t& negative_count_out);`{:.cpp}.
    
    - `concatenate`: la fonction ne modifiant pas ses paramètres, on rajoute un `const` devant chacun d'eux. On obtient: `std::string concatenate(char* str1, char* str2);`{:.cpp}.


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

Pour chaque architecture, vous indiquerez les opérations que le programme devrait effectuer pour satisfaire chacun des besoins cités plus haut, sans jamais introduire de dangling-reference.

## Architecture A

1. lister tous les salariés: un simple parcours d'un `vector<Employee>` suffit.
2. lister tous les départements:  un simple parcours d'un `vector<Department>` suffit.
3. lister les personnes appartenant à un département précis: l'architecture A précise qu'il doit s'agir d'une collection de références, on parcourra donc un `vector<Employee*>` de pointeurs observants --- plutôt que des références, car plus bas on peut licencier des employés, ce qui poserait problème pour les références qui contrairement aux pointeurs ne peuvent pas être "nulles".
4. lister tous les managers: un simple parcours d'un `vector<Employee>` suffit.
5. lister les subordonnés d'un manager: on parcourt un `vector<Employee>` à la recherche du manager dont on a reçu le nom, puis l'on parcourt un `vector<Employee>` correspondant pour afficher son contenu.
6. embaucher un nouveau salarié: ajout en fin d'un `vector<Employee>`.
7. licencier un salarié: parcours et suppression dans un `vector<Employee>`, et suppression du pointeur observant correspondant dans l'unique département qui l'employait.
8. changer un salarié de département: suppression du pointeur observant dans l'ancien département et ajout dans le nouveau.
9. augmenter le salaire d'une personne: modification du champ correspondant dans `Employee`.
10. afficher la somme totale payée pour les salaires par département: parcours simple d'un `vector<Department>` pour chaque département, et consultation des salaires via les références vers les employées appartenant au département.

## Architecture B

1. lister tous les salariés: un simple parcours d'un `vector<Employee>` par département.
2. lister tous les départements: un simple parcours d'un `vector<Department>` suffit.
3. lister les personnes appartenant à un département précis: une fois le département identifié dans la collection, un simple parcours d'un `vector<Employee>` suffit.
4. lister tous les managers: pour chaque département, il nous faut parcourir les employés qui s'y trouvent et identifier le manager parmi eux.
5. lister les subordonnés d'un manager: on doit parcourir tous les départements à la recherche du manager, et une fois le manager trouvé, on a accès directement à sa collection de subordonnés.
6. embaucher un nouveau salarié: on doit aller chercher le département auquel il va appartenir, puis seulement l'insérer dans la collection correspondante.
7. licencier un salarié: parcourir les départements à la recherche de celui du salarié, puis le supprimer de la collection correspondante. Mais en plus de cela, il faut parcourir toutes les collections de subordonnés pour éliminer les références à l'employé licencié. Comme le montre le schéma, on doit parcourir tous les départements pour ce faire, puisqu'un employé peut être subordonné à quelqu'un d'un autre département.
8. changer un salarié de département: l'extraire de sa collection actuelle et le rajouter à la collection future. Les relations de subordination sont mises à jour automatiquement grâce aux références.
9. augmenter le salaire d'une personne: il faut parcourir chaque département à la recherche de l'employé, puis modifier le champ associé.
10. afficher la somme totale payée pour les salaires par département: pour chaque département, sommer ce que l'on paie pour chacun de ses employés.

## Architecture C

1. lister tous les salariés: on doit parcourir la collection d'employés récursivement;
2. lister tous les départements: on doit parcourir la collection de départements;
3. lister les personnes appartenant à un département précis: on doit parcourir la collection d'employés récursivement, et ne garder que ceux dont le département correspond à celui demandé;
4. lister tous les managers: on explore récursivement les employés qui possèdent des subordonnés;
5. lister les subordonnés d'un manager: on explore récursivement les employés jusqu'à trouver celui dont on a reçu le nom, et on affiche ensuite sa collection de subordonnés;
6. embaucher un nouveau salarié: si c'est un manager, on le rajoute à la collection dont fait partie par exemple charline; sinon, c'est le subordonné d'un ou plusieurs managers, et il faut explorer la structure récursivement pour faire les ajustements nécessaires. Dans tous les cas, on doit rajouter également une référence vers le département dont il fera partie.
7. licencier un salarié: on le supprime des collections de subordonnés dont il fait partie, en n'oubliant pas d'effacer la référence au département auquel il appartient.
8. changer un salarié de département: il faut mettre à jour la référence du salarié vers le nouveau département.
9. augmenter le salaire d'une personne: explorer la structure d'employés récursivement à la recherche de la personne à augmenter et faire les modifications.
10. afficher la somme totale payée pour les salaires par département: explorer la structure d'employés récursivement, et procéder aux calculs des sommes séparées par département.

