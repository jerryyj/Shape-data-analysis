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
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Cross.h"
using namespace std;

// Declare prototype functions
void displayMainMenu();
void displaySortOptions();
void deallocateShapesDataMemory();
void inputSensorData();
void computeArea();
void displayShapesReport();
void toUpperCase(string &value);

// Declare sort functors
struct AreaAscendingComparator // sort by aree ascending
{
    bool operator()(const ShapeTwoD *s1, const ShapeTwoD *s2)
    {
      return s1->computeArea() < s2->computeArea();
    }
};

struct AreaDescendingComparator // sort by area descending
{
    bool operator()(const ShapeTwoD *s1, const ShapeTwoD *s2)
    {
        return s1->computeArea() > s2->computeArea();
    }
};

struct SpecialTypeDescendingAreaComparator // sort by special type then area descending for each type
{
    bool operator()(const ShapeTwoD *s1, const ShapeTwoD *s2)
    {
        return (s1->getContainsWarpSpace() > s2->getContainsWarpSpace() || 
        (s1->getContainsWarpSpace() == s2->getContainsWarpSpace() && s1->computeArea() > s2->computeArea()));
    }
};

// Declare global vector of ShapeTwoD pointer type to store shapes data
vector <ShapeTwoD*> shapesData;

int main()
{
    
    // Declare option variable to store user input for menu option
    int option = -1;
    do
    {
        displayMainMenu();

        cout << "Please enter your choice: ";
        cin >> option;

        cin.clear(); // reset failbit
		cin.ignore(10000, '\n'); // clear input buffer

        // swtich-case statement to branch out options
        switch (option)
        {
            case 1:
			{
                // Get user input to store sensor data
				inputSensorData();
                cout << endl << "Record successfully stored. Going back to main menu..." << endl;
			} 
				break;
			case 2:
			{
				computeArea();
			}
				break;
			case 3:
			{
				displayShapesReport();
                cout << endl << "Press <enter> to go back to main menu ...";
                cin.ignore(10000, '\n'); // Ignore up to 10000 characters until user presses enter
			}
				break;
			case 4:
			{
                // Declare variable to store char user input
                char subOption;
                do
                {
                    displaySortOptions();

                    cout << "Please select sort option ('q' to go main menu) : ";
                    cin >> subOption;
                    cin.ignore(10000, '\n'); // clear input buffer

                    switch (subOption)
                    {
                        // Sort data by area (ascending) using comparator function then display the sorted report
                        case 'a':
                        {
                            sort(shapesData.begin(), shapesData.end(), ShapeTwoD::compareAreaAscending);
                            displayShapesReport();
                            cout << endl << "Press <enter> to go back to main menu ...";
                            cin.ignore(10000, '\n'); // Ignore up to 10000 characters until user presses enter
                        }
                            break;
                        // Sort data by area (descending) using comparator function then display the sorted report
                        case 'b':
                        {
                            sort(shapesData.begin(), shapesData.end(), AreaDescendingComparator());
                            displayShapesReport();
                            cout << endl << "Press <enter> to go back to main menu ...";
                            cin.ignore(10000, '\n'); // Ignore up to 10000 characters until user presses enter
                        }
                            break;
                        // Sort data by special type, then area (descending) using comparator function. Then display the sorted report
                        case 'c':
                        {
                            sort(shapesData.begin(), shapesData.end(), SpecialTypeDescendingAreaComparator());
                            displayShapesReport();
                            cout << endl << "Press <enter> to go back to main menu ...";
                            cin.ignore(10000, '\n'); // Ignore up to 10000 characters until user presses enter
                        }
                            break;
                    }   
                }while(!(subOption >= 'a' && subOption <= 'c') && !(subOption == 'q'));
			}
				break;
			case 5:
			{
                // Call function to delete existing sensor data records
				deallocateShapesDataMemory();
                cout << endl << "All existing records successfully removed! Going back to main menu..." << endl;
			}
				break;
            case 6:
            {
                cout << endl << "Exiting program..." << endl << endl;
            }
                break;
            default:
            {
                cout << endl << "Please enter a valid option (1 - 6)" << endl;
            }
                break;
        }
    }while (option != 6);

    // Deallocate memory from pointers of shapesData vector
    deallocateShapesDataMemory();
}

