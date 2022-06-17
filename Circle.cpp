#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iomanip>
#include <utility>
#include <cmath>
#include <algorithm>
#include "Circle.h"
using namespace std;

// Implement constructors
Circle::Circle() : ShapeTwoD() // Call parent class default constructor
{

}

Circle::Circle(string name, bool containsWarpSpace, pair<int, int> center, int radius) : ShapeTwoD(name, containsWarpSpace) // Call parent class other constructor
{
    this->center = center;
    this->radius = radius;
}

// Implement accessor methods
pair<int, int> Circle::getCenter() const
{
    return center;
}

int Circle::getRadius() const
{
    return radius;
}

// Implement mutator methods
void Circle::setCenter(pair<int, int> center)
{
    this->center = center;
}

void Circle::setRadius(int radius)
{
    this->radius = radius;
}

// Implement toString method
string Circle::toString()
{
    // Format string output
    ostringstream ss;
    ss << ShapeTwoD::toString() // Call parent class toString()
    << "\nArea : " << computeArea() << " units square";

    // Format string for circle center and radius info
    ss << "\nCenter Point : " << "(" << center.first << ", " << center.second << ")";
    ss << "\nRadius : " << radius << " units";

    return ss.str();
}

// Implement method to compute and return area of square
double Circle::computeArea() const
{
    return M_PI * radius * radius;
}

// Implement methods to check if a point(x, y) is in shape or on shape
bool Circle::isPointInShape(int x, int y)
{   
    if ((pow((center.first - x), 2) + pow((center.second - y), 2)) < pow(radius, 2))
        return true;
    else
        return false;
}

bool Circle::isPointOnShape(int x, int y)
{
    if ((pow((center.first - x), 2) + pow((center.second - y), 2)) == pow(radius, 2))
        return true;
    else
        return false;
}

// Implement method to get list of North, South, East, West points on perimeter
vector <pair<int, int>> Circle::getPointsOnPerimeter()
{
    // Declare list to store the 4 points (North, South, East, West) on perimeter
    vector <pair<int, int>> list;

    list.push_back(make_pair(center.first, center.second + radius)); // North coordinates
    list.push_back(make_pair(center.first, center.second - radius)); // South coordinates
    list.push_back(make_pair(center.first + radius, center.second)); // East coordinates
    list.push_back(make_pair(center.first - radius, center.second)); // West coordinates

    return list;
}

// Implement method to get list of points within shape excluding center
vector <pair <int, int>> Circle::getPointsWithinShape()
{
    // Declare list to store points within circle
    vector <pair<int, int>> list;

    // Pretend the circle is in an imaginary square with side equal to the circle's diameter
    // Find the x and y coordinates of the bottom-most, left-most vertex of the imaginary square
    int minX = center.first - radius;
    int minY = center.second - radius;

    // Find the x and y coordinates of the top-most, right-most vertex of the imaginary square
    int maxX = center.first + radius;
    int maxY = center.second + radius;

    // Iterate the points of the shape starting from bottom-most, left-most point to top-most, right-most point
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxY; j++)
        {
            // Check if the point is within the shape
            if (isPointInShape(j, i) && !(j == center.first && i == center.second))
                list.push_back(make_pair(j, i));
        }
    }

    return list;
}