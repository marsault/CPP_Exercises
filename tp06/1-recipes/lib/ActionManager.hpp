#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <map>

#include "../ProgramData.hpp"

// Attention, vous n'avez pas à comprendre en détail comment fonctionne un ActionManager

class ActionManager;
using ActionTarget
    = std::function<void(const ActionManager&, ProgramData&, std::deque<std::string>)>;

class Node
{
public:
  void register_action(const std::vector<std::string>& path, ActionTarget target,
                       int arg_expected, std::string description, size_t index)
  {
    assert(!(_target));
    if (path.size() == index) {
      assert(_children.size() == 0);
      _target = target;
      _arg_expected = arg_expected;
      _description = description;
    }
    else {
      if (_children.count(path[index]) == 0)
        _children[path[index]] = Node{};
      _children[path[index]].register_action(path, target, arg_expected, description,
                                             index + 1);
    }
  }

  const ActionTarget find_action(std::vector<std::string> path,
                                 std::deque<std::string>& arguments) const
  {
    if (_target) {
      if (_arg_expected < 0 || arguments.size() == _arg_expected)
        return _target;
      std::cerr << "Action '";
      bool first = true;
      for (auto& s : path) {
        if (first)
          first = false;
        else
          std::cerr << " ";
        std::cerr << s;
      }
      std::cerr << "' expects " << _arg_expected << " arguments, got " << arguments.size()
                << std::endl;
      return nullptr;
    }

    std::string subaction = std::move(arguments.front());
    arguments.pop_front();

    auto it = _children.find(subaction);
    if (it == _children.end()) {
      if (path.empty())
        std::cerr << "There is no action '" << subaction << "'" << std::endl;
      else {
        std::cerr << "There is no subaction '" << subaction << "' in action '";
        bool first = true;
        for (auto& s : path) {
          if (first)
            first = false;
          else
            std::cerr << " ";
          std::cerr << s;
        }
        std::cerr << "' ";
      }
      std::cerr << "(Possibilities are:";
      for (auto& s : _children)
        std::cerr << " " << s.first;
      std::cerr << ")" << std::endl;
      return nullptr;
    }
    path.push_back(std::move(subaction));
    return it->second.find_action(path, arguments);
  }

  std::ostream& put(std::ostream& o, const std::string& prefix = "") const
  {
    if (_children.empty()) {
      o << prefix;
      for (int i = 0; i < _arg_expected; ++i)
        o << " <arg>";
      if (_arg_expected == -1)
        o << " <arg> [<arg> ...] => <arg>";
      o << " :\t" << _description << std::endl;
    }
    else
      for (auto& child : _children)
        child.second.put(o, prefix + " " + child.first);
    return o;
  }

private:
  std::map<std::string, Node> _children;
  ActionTarget _target;
  int _arg_expected;
  std::string _description;
};

class ActionManager
{
  friend std::ostream& operator<<(std::ostream& o, const ActionManager& manager)
  {
    return manager._root.put(o, "\t-");
  }

public:
  void execute_action(ProgramData& data, std::deque<std::string> arguments) const
  {
    auto target = _root.find_action({}, arguments);
    if (target != nullptr)
      target(*this, data, arguments);
  }

  void register_action(const std::vector<std::string>& path, int args_expected,
                       std::string description, ActionTarget target)
  {
    _root.register_action(path, target, args_expected, description, 0);
  }

  void register_action(const std::vector<std::string>& path, int args_expected,
                       std::string description, std::function<void(ProgramData&)> target)
  {
    ActionTarget ext_target = [target](const ActionManager&, ProgramData& data,
                                       std::deque<std::string>) { target(data); };
    _root.register_action(path, ext_target, args_expected, description, 0);
  }

  void register_action(const std::vector<std::string>& path, int args_expected,
                       std::string description,
                       std::function<void(const ActionManager&)> target)
  {
    ActionTarget ext_target = [target](const ActionManager& manager, ProgramData&,
                                       std::deque<std::string>) { target(manager); };
    _root.register_action(path, ext_target, args_expected, description, 0);
  }

  void register_action(const std::vector<std::string>& path, int args_expected,
                       std::string description,
                       std::function<void(ProgramData&, std::deque<std::string>)> target)
  {
    ActionTarget ext_target
        = [target](const ActionManager&, ProgramData& data, std::deque<std::string> args)
    { target(data, args); };
    _root.register_action(path, ext_target, args_expected, description, 0);
  }

  void register_action(const std::vector<std::string>& path, int args_expected,
                       std::string description,
                       std::function<void(ProgramData&, std::string)> target)
  {
    assert(args_expected == 1);
    ActionTarget ext_target
        = [target](const ActionManager&, ProgramData& data, std::deque<std::string> args)
    { target(data, std::move(args.front())); };
    _root.register_action(path, ext_target, args_expected, description, 0);
  }

private:
  Node _root;
};