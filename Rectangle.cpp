#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iomanip>
#include <utility>
#include <cmath>
#include <algorithm>
#include "Rectangle.h"
using namespace std;

// Implement constructors
Rectangle::Rectangle() : ShapeTwoD() // Call parent class default constructor
{

}

Rectangle::Rectangle(string name, bool containsWarpSpace, vector<pair<int, int>> coordinates) : ShapeTwoD(name, containsWarpSpace) // Call parent class other constructor
{
    this->coordinates = coordinates;
}

// Implement accessor methods
vector <pair<int, int>> Rectangle::getCoordinates() const
{
    return coordinates;
}

// Implement mutator methods
void Rectangle::setCoordinates(vector<pair<int, int>> coordinates)
{
    this->coordinates = coordinates;
}

// Implement toString method
string Rectangle::toString()
{
    // Format string output
    ostringstream ss;
    ss << ShapeTwoD::toString() // Call parent class toString()
    << "\nArea : " << computeArea() << " units square"
    << "\nVertices  :";

    // Format string for rectangle vertices
    int pointNo = 0;
    for (auto &point : coordinates)
    {
        ss << "\nPoint [" << pointNo << "] : (" << point.first << ", " << point.second << ")";
        pointNo++;
    }
    
    return ss.str();
}

// Implement method to compute and return area of rectangle
double Rectangle::computeArea() const
{
    double length = computeDist(coordinates[0].first, coordinates[0].second, coordinates[1].first, coordinates[1].second);
    double breadth = computeDist(coordinates[1].first, coordinates[1].second, coordinates[2].first, coordinates[2].second);

    return length * breadth;
}

// Implement methods to check if a point(x, y) is in shape or on shape
bool Rectangle::isPointInShape(int x, int y)
{   
    // Find the maximum and minimum x-coordinate of rectangle using x values from diagonally opposite points of rectangle
    int maxX = max(coordinates[0].first, coordinates[2].first);
    int minX = min(coordinates[0].first, coordinates[2].first);

    // Find the maximum and minimum y-coordinate of rectangle using y values from diagonally opposite points of rectangle
    int maxY = max(coordinates[0].second, coordinates[2].second);
    int minY = min(coordinates[0].second, coordinates[2].second);

    // Check if the given point lies within the ranges minX - maxX and minY - maxY (exclusive)
    if (x > minX && x < maxX && y > minY && y < maxY)
        return true;
    else
        return false;
}

bool Rectangle::isPointOnShape(int x, int y)
{
    // Find the maximum and minimum x-coordinate of rectangle using x values from diagonally opposite points of rectangle
    int maxX = max(coordinates[0].first, coordinates[2].first);
    int minX = min(coordinates[0].first, coordinates[2].first);

    // Find the maximum and minimum y-coordinate of rectangle using y values from diagonally opposite points of rectangle
    int maxY = max(coordinates[0].second, coordinates[2].second);
    int minY = min(coordinates[0].second, coordinates[2].second);

    // Check if given x lies on the left or right side of rectangle
    if (x == minX || x == maxX)
    {
        // Check if given y lies between range minY - maxY (inclusive)
        if (y >= minY && y <= maxY)
            return true;
    }

    // Check if given x lies on the top or bottom side of rectangle
    if (y == minY || y == maxY)
    {
        // Check if given x lies betwwen range minX - maxX (inclusive)
        if (x >= minX && x <= maxX)
            return true;
    }

    return false;
}

// Implement method to get list of points on perimeter excluding vertices
vector <pair<int, int>> Rectangle::getPointsOnPerimeter()
{
    // Declare list to store points on perimeter
    vector <pair<int, int>> list;

    // Find the maximum and minimum x-coordinate of rectangle using x values from diagonally opposite points of rectangle
    int maxX = max(coordinates[0].first, coordinates[2].first);
    int minX = min(coordinates[0].first, coordinates[2].first);

    // Find the maximum and minimum y-coordinate of rectangle using y values from diagonally opposite points of rectangle
    int maxY = max(coordinates[0].second, coordinates[2].second);
    int minY = min(coordinates[0].second, coordinates[2].second);

    // Iterate the points of the shape starting from bottom-most, left-most point to top-most, right-most point
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            pair <int, int> xy(j, i);

            // Check that point is not a vertex
            if (find(coordinates.begin(), coordinates.end(), xy) == coordinates.end())
            {
                // Check that point is on perimeter
                if (isPointOnShape(xy.first, xy.second))
                    list.push_back(xy);
            }
        }
    }

    return list;
}

// Implement method to get list of points within shape
vector <pair<int, int>> Rectangle::getPointsWithinShape()
{
    // Declare list to store points within rectangle
    vector <pair<int, int>> list;

    // Find the maximum and minimum x-coordinate of rectangle using x values from diagonally opposite points of rectangle
    int maxX = max(coordinates[0].first, coordinates[2].first);
    int minX = min(coordinates[0].first, coordinates[2].first);

    // Find the maximum and minimum y-coordinate of rectangle using y values from diagonally opposite points of rectangle
    int maxY = max(coordinates[0].second, coordinates[2].second);
    int minY = min(coordinates[0].second, coordinates[2].second);

    // Iterate the points of the shape starting from bottom-most, left-most point to top-most, right-most point
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            pair <int, int> xy(j, i);

            // Check that point is in shape
            if (isPointInShape(xy.first, xy.second))
                list.push_back(xy);
        }
    }

    return list;
}
