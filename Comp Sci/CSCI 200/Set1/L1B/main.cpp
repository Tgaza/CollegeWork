/* CSCI 200: Lab 1B : Random Classification
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <iomanip>

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
  double min = 1;
  double max = 0;
  double result;
  double quartile;
  string answer;
  bool validInput = false;
  bool run = true;
  
  while(run){
    do{
        validInput = false;
        cout << "Enter min Value: ";
        //Valid input test doesn't work but i left it in
        //for some reason code breaks if a letter is inputted and instead of catching
        //the exception it just goes haywires
        while(!validInput){
            if(!cin.fail()){
            cin >> min;
            validInput = true;
            }else{
            cout << endl;
            cout << "Enter min Value: ";
            }
        }
        validInput = false;
        cout << "Enter max Value: ";
        while(!validInput){
            if(!cin.fail()){
            cin >> max;
            validInput = true;
            }else{
            cout << endl;
            cout << "Enter max Value: ";
            }
        }
    }while(min >= max);
    result = min + rand()/(RAND_MAX/max);
    cout << "A Random Value is: " << fixed << setprecision(4) << result << endl;
    quartile = (max-min)/4;
    if(result <= min + quartile){
        cout << "This is in the first quartile" << endl;
    }else if(result <= min + quartile*2){
        cout << "This is in the second quartile" << endl;
    }else if(result <= min + quartile*3){
        cout << "This is in the third quartile" << endl;
    }else{
        cout << "This is in the fourth quartile" << endl;
    }

    validInput = false;
    cout << "Would you like another random value?(Y/N)";
    cin >> answer;
    while(!validInput){
        if(answer == "Y"){
            validInput = true;
            run = true;
        }else if(answer == "N"){
            validInput = true;
            run = false;
        }else{
            cout << "Would you like another random value?(Y/N)";
            cin >> answer;
        }
    }
  }
  

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}