#ifndef SHAPETWOD_H
#define SHAPETWOD_H

// Definition of abstract class ShapeTwoD
class ShapeTwoD
{   
    protected:
        std::string name;
        bool containsWarpSpace;

    public:
        // Definition of constructors
        ShapeTwoD();
        ShapeTwoD(std::string name, bool containsWarpSpace);
        
        // Definition of accessor methods
        std::string getName() const;
        bool getContainsWarpSpace() const;

        // Definition of mutator methods
        void setName(std::string name);
        void setContainsWarpSpace(bool containsWarpSpace);

        // Definition of helper method to compute distance between two points
        static double computeDist(int x1, int y1, int x2, int y2);

        // Definition of comparator functions to compare between ShapeTwoD objects
        static bool compareAreaAscending(const ShapeTwoD *s1, const ShapeTwoD *s2);

        // Defintion of toString() method to display object member variables and assocaited values
        virtual std::string toString();

        // Definition of abstract methods
        virtual double computeArea() const = 0; // abstract method to compute area
        virtual bool isPointInShape(int x, int y) = 0; // abstract method to check if a point(x, y) is in shape
        virtual bool isPointOnShape(int x, int y) = 0; // abstract method to check if a point(x, y) is on shape
        virtual std::vector <std::pair<int, int>> getPointsOnPerimeter() = 0; // abstract method to get a list of all points on perimeter of shape
        virtual std::vector <std::pair<int, int>> getPointsWithinShape() = 0; // abstract method to get a list of all points within the shape
};

#endif
