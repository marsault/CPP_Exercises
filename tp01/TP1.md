# TP1 - Introduction

## Objectifs

- Ecrire un programme basique en C++
- Utiliser quelques classes de la librairie standard
- Compiler un programme constitué de plusieurs fichiers sources
- Commiter et revenir en arrière avec Git

## Rappels du cours

<details>
<summary>Compilation</summary>

```bash
# Build some source files (= generate object-files)
g++ -c file1.cpp file2.cpp file3.cpp --std=c++17
# Link the object-files into an executable.
g++ -o the_exe file1.o file2.o file3.o
# Execute the binary.
./the_exe
```
</details>

<details>
<summary>Utiliser Git</summary>

```bash
# Clone a repository.
git clone https://url_to_repository
# Move into the repository.
cd repository_folder
# Create and go on a new branch.
git switch -c new_branch
# Stage some changes (= prepare them for commit).
git add file1 file2 folder1
# Commit with a specific message on the current branch.
git commit -m "a message"
# Switch back to an existing branch.
git switch other_branch
# Put the commits of a branch named "work" into the current branch.
git merge work
```
</details>

<details>
<summary>Ecrire dans la console</summary>

```cpp
std::cout << "Value of var_a is:" << var_a << "." << std::endl;
```
</details>

<details>
<summary>Lire depuis la console</summary>

```cpp
std::cin >> var_a;
```
</details>

<details>
<summary>Utiliser un tableau dynamique</summary>

```cpp
auto values = std::vector<int>{ 1, 2, 3 };
auto first = values[0];
values.push_back(4);
```
</details>

<details>
<summary>Utiliser une chaîne de caractères</summary>

```cpp
auto first_name = std::string { "Medor" };
auto last_name = std::string { "TheDog" };
auto full_name = first_name + ' ' + last_name;
```
</details>


## Exercice 1 - Entrée / sortie (30 min)

1. Ouvrez le fichier [main.cpp](ex1/main.cpp) et essayez de comprendre ce que font chacune de ses lignes.

2. Compilez ce programme de manière à générer un executable nommé "bonjour".

3. Lancez le programme. Celui-ci vous demande votre nom, mais affiche toujours en sortie : "Bonjour Palluche La Faluche !".  
Modifiez le programme pour qu'il affiche votre prénom à la place.

4. Créez une nouvelle branche git nommée `tp1` et commitez vos changements dessus avec le message "tp1 - ex1 - q4".

5. Lancez le programme et passez-lui un très long nom (au moins 20 caractères). Que se passe-t-il ?  
Quelle classe de la librairie standard faudrait-il utiliser à la place du tableau de `char` pour stocker le nom de l'utilisateur ?

6. Modifiez le programme afin de réaliser ce changement. Testez et commitez vos modifications.

7. Prenez note des difficultés que vous avez rencontrées durant cet exercice et de comment vous les avez surmontées.
 
## Exercice 2 - Tableaux dynamiques

1. Ouvrez le fichier [main.cpp](ex2/main.cpp) et essayez de comprendre ce que font chacune de ses lignes.

2. La boucle affichant le contennu du tableau est une boucle classique du C. Transformez là en une boucle `for-each`.

3. Affichez les valeurs du premier et du dernier élément.

3. Écrivez un code ajoutant à la fin du tableau d'entiers le double de chaque valeur déjà présente.

4. Plutôt que d'écrire en dur les premières valeurs du tableau, complétez le programme afin qu'il demande à l'utilisateur la suite de ces valeurs.
   On terminera la saisie par la valeur 0.

5. Permettez à l'utilisateur d'effacer la dernière valeur saisie en entrant un nombre négatif.

6. Prenez note des difficultés que vous avez rencontrées durant cet exercice et de comment vous les avez surmontées.

## Exercice 3 - Questions (30 min)

A faire avec l'ensemble du groupe.  
Pensez à prendre des notes pour les donner à vos camarades absents.

1. Parlez de vos différents blocages avec le restant de la classe et discutez des solutions.

2. Expliquez la différence entre phase de build (compilation) et phase de link (édition des liens).  
En quoi consiste la précompilation et à quel moment est-elle effectuée ?

3. Que signifient les messages suivants ?  
a. error: 'qqchose' was not declared in this scope  
b. error: 'qqchose' is not a member of 'std'  
Ces erreurs se produisent-elles pendant la phase de build ou de link ?  
Que fait exactement l'instruction préprocesseur `#include` et pourquoi permet-elle généralement de résoudre ce type de problème ?

4. Compilez le programme de l'exercice en ne linkant que le fichier-objet associé à `main.cpp` (c'est-à-dire en oubliant `utils.cpp`).  
Quelle est l'erreur qui s'affiche ?    
En quoi est-elle différente des erreurs de la question précédente ?  
Expliquez ce qu'elle signifie exactement.

5. Décommentez maintenant les instructions commentées des fichiers [main.cpp](ex3/main.cpp) et [utils.hpp](ex3/utils.hpp).  
Compilez maintenant le programme complet (avec les modules main et utils).  
Quelle est l'erreur qui s'affiche ? S'agit-il d'une erreur de build ou de link ?  
Pourquoi se produit-elle ?  
Que faudrait-il faire pour la résoudre ?

6. Ajoutez le mot-clef `inline` devant la définition de la fonction `print_bye` dans [utils.hpp](ex3/utils.hpp). Que constatez-vous quand vous réessayez de compiler le programme ?  
Selon-vous, quel est l'effet du mot-clef `inline` sur le linker ?

## Pour terminer

Commitez vos modifications si ce n'est pas déjà fait.  
Revenez sur la branche `master`. Vous devriez voir disparaître tout votre beau travail.  
Si vous souhaitez le retrouver, vous pouvez soit retourner sur la branche `tp1`, soit merger cette branche sur la branche `master`.