// Function to display student info and main menu options
void displayMainMenu()
{
    // DIsplay header
	cout << endl;
	cout << "Welcome to Shapes Data Program!" << endl;

    // Display menu options
	cout << endl;
    cout << "1)" << '\t' << "Input sensor data" << endl;
	cout << "2)" << '\t' << "Compute area (for all records)" << endl;
	cout << "3)" << '\t' << "Print shapes report" << endl;
	cout << "4)" << '\t' << "Sort shapes data" << endl;
    cout << "5)" << '\t' << "Clear sensor data" << endl;
    cout << "6)" << '\t' << "Quit" << endl;
    cout << endl;
}

// Function to display menu for shape data sorting options
void displaySortOptions()
{
    // Display menu options
    cout << endl;
    cout << "   a)" << "      " << "Sort by area (ascending)" << endl;
    cout << "   b)" << "      " << "Sort by area (descending)" << endl;
    cout << "   c)" << "      " << "Sort by special type and area" << endl;
    cout << endl;
}

// Function to deallocate pointer memory and clear data from shapesData vector
void deallocateShapesDataMemory()
{
    // If no element exists in vector, exit function
    if (shapesData.size() == 0)
        return;

    // Deallocate memory from each pointer element in vector
    for (auto *shPtr : shapesData)
	{
		delete shPtr;
	}

    // Clear elements in vector
    shapesData.clear();
}

