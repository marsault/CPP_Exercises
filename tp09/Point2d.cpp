
#include <iostream>
#include <string>
#include <unordered_map>

enum class Content
{
    Empty,
    Red,
    Yellow
};

class Point2d
{
public:
    Point2d(int x, int y)
        : _x { x }
        , _y { y } {}
    ~Point2d() = default;

    bool operator==(const Point2d& other) const { return other._x == _x && other._y == _y; };

    int _x;
    int _y;
};

namespace std {
template <>
struct hash<Point2d>
{
    std::size_t operator()(const Point2d& point) const {
        return (point._x * point._x + point._x + 2 * point._x * point._y + 3 * point._y + point._y * point._y) / 2;
    }
};
}

class Point2dHash
{
public:
    std::size_t operator()(const Point2d& point) const {
        const auto x = point._x, y = point._y;
        return (x * x + x + 2 * x * y + 3 * y + y * y) / 2;
    };
};

class Point2dEqual
{
public:
    bool operator()(const Point2d& premier, const Point2d& second) const {
        auto comparateur = Point2dHash();
        return comparateur(premier) == comparateur(second);
    };
};

void printMap(const std::unordered_map<Point2d, Content>& map)
{
    for (const auto& [key, value] : map)
    {
        std::string contentStr;
        switch (value)
        {
        case Content::Empty:
            contentStr = "Empty";
            break;
        case Content::Red:
            contentStr = "Red";
            break;
        case Content::Yellow:
            contentStr = "Yellow";
            break;
        }
        std::cout << "Point(" << key._x << ", " << key._y << ") -> " << contentStr << std::endl;
    }
};

int main(int argc, char const* argv[]) {
    auto map = std::unordered_map<Point2d, Content, Point2dHash, Point2dEqual>();
    map.emplace(Point2d(1, 2), Content::Red);
    map.emplace(Point2d(2, 1), Content::Yellow);
    auto grid = std::unordered_map<Point2d, Content>();
    grid.emplace(Point2d(1, 2), Content::Empty);
    grid.emplace(Point2d(2, 1), Content::Empty);
    printMap(grid);
    return 0;
}
