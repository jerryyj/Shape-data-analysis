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
#include "Cross.h"
using namespace std;

// Implement constructors
Cross::Cross() : ShapeTwoD() // Call parent class default constructor
{

}

Cross::Cross(string name, bool containsWarpSpace, vector<pair<int, int>> coordinates) : ShapeTwoD(name, containsWarpSpace) // Call parent class other constructor
{
    this->coordinates = coordinates;
}

// Implement accessor methods
vector <pair<int, int>> Cross::getCoordinates() const
{
    return coordinates;
}

// Implement mutator methods
void Cross::setCoordinates(vector<pair<int, int>> coordinates)
{
    this->coordinates = coordinates;
}

// Implement toString method
string Cross::toString()
{
    // Format string output
    ostringstream ss;
    ss << ShapeTwoD::toString() // Call parent class toString()
    << "\nArea : " << computeArea() << " units square"
    << "\nVertices  :";

    // Format string for cross vertices
    int pointNo = 0;
    for (auto &point : coordinates)
    {
        ss << "\nPoint [" << pointNo << "] : (" << point.first << ", " << point.second << ")";
        pointNo++;
    }

    return ss.str();
}

// Implement method to compute and return area of cross
double Cross::computeArea() const
{
    // Declare variable to store outer rectangle objects
    vector <Rectangle> outerRectList = getOuterRectList();

    // First set area to the area of enclosing rectangle of cross
    int area = outerRectList[0].computeArea();

    // Iterate through the 4 smaller rectangles and subtract their area from the area of the enclosing rectangle
    for (int i = 1; i < outerRectList.size(); i++)
    {
        area -= outerRectList[i].computeArea();
    }

    return area;
}

// Implement methods to check if a point(x, y) is in shape or on shape
bool Cross::isPointInShape(int x, int y)
{   
    // Declare variable to store outer rectangle objects
    vector <Rectangle> outerRectList = getOuterRectList();

    // Check if point is within enclosing rectangle
    if (outerRectList[0].isPointInShape(x, y))
    {
        // Iterate through the 4 smaller rectangles and check if point lies within or on them
        for (int i = 1; i < outerRectList.size(); i++)
        {
            // Return false if point lies within or on either 4 smaller rectangles
            if (outerRectList[i].isPointOnShape(x, y) || outerRectList[i].isPointInShape(x, y))
                return false;
        }

        // Return false if point does not lie within or on either 4 smaller rectangles
        return true;
    }
    else
    {
        // Return false if point is not within enclosing rectangle
        return false;
    }  
}

bool Cross::isPointOnShape(int x, int y)
{
    // Check if point is a vertex of cross
    if (find(coordinates.begin(), coordinates.end(), make_pair(x, y)) != coordinates.end())
        return true;

    // Declare variable to store outer rectangle objects
    vector <Rectangle> outerRectList = getOuterRectList();
    
    // Check if point is within enclosing rectangle
    if (outerRectList[0].isPointInShape(x, y))
    {
        // Iterate through the 4 smaller rectangles and check if point lies on them
        for (int i = 1; i < outerRectList.size(); i++)
        {
            // Return true if point lies on either 4 smaller rectangles
            if (outerRectList[i].isPointOnShape(x, y))
                return true;
        }

        // Return false if point does not lie on either 4 smaller rectangles
        return false;
    }else
    {
        // Check if point is on enclosing rectangle
        if (outerRectList[0].isPointOnShape(x, y))
        {
            // Iterate through the 4 smaller rectangles and check if point lies on them
            for (int i = 1; i < outerRectList.size(); i++)
            {
                // Return false if point lies on either 4 smaller rectangles
                if (outerRectList[i].isPointOnShape(x, y))
                    return false;
            }

            // Return true if point does not lie on either 4 smaller rectangles
            return true;
        }else
        {
            return false;
        }
    }
}

