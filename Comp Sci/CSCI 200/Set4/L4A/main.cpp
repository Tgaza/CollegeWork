#include <iostream>
using namespace std;

#include "test_suite.h"

int main() {

    cout << "Testing your functions..." << endl << endl;
    if( run_all_tests() ) {
        cout << "ALL TESTS PASSED!" << endl;
    } else {
        cout << "Not all tests are passing, errors remain..." << endl;
    }

    return 0;
}