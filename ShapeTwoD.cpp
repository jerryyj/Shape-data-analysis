#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iomanip>
#include <utility>
#include <cmath>
#include <algorithm>
#include "ShapeTwoD.h"
using namespace std;

// Implement constructors
ShapeTwoD::ShapeTwoD()
{
    name = "";
    containsWarpSpace = false;
}

ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
}

// Implement accessor and mutator methods
string ShapeTwoD::getName() const
{
    return name;
}

bool ShapeTwoD::getContainsWarpSpace() const
{
    return containsWarpSpace;
}

void ShapeTwoD::setName(string name)
{
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)
{
    this->containsWarpSpace = containsWarpSpace;
}

// Implement toString method
string ShapeTwoD::toString()
{
    string type;
    if (containsWarpSpace)
        type = "WS";
    else
        type = "NS";
    
    ostringstream ss;
    ss << "Name : " << name << "\nSpecial Type : " << type;
    return ss.str();
}

// Implement static utility method to calculate distance between two points
double ShapeTwoD::computeDist(int x1, int y1, int x2, int y2)
{
    // By Pythagoras' Theorem, calculate distance
    return pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
}

// Implement comparator function to compare between ShapeTwoD objects
bool ShapeTwoD::compareAreaAscending(const ShapeTwoD *s1, const ShapeTwoD *s2)
{
    return s1->computeArea() < s2->computeArea();
}