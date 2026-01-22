#include "lib/Actions.cpp"

int main(int argc, char** argv)
{
  ProgramData data;
  ActionManager manager;
  //                    expected number of arguments
  //                                |
  //                      command   |   short description   function called
  //                      vvvvvvv   v  vvvvvvvvvvvvvvvvvvvv vvvv (in lib.Actions)
  manager.register_action({"help"}, 0, "Affiche cette aide", help);
  manager.register_action(
      {"load"}, 1, "Charge le fichier <arg>.txt et execute chacune de ses lignes", load);
  manager.register_action({"new", "mat"}, 1, "Déclare le nouveau materiau <arg>", new_mat);
  manager.register_action({"add", "mat"}, 1, "Ajoute un materiau <arg> à l'inventaire",
                          add_mat);
  manager.register_action({"list", "mat"}, 0, "Affiche tous les matériaux déclarés",
                          list_mat);
  manager.register_action({"list", "rec"}, 0, "Affiche toutes les recettes déclarés",
                          list_rec);
  manager.register_action({"list", "doable"}, 0, "Affiche toutes les recettes réalisables",
                          list_doable);
  manager.register_action({"list", "inv"}, 0, "Affiche les matériaux dans l'inventaire",
                          list_inv);
  manager.register_action({"del", "rec"}, 1,
                          "Supprime la recette dont l'identifiant est donné", del_rec);
  manager.register_action(
      {"prod"}, 1, "Tente de réaliser la recette dont l'identifiant est <arg>", produce);
  manager.register_action({"new", "rec"}, -1, "Déclare une nouvelle recette", new_rec);
  manager.register_action({"quit"}, 0, "Termine le programme", quit);

  while (true) {
    std::cout << ">> Entrez une commande ('help' pour afficher l'aide):" << std::endl;

    auto command = std::string{};
    while (command.empty())
      std::getline(std::cin, command);
    std::deque<std::string> arguments = parse_words(command);
    if (command == "quit")
      break;
    manager.execute_action(data, arguments);
    std::cout << std::endl;
  }
}
