////////////////////////////////////////////////////////////////////////////////////////
//
// Vous devez indiquer si chacune des propositions est vraie (true) ou fausse (false).
//
// Exemple : Le C++ est le meilleur langage de tous les temps.
#define ANSWER_EX1 true
//                 ^^^^ indiquez votre réponse ici
//
// Exemple : Le Java est le meilleur langage de tous les temps.
#define ANSWER_EX2 false
//                 ^^^^^
//
////////////////////////////////////////////////////////////////////////////////////////

// Pour indiquer qu'une fonction-membre ne modifie pas l'état de l'objet, on écrit const
// devant le type de retour de la fonction.
#define ANSWER_1 false // c'est juste avant le { qu'il faut placer le const

// Le type char* est le mieux adapté pour représenter des chaînes de caractères.
#define ANSWER_2 false // cela fonctionne, mais std::string est plus souple

// On ne peut pas définir de fonctions-membres dans une struct.
#define ANSWER_3 false // rappelez-vous du destructeur du TP 3

// Le littéral 0u est de type unsigned int.
#define ANSWER_4 true

// Une variable booléenne se définit avec le type `boolean`.
#define ANSWER_5 false // c'est bool, pas boolean

// On peut utiliser `inline` pour définir des attributs statiques directement dans la classe.
#define ANSWER_6 true

// Si une fonction est définie dans deux fichiers-objets différents, l'erreur se produit lors de la phase de
// build.
#define ANSWER_7 false // le conflit sera apparent au moment où le linker doit faire son travail

// Le mot-clef `auto` sert à définir des variables sans préciser leur valeur initiale.
#define ANSWER_8 false // il sert à laisser le compilateur déduire le type de la variable, ce qu'il ne peut faire sans valeur

// Le type `std::vector` sert à créer des tableaux alloués dynamiquement.
#define ANSWER_9 true

// Il faut toujours penser à appeler `delete` sur les pointeurs observants.
#define ANSWER_10 false // ce sont les pointeurs ownants qui sont responsables de la désinstanciation

// Si une classe `MyClass` a un attribut `std::string& _name` alors, par défaut,
// la destruction d'une instance o de  `MyClass` détruit la chaîne de caractère référencée par o._name.
#define ANSWER_11 true

// Si une classe `MyBoxingClass` a un attribut `std::vector<MyBoxedClass> _data` alors, par défaut,
// la destruction d'une instance o de  `MyBoxingClass` provoque la destruction de toutes les instances de
// `MyBoxedClass` contenues dans o.name.
#define ANSWER_12 true