// Function for user to input sensor data
void inputSensorData()
{
    cout << endl;
    cout << "[ Input sensor data ] " << endl;

    // Declare input variable to store user input
    string input = "";

    // Declare variables to store shapeData info
    string name;
    bool specialType;

    // Declare boolean variable to store inputValidity
    bool validInput;

    // Get user input for a valid shape name
    do
    {
        cout << "Please enter name of shape : ";
        cin >> input;
        cin.ignore(10000, '\n'); // clear input buffer
        toUpperCase(input); // convert string input to uppercase

        // Validate input
        if (input == "CIRCLE")
        {
            name = "Circle";
            validInput = true;
        }
        else if (input == "SQUARE")
        {
            name = "Square";
            validInput = true;
        }  
        else if (input == "RECTANGLE")
        {
            name = "Rectangle";
            validInput = true;
        }
        else if (input == "CROSS")
        {
            name = "Cross";
            validInput = true;
        }
        else
            validInput = false;
    }while (validInput == false);

    // Get user input for a valid special type
    do
    {
        cout << "Please enter special type : ";
        cin >> input;
        cin.ignore(10000, '\n'); // clear input buffer
        toUpperCase(input); // convert string to uppercase

        // Validate input
        if (input == "WS")
        {
            specialType = true;
            validInput = true;
        }
        else if (input == "NS")
        {
            specialType = false;
            validInput = true;
        }
        else
            validInput = false;
    }while (validInput == false);

    // Get user input for shape values
    if (name == "Circle")
    {
        int centerX;
        int centerY;
        int radius;
        
        // Get user input for x-ordinate of circle center
        cout << endl;
        cout << "Please enter x-ordinate of center : ";
        cin >> centerX;

        // If input is not an integer or is not a postive value, prompt user to re-enter an integer
        while (!cin || centerX <= 0)
        {
            cout << "Error: Please enter a valid positive integer" << endl;
            cout << "Please enter x-ordinate of center : ";
            cin.clear(); // reset failbit
            cin.ignore(10000, '\n'); // clear input buffer
            cin >> centerX;
        }

        cin.ignore(10000, '\n'); // clear input buffer

        // Get user input for y-ordinate of circle center
        cout << "Please enter y-ordinate of center : ";
        cin >> centerY;

        // If input is not an integer or is not a postive value, prompt user to re-enter an integer
        while (!cin || centerY <= 0)
        {
            cout << "Error: Please enter a valid positive integer" << endl;
            cout << "Please enter y-ordinate of center : ";
            cin.clear(); // reset failbit
            cin.ignore(10000, '\n'); // clear input buffer
            cin >> centerY;
        }

        cin.ignore(10000, '\n'); // clear input buffer

        // Get user input for radius of circle
        cout << "Please enter radius (units) : ";
        cin >> radius;

        // If input is not an integer or is not a postive value, prompt user to re-enter an integer
        while (!cin || centerY <= 0)
        {
            cout << "Error: Please enter a valid positive integer" << endl;
            cout << "Please enter radius (units) : ";
            cin.clear(); // reset failbit
            cin.ignore(10000, '\n'); // clear input buffer
            cin >> radius;
        }

        cin.ignore(10000, '\n'); // clear input buffer

        // Construct a dynamic circle object and store the pointer of object to shapesData vector
        ShapeTwoD *circlePtr = new Circle(name, specialType, make_pair(centerX, centerY), radius);
        shapesData.push_back(circlePtr);
    }
    else if (name == "Square")
    {
        vector <pair <int, int>> coordinates;

        // Get user inputs for 4 sets of (x, y) values
        for (int i = 1; i <= 4; i++)
        {
            int x;
            int y;
            bool invalidPt;

            do
            {
                cout << endl;
                // Get user input for x-ordinate of vertex
                cout << "Please enter x-ordinate of pt. " << i << " : ";
                cin >> x;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter x-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> x;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                // Get user input for y-ordinate of vertex
                cout << "Please enter y-ordinate of pt. " << i << " : ";
                cin >> y;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter y-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> y;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                pair <int, int> newPt(x, y);

                // Check if the point entered exists already
                if (find(coordinates.begin(), coordinates.end(), newPt) != coordinates.end())
                {
                    cout << "Error: point (" << x << ", " << y << ") already exists. Please re-enter a valid point" << endl;
                    invalidPt = true;
                }else
                {
                    coordinates.push_back(newPt);
                    invalidPt = false;
                }
            }while (invalidPt == true);
        }

        // Construct a dynamic square object and store the pointer of object to shapesData vector
        ShapeTwoD *squarePtr = new Square(name, specialType, coordinates);
        shapesData.push_back(squarePtr);
    }
    else if (name == "Rectangle")
    {
        vector <pair <int, int>> coordinates;

        // Get user inputs for 4 sets of (x, y) values
        for (int i = 1; i <= 4; i++)
        {
            int x;
            int y;
            bool invalidPt;

            do
            {
                cout << endl;
                // Get user input for x-ordinate of vertex
                cout << "Please enter x-ordinate of pt. " << i << " : ";
                cin >> x;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter x-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> x;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                // Get user input for y-ordinate of vertex
                cout << "Please enter y-ordinate of pt. " << i << " : ";
                cin >> y;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter y-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> y;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                pair <int, int> newPt(x, y);

                // Check if the point entered exists already
                if (find(coordinates.begin(), coordinates.end(), newPt) != coordinates.end())
                {
                    cout << "Error: point (" << x << ", " << y << ") already exists. Please re-enter a valid point" << endl;
                    invalidPt = true;
                }else
                {
                    coordinates.push_back(newPt);
                    invalidPt = false;
                }
            }while (invalidPt == true);
        }

        // Construct a dynamic rectangle object and store the pointer of object to shapesData vector
        ShapeTwoD *rectPtr = new Rectangle(name, specialType, coordinates);
        shapesData.push_back(rectPtr);
    }
    else
    {
        vector <pair <int, int>> coordinates;

        // Get user inputs for 12 sets of (x, y) values
        for (int i = 1; i <= 12; i++)
        {
            int x;
            int y;
            bool invalidPt;

            do
            {
                cout << endl;
                // Get user input for x-ordinate of vertex
                cout << "Please enter x-ordinate of pt. " << i << " : ";
                cin >> x;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter x-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> x;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                // Get user input for y-ordinate of vertex
                cout << "Please enter y-ordinate of pt. " << i << " : ";
                cin >> y;

                // If input is not an integer or is not a postive value, prompt user to re-enter an integer
                while (!cin || x <= 0)
                {
                    cout << "Error: Please enter a valid positive integer" << endl;
                    cout << "Please enter y-ordinate of pt. " << i << " : ";
                    cin.clear(); // reset failbit
                    cin.ignore(10000, '\n'); // clear input buffer
                    cin >> y;
                }

                cin.ignore(10000, '\n'); // clear input buffer

                pair <int, int> newPt(x, y);

                // Check if the point entered exists already
                if (find(coordinates.begin(), coordinates.end(), newPt) != coordinates.end())
                {
                    cout << "Error: point (" << x << ", " << y << ") already exists. Please re-enter a valid point" << endl;
                    invalidPt = true;
                }
                else
                {
                    coordinates.push_back(newPt);
                    invalidPt = false;
                }
            }while (invalidPt == true);
        }

        // Construct a dynamic rectangle object and store the pointer of object to shapesData vector
        ShapeTwoD *crossPtr = new Cross(name, specialType, coordinates);
        shapesData.push_back(crossPtr);
    }
}

