#include "Entity.hpp"
#include "Logger.hpp"
#include "Character.hpp"
#include "Trap.hpp"
#include "Potion.hpp"

#include <array>
#include <chrono>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using Cell = std::vector<Entity*>;
using Grid = std::array<std::array<Cell, 50>, 10>;

void fill_grid(Grid& grid, const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (auto& line : grid)
    {
        for (auto& cell : line)
        {
            cell.clear();
        }
    }

    for (const auto& entity : entities)
    {
        const auto x = entity->get_x();
        const auto y = entity->get_y();

        if (0 <= y && y < grid.size() && 0 <= x && x < grid[y].size())
        {
            grid[y][x].push_back(entity.get());
        }
    }
}

void display(const Grid& grid, const std::deque<std::string>& logs)
{
    auto stream = std::stringstream {};

    for (auto x = 0; x < grid.front().size() + 2; ++x)
    {
        stream << "#";
    }

    stream << "\n";

    for (auto y = 0; y < grid.size(); ++y)
    {
        stream << "|";

        for (auto x = 0; x < grid[y].size(); ++x)
        {
            const auto& cell = grid[y][x];
            if (cell.empty())
            {
                stream << " ";
            }
            else
            {
                stream << cell.front()->get_representation();
            }
        }

        stream << "|\n";
    }

    for (auto x = 0; x < grid.front().size() + 2; ++x)
    {
        stream << "#";
    }

#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif

    stream << "\n";
    for (const auto& log : logs)
    {
        stream << log << "\n";
    }
    for (int i = logs.size(); i < 2; ++i)
    {
        stream << "\n";
    }

    std::cout << stream.str() << std::endl;
}

void trigger_interactions(const std::vector<Entity*>& entities)
{
    if (entities.size() > 1)
    {
        entities[0]->interact_with(*entities[1]);
        entities[1]->interact_with(*entities[0]);
    }
}

void remove_dead_entities(std::vector<std::unique_ptr<Entity>>& entities, int width, int height)
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        const auto should_remove = it->get()->should_destroy(); // <- modifiez cette condition
        if (it->get()->get_x() < 0 || it->get()->get_x() >= width) {
            it->get()->destroy();
        }
        if (it->get()->get_y() < 0 || it->get()->get_y() >= height) {
            it->get()->destroy();
        }
        if (should_remove)
        {
            it = entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void collect_logs(std::deque<std::string>& logs)
{
    while (!logger.eof())
    {
        std::getline(logger, logs.emplace_back());
        if (logs.back().empty())
        {
            logs.pop_back();
        }
    }

    logger = {};

    while (logs.size() > 2)
    {
        logs.erase(logs.begin());
    }
}

void update(Grid& grid, std::vector<std::unique_ptr<Entity>>& entities, int width, int height)
{
    for (auto& entity : entities)
    {
        entity->update();
    }

    fill_grid(grid, entities);

    for (auto& line : grid)
    {
        for (auto& cell : line)
        {
            trigger_interactions(cell);
        }
    }

    remove_dead_entities(entities, width, height);
    std::cout << logger.str();
    fill_grid(grid, entities);
}

int main()
{
    using namespace std::chrono_literals;

    auto logs = std::deque<std::string> {};

    auto       grid   = Grid {};
    const auto width  = grid.front().size();
    const auto height = grid.size();

    auto all_entities = std::vector<std::unique_ptr<Entity>> {};

    for (auto i = 0; i < 10; i++) {
        all_entities.push_back(std::make_unique<Character>(random_value(0, width - 1), random_value(0, height - 1)));
    }

    for (auto i = 0; i < 20; i++) {
        all_entities.push_back(std::make_unique<Trap>(width, height));
    }

    for (auto i = 0; i < 20; i++) {
        all_entities.push_back(std::make_unique<Potion>(width, height));
    }
    fill_grid(grid, all_entities);

    while (true)
    {
        collect_logs(logs);
        display(grid, logs);

        std::this_thread::sleep_for(1s);
        update(grid, all_entities, width, height);
    }

    return 0;
}
