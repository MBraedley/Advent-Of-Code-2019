// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <cassert>

struct Point
{
    int x;
    int y;

    Point& operator+=(const Point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
};

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Point& lhs, const Point& rhs)
{
    return (lhs.x + lhs.y) < (rhs.x + rhs.y);
}

void MapWire(std::string& line, std::multiset<Point>& wire1)
{
    char dir;
    int dist;
    char comma;

    Point lastPoint = { 0, 0 };
    std::stringstream sstrm1(line);
    while (sstrm1 >> dir >> dist >> comma)
    {
        Point modifier = { 0, 0 };
        switch (dir)
        {
        case 'R':
            modifier.x = 1;
            break;
        case 'L':
            modifier.x = -1;
            break;
        case 'U':
            modifier.y = 1;
            break;
        case 'D':
            modifier.y = -1;
            break;
        default:
            assert(false);
            break;
        }

        for (int i = 0; i < dist; i++)
        {
            lastPoint += modifier;
            wire1.insert(lastPoint);
        }
    }
}

int Distance(const Point& point)
{
    return abs(point.x) + abs(point.y);
}

int main()
{
    std::multiset<Point> wire1;
    std::multiset<Point> wire2;

    std::ifstream input("input.txt");

    std::string line;
    input >> line;
    line.append(",");

    MapWire(line, wire1);

    input >> line;
    line.append(",");

    MapWire(line, wire2);

    int best = std::numeric_limits<int>::max();
    for (const Point& pnt1 : wire1)
    {
        auto range = wire2.equal_range(pnt1);
        for (auto iter = range.first; iter != range.second; iter++)
        {
            if (pnt1 == *iter && Distance(pnt1) < best)
            {
                best = Distance(pnt1);
            }
        }
    }

    std::cout << best << std::endl;

    return -1;
}
