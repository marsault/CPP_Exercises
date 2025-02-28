#include <functional>
#include <map>
#include <cassert>
#include <deque>

#include "../ProgramData.hpp"

class ActionManager;
using ActionTarget = std::function<void(const ActionManager &, ProgramData &, std::deque<std::string>)>;

class Node
{
public:
    void register_action(const std::vector<std::string> &path, ActionTarget target, int arg_expected, size_t index)
    {
        assert(!(_target));
        if (path.size() == index)
        {
            assert(_children.size() == 0);
            _target = target;
            _arg_expected = arg_expected;
        }
        else
        {
            if (_children.count(path[index]) == 0)
                _children[path[index]] = Node{};
            _children[path[index]].register_action(path, target, arg_expected, index + 1);
        }
    }

    const ActionTarget find_action(std::vector<std::string> path, std::deque<std::string> &arguments) const
    {
        if (_target)
        {
            if (_arg_expected < 0 || arguments.size() == _arg_expected)
                return _target;
            std::cerr << "Action '";
            bool first = true;
            for (auto &s : path)
            {
                if (first)
                    first = false;
                else
                    std::cerr << " ";
                std::cerr << s;
            }
            std::cerr << "' expects " << _arg_expected << " arguments, got " << arguments.size() << std::endl;
            return nullptr;
        }

        std::string subaction = std::move(arguments.front());
        arguments.pop_front();

        auto it = _children.find(subaction);
        if (it == _children.end())
        {
            if (path.empty())
                std::cerr << "There is no action '" << subaction << "'" << std::endl;
            else
            {
                std::cerr << "There is no subaction " << subaction << "in action '";
                bool first = true;
                for (auto &s : path)
                {
                    if (first)
                        first = false;
                    else
                        std::cerr << " ";
                    std::cerr << s;
                }
                std::cerr << "'" << std::endl;
            }
            std::cerr << "(Possibility are:";
            for (auto &s : _children)
                std::cerr << " " << s.first;
            std::cerr << ")" << std::endl;
            return nullptr;
        }
        path.push_back(std::move(subaction));
        return it->second.find_action(path, arguments);
    }

private:
    std::map<std::string, Node> _children;
    ActionTarget _target;
    int _arg_expected;
};

class ActionManager
{
public:
    void execute_action(ProgramData &data, std::deque<std::string> arguments) const
    {
        auto target = _root.find_action({}, arguments);
        if (target != nullptr)
            target(*this, data, arguments);
    }

    void register_action(const std::vector<std::string> &path, int args_expected, ActionTarget target)
    {
        _root.register_action(path, target, args_expected, 0);
    }

private:
    Node _root;
};