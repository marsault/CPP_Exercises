#include <set>
#include <tuple>
#include <iostream>

class Point3d
{

public:
    Point3d(int _x, int _y, int _z) : x {_x}, y {_y}, z{_z} {}
    ~Point3d() = default;

    bool operator<(const Point3d& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }

    int x;
    int y;
    int z;
};

class Point3dCompare {
    public:
    bool operator()(const Point3d& first, const Point3d& second) const {
        return std::tie(first.x, first.y, first.z) < std::tie(second.x, second.y, second.z);
    }
};

void printSet(const std::set<Point3d, Point3dCompare>& set)
{
    for (const auto& point : set)
    {
        std::cout << "Point(" << point.x << ", " << point.y << ", " << point.z << ")"  << std::endl;
    }
};

void printSet2(const std::set<Point3d>& set)
{
    for (const auto& point : set)
    {
        std::cout << "Point(" << point.x << ", " << point.y << ", " << point.z << ")"  << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    auto coords = std::set<Point3d, Point3dCompare>();
    coords.emplace(Point3d(1,2,3));
    printSet(coords);
    auto coords2 = std::set<Point3d>();
    coords2.emplace(Point3d(4,5,6));
    printSet2(coords2);
    return 0;
}

