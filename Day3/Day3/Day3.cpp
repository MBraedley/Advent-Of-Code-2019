// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <map>
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

void MapWire(std::string& line, std::multimap<Point, int>& wire1)
{
    char dir;
    int dist;
    char comma;
    int totalDistance = 0;

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
            wire1.insert({ lastPoint, ++totalDistance });
        }
    }
}

int Distance(const Point& point)
{
    return abs(point.x) + abs(point.y);
}

int main()
{
    std::multimap<Point, int> wire1;
    std::multimap<Point, int> wire2;

    std::ifstream input("input.txt");

    std::string line;
    input >> line;
    line.append(",");

    MapWire(line, wire1);

    input >> line;
    line.append(",");

    MapWire(line, wire2);

    int bestPt1 = std::numeric_limits<int>::max();
    int bestPt2 = std::numeric_limits<int>::max();
    for (auto& pnt1 : wire1)
    {
        auto range = wire2.equal_range(pnt1.first);
        for (auto iter = range.first; iter != range.second; iter++)
        {
            if (pnt1.first == iter->first)
            {
                if (Distance(pnt1.first) < bestPt1)
                {
                    bestPt1 = Distance(pnt1.first);
                }
                if (pnt1.second + iter->second < bestPt2)
                {
                    bestPt2 = pnt1.second + iter->second;
                }
            }
        }
    }

    std::cout << bestPt1 << std::endl;
    std::cout << bestPt2 << std::endl;

    return -1;
}
