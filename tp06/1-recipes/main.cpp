#include "lib/Actions.c"

int main(int argc, char **argv)
{
    ProgramData data;
    ActionManager manager;
    manager.register_action({"help"}, 0, print_usage);
    manager.register_action({"load"}, 1, load);
    manager.register_action({"new", "mat"}, 1, new_mat);
    manager.register_action({"add", "mat"}, 1, add_mat);
    manager.register_action({"new", "rec"}, -1, new_rec);
    manager.register_action({"list", "mat"}, 0, list_mat);
    manager.register_action({"list", "rec"}, 0, list_rec);
    manager.register_action({"list", "doable"}, 0, list_doable);
    manager.register_action({"list", "inv"}, 0, list_inv);
    manager.register_action({"produce"}, 1, produce);
    while (true)
    {
        std::cout << ">> Entrez une commande :" << std::endl;

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
