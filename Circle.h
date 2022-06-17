#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"

// Definition of sub-class Circle
class Circle : public ShapeTwoD
{
    private:
        // Definition of member variables
        std::pair<int, int> center;
        int radius;

    public:
        // Definition of contructors
        Circle();
        Circle(std::string name, bool containsWarpSpace, std::pair<int, int> center, int radius);

        // Definition of accessor methods
        std::pair<int, int> getCenter() const;
        int getRadius() const;

        // Definition of mutator methods
        void setCenter(std::pair<int, int> center);
        void setRadius(int radius);

        // Defintion of toString() method to display object member variables and associated values
        std::string toString();

        // Definition of method to compute and return area of circle
        double computeArea() const;

        // Definition of methods to check if a point(x, y) is in shape or on shape
        bool isPointInShape(int x, int y);
        bool isPointOnShape(int x, int y);
        std::vector <std::pair<int, int>> getPointsOnPerimeter();
        std::vector <std::pair<int, int>> getPointsWithinShape();
};

#endif