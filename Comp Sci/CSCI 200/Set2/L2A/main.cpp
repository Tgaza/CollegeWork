/* CSCI 200: Lab 2A : Secret Moosage
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <fstream>
#include <math.h>

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
    ifstream secretMessage("secretMessage.txt");
    ofstream decipheredMessage("decipheredMessage.txt");

    if ( secretMessage.fail() ) {
        cerr << "Error opening input file";
        return -1;
    } else if ( decipheredMessage.fail() ) {
        cerr << "Error creating output file";
        return -1;
    }

    // read the data and do something with it
    char charr;
    while( secretMessage.get(charr) ) {
        if(charr == '\n'){
            decipheredMessage << endl;
        }else if(charr == '~'){
            decipheredMessage << " ";
        }else{
            decipheredMessage << (char)(charr + 1);
        }
    }

    secretMessage.close();
    decipheredMessage.close();

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}