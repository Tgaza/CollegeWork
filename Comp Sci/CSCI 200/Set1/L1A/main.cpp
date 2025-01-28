/* CSCI 200: Lab 1A : Math Equation Solver
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <iomanip>
#include <math.h>

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
  double x;
  double y;
  double radius;
  bool validInput = false;
  
  cout << "Calculating distance" << endl;
  cout << "Enter X Value: ";
  while(!validInput){
    try{
      cin >> x;
      validInput = true;
    }catch(exception e){
      cout << endl;
      cout << "Enter X Value: ";
    }
  }
  validInput = false;
  cout << "Enter Y Value: ";
  while(!validInput){
    try{
      cin >> y;
      validInput = true;
    }catch(exception e){
      cout << endl;
      cout << "Enter Y Value: ";
    }
  }
  cout << "Distance: " << fixed << setprecision(2) << (sqrt(x * x + y * y)) << endl;
  cout << endl;
  cout << "Calculating area" << endl;
  validInput = false;
  cout << "Enter radius Value: ";
  while(!validInput){
    try{
      cin >> radius;
      validInput = true;
    }catch(exception e){
      cout << endl;
      cout << "Enter radius Value: ";
    }
  }
  cout << "Area: " << fixed << setprecision(2) << (4.0/3) * M_PI * pow(radius, 3) << endl;
  

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}