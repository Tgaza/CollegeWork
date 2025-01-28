/* Lecture 06 - Debugging
 * cout
 * DEBUG compiler directive
 * gdb
 */
#include <iostream>

using namespace std;

int main() {

    // Variables
    char ans = 'n';
    int fact = 0, prod = 1;

    // Looping errors
    // Keeping looping until we get there!
    cout << "Let's play 'Are we there yet' !" << endl;
    while (ans != 'y'){
        cout << "Are we there yet (y/n)? ";
        cin >> ans;
    }

    // Arithmetic Errors    
    cout << "Calculate the factorial of a number: ";
    cin >> fact;
    for (int i = 1; i <= fact; i++) {
        prod = prod * i;
    }
    cout << fact << "! is equal to " << prod << endl;


    return 0;
}