/* CSCI 200: Lab 2B : Coordinate Conversion
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <iomanip>
#include "coordinate_conversion.h"

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
    double input1, input2, output1, output2;
    int answer;
    string prompt1, prompt2;
    while(true){
    cout << "Please enter 1 to convert from (r, theta) -> (x, y) or 2 for (x, y) -> (r, theta)." << endl;
    cin >> answer;
    if(cin.fail() || (answer != 1 && answer != 2)){
        cin.clear();
        char badChar;
        do{badChar = cin.get();} while(badChar != '\n');
        continue;
    }else{
        break;
    }
    }
    if(answer == 1){
        prompt1 = "Please enter the radius: ";
        prompt2 = "Please enter the theta(radians as a number): ";
        getInput(prompt1, prompt2, input1, input2);
        polar_to_cartesian(input1, input2, output1, output2);
    } else {
        prompt1 = "Please enter the xCoord: ";
        prompt2 = "Please enter the yCoord: ";
        getInput(prompt1, prompt2, input1, input2);
        cartesian_to_polar(input1, input2, output1, output2);
    }
    
    cout << "(" << input1 << ", " << input2 << ") -> (" << fixed << setprecision(2) << output1 << ", " << output2 << ")" << endl;

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}