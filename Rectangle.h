#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ShapeTwoD.h"

// Definition of sub-class Rectangle
class Rectangle : public ShapeTwoD
{
    private:
        // Member variable to store list of vertice (x, y) coordinates as pairs
        std::vector <std::pair<int, int>> coordinates;
    
    public:
        // Definition of contructors
        Rectangle();
        Rectangle(std::string name, bool containsWarpSpace, std::vector<std::pair<int, int>> coordinates);
        
        // Definition of accessor methods
        std::vector <std::pair<int, int>> getCoordinates() const;

        // Definition of mutator methods
        void setCoordinates(std::vector<std::pair<int, int>> coordinates);

        // Defintion of toString() method to display object member variables and associated values
        std::string toString();

        // Definition of method to compute and return area of rectangle
        double computeArea() const;

        // Definition of methods to check if a point(x, y) is in shape or on shape
        bool isPointInShape(int x, int y);
        bool isPointOnShape(int x, int y);
        std::vector <std::pair<int, int>> getPointsOnPerimeter();
        std::vector <std::pair<int, int>> getPointsWithinShape();
};

#endif