// Helper function to convert a string to uppercase
void toUpperCase(string &value)
{
    // Iterate through each character in string and convert it to uppercase
    for (auto &c : value)
         c = toupper(c);
}

// Function to compute area for each shape in shapesData
void computeArea()
{
    if (shapesData.size() == 0)
    {
        cout << endl << "Computation unsuccessful! ( 0 records currently stored )" << endl;
        return;
    }
    
    // Counter variable
    int noOfRecords = 0;

    // Iterate through each shape and call computeArea() polymorphically
    for (auto &shapePtr : shapesData)
    {
        shapePtr->computeArea();
        noOfRecords++;
    }

    cout << endl << "Computation completed! ( " << noOfRecords << " records were updated )" << endl;
}

// Function to display shapes report of stored records
void displayShapesReport()
{
    int noOfRecords = shapesData.size();

    cout << endl << "Total no. of records available = " << noOfRecords << endl;

    // Exit function if no elements exist in vector
    if (noOfRecords == 0)
    {
        return;
    }

    // Iterate through each shape pointer to print shapes report
    for (int i = 0; i < noOfRecords; i++)
    {
        // Dsiplay shape details in string by calling toString() method
        cout << endl << "Shape [" << i << "]" << endl;
        cout << shapesData[i]->toString() << endl;

        // Get list of points on perimeter
        vector <pair<int, int>> ptList = shapesData[i]->getPointsOnPerimeter();

        // Display points on perimeter
        cout << endl;
        if (ptList.empty())
        {
            cout << "Points on perimeter : none!" << endl;
        }
        else
        {
            cout << "Points on perimeter : ";
            for (auto &point : ptList)
            {
                // Check if point is the last element in the vector
                if (&point != &ptList.back())
                    cout << "(" << point.first << ", " << point.second << "), ";
                else
                    cout << "(" << point.first << ", " << point.second << ")" << endl;
            }
        }

        // Get list of points in shape
        ptList = shapesData[i]->getPointsWithinShape();

        // Display points in shape
        cout << endl;
        if (ptList.empty())
        {
            cout << "Points within shape : none!" << endl;
        } 
        else
        {
            cout << "Points within shape : ";
            for (auto &point : ptList)
            {
                // Check if point is the last element in the vector
                if (&point != &ptList.back())
                    cout << "(" << point.first << ", " << point.second << "), ";
                else
                    cout << "(" << point.first << ", " << point.second << ")" << endl;
            }
        }
    }
}