// Implement method to get list of points on perimeter excluding vertices
vector <pair<int, int>> Cross::getPointsOnPerimeter()
{
    // Declare list to store points on perimeter
    vector <pair<int, int>> list;

    // Declare variables to store min/max x and y coordinates among the points of the cross
    int minX = coordinates[0].first;
    int maxX = coordinates[0].first;
    int minY = coordinates[0].second;
    int maxY = coordinates[0].second;

    // Find min/max x and y coordinates among the points of the cross
    for (auto &point : coordinates)
    {
        int x = point.first;
        int y = point.second;
        if (x < minX)
            minX = x;

        if (x > maxX)
            maxX = x;

        if (y < minY)
            minY = y;

        if (y > maxY)
            maxY = y;
    }
    
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
vector <pair<int, int>> Cross::getPointsWithinShape()
{
    // Declare list to store points within cross
    vector <pair<int, int>> list;

    // Declare variables to store min/max x and y coordinates among the points of the cross
    int minX = coordinates[0].first;
    int maxX = coordinates[0].first;
    int minY = coordinates[0].second;
    int maxY = coordinates[0].second;

    // Find min/max x and y coordinates among the points of the cross
    for (auto &point : coordinates)
    {
        int x = point.first;
        int y = point.second;
        if (x < minX)
            minX = x;

        if (x > maxX)
            maxX = x;

        if (y < minY)
            minY = y;

        if (y > maxY)
            maxY = y;
    }

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

vector <Rectangle> Cross::getOuterRectList() const
{
    // Declare variable to store outer rectangle objects
    vector <Rectangle> outerRectList;

    // Declare variables to store min/max x and y coordinates among the points of the cross
    int minX = coordinates[0].first;
    int maxX = coordinates[0].first;
    int minY = coordinates[0].second;
    int maxY = coordinates[0].second;

    // Find min/max x and y coordinates among the points of the cross
    for (auto &point : coordinates)
    {
        int x = point.first;
        int y = point.second;
        if (x < minX)
            minX = x;

        if (x > maxX)
            maxX = x;

        if (y < minY)
            minY = y;

        if (y > maxY)
            maxY = y;
    }

    // Find the points of big enclosing rectangle
    vector <pair <int, int>> bigRectCoord;
    pair <int, int> pt1(minX, minY); // point at bottom-left vertex of rectangle
    pair <int, int> pt2(maxX, maxY); // point at top-right vertex of the rectangle
    pair <int, int> pt3(minX, maxY); // point at top-left vertex of the rectangle
    pair <int, int> pt4(maxX, minY); // point at bottom-right vertex of the rectangle
    bigRectCoord.push_back(pt1);
    bigRectCoord.push_back(pt3);
    bigRectCoord.push_back(pt2);
    bigRectCoord.push_back(pt4); // Add adjacent points sequentially
    outerRectList.push_back(Rectangle("Rectangle", false, bigRectCoord));

    // Find the points of the 4 rectangles at each corner of the cross (North-East, South-East, North-West, South-West)
    // Declare list to store indices of middle points of the cross
    vector <int> midIndices;

    // Find and store indices of middle points of the cross
    for (int i = 0; i < coordinates.size(); i++)
    {
        if (coordinates[i].first != minX && coordinates[i].first != maxX && coordinates[i].second != minY && coordinates[i].second != maxY)
            midIndices.push_back(i);
    }

    // Iterate through mid indices to find, instantiate and store outer rectangles
    for (int index : midIndices)
    {
        pair <int, int> pt1(coordinates[index].first, coordinates[index].second);
        pair <int, int> pt2;
        pair <int, int> pt3;
        int pt4_X;
        int pt4_Y;

        // If the index accesses the first element, use the last element of vector for pt2
        if (index == 0)
        {
            pt2.first = coordinates[11].first;
            pt2.second = coordinates[11].second;
            pt3.first = coordinates[index + 1].first;
            pt3.second = coordinates[index + 1].second;
        }else if (index == 11) // If the index accesses the last element, use the first element for pt3
        {
            pt2.first = coordinates[index - 1].first;
            pt2.second = coordinates[index - 1].second;
            pt3.first = coordinates[0].first;
            pt3.second = coordinates[0].second;
        }else
        {
            pt2.first = coordinates[index - 1].first;
            pt2.second = coordinates[index - 1].second;
            pt3.first = coordinates[index + 1].first;
            pt3.second = coordinates[index + 1].second;
        }

        // Check if rectangle lies on the right side of cross
        if (pt1.first - pt2.first <= 0 && pt1.first - pt3.first <= 0)
        {
            // Check if rectangle lies on the top side of cross
            if (pt1.second - pt2.second <= 0 && pt1.second - pt3.second <= 0)
            {
                pt4_X = max(pt2.first, pt3.first);
                pt4_Y = max(pt2.second, pt3.second);
            }else
            {
                pt4_X = max(pt2.first, pt3.first);
                pt4_Y = min(pt2.second, pt3.second);
            }
        }else
        {
            // Check if rectangle lies on the top side of cross
            if (pt1.second - pt2.second <= 0 && pt1.second - pt3.second <= 0)
            {
                pt4_X = min(pt2.first, pt3.first);
                pt4_Y = max(pt2.second, pt3.second);
            }else
            {
                pt4_X = min(pt2.first, pt3.first);
                pt4_Y = min(pt2.second, pt3.second);
            }
        }
        
        vector <pair <int,int>> coordList;
        coordList.push_back(pt1);
        coordList.push_back(pt2);
        coordList.push_back(make_pair(pt4_X, pt4_Y));
        coordList.push_back(pt3);
        outerRectList.push_back(Rectangle("Rectangle", false, coordList));
    }

    return outerRectList;
}