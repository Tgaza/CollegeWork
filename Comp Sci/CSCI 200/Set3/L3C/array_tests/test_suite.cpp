#include "test_suite.h"
#include "array_functions.h"

#include <exception>
#include <iomanip>
#include <iostream>
using namespace std;

const int MESSAGE_WIDTH = 35;

int test_int(int& testNum, const string MESSAGE, const int LHS, const int RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_int_pointer(int& testNum, const string MESSAGE, const int* LHS, const int* RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_int_pointer_not(int& testNum, const string MESSAGE, const int* LHS, const int* RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS != RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS != RHS ? 1 : 0;
}

int test_exception(int& testNum, const std::string MESSAGE, const bool EXCEPTION_THROWN) {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (EXCEPTION_THROWN)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Exception improperly thrown\n";
    return EXCEPTION_THROWN ? 1 : 0;
}

int test_exception_not(int& testNum, const std::string MESSAGE, const bool EXCEPTION_NOT_THROWN) {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (EXCEPTION_NOT_THROWN)
        cout << " !!>FAILED<!! This should not occur, function was used incorrectly\n";
    else
        cout << " !!>FAILED<!! Exception not properly thrown\n";
    return 0;
}

bool run_all_tests()  {
    int totalPassed = 0, totalNumTests = 0;

    int *pArray = nullptr;
    totalPassed += test_int_pointer(       totalNumTests,  "Testing array is null",               pArray , nullptr );

    int currArraySize = 10;
    cout << endl << ">>>>> Allocating array to size 10 and initializing to zero <<<<<" << endl;
    array_allocate(pArray, currArraySize);
    totalPassed += test_int_pointer_not(   totalNumTests,  "Testing array_allocate is not null",  pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_allocate size",         currArraySize , 10 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(3)",     array_get_element_at(pArray, currArraySize, 3), 0 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(3)",     false );   
    }
    
    cout << endl << ">>>>> Setting each element to 1 <<<<<" << endl;
    for(int i = 0; i < currArraySize; i++) {
        array_set_element_at(pArray, currArraySize, i, 1);
    }
    try {
       totalPassed += test_int(            totalNumTests,  "Testing array_get_element_at(3)",     array_get_element_at(pArray, currArraySize, 3), 1 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(3)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(7)",     array_get_element_at(pArray, currArraySize, 7), 1 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(7)",     false );
    }
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_get_element_at(-1)",    array_get_element_at(pArray, currArraySize, -1) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(-1)",    true );
    }
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_get_element_at(13)",    array_get_element_at(pArray, currArraySize, 13) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(13)",    true );
    }   
    
    cout << endl << ">>>>> Setting element 3 to 3 <<<<<" << endl;
    array_set_element_at(pArray, currArraySize, 3, 3);
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(3)",     array_get_element_at(pArray, currArraySize, 3), 3 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(3)",     false );   
    }
    
    cout << endl << ">>>>> Dellocating array, setting pointer to null and size to zero <<<<<" << endl;
    array_deallocate(pArray, currArraySize);
    totalPassed += test_int_pointer(       totalNumTests,  "Testing array_deallocate is null",    pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_deallocate size",       currArraySize , 0 );

    cout << endl << ">>>>> Allocating array of size zero <<<<<" << endl;
    array_allocate(pArray, currArraySize);
    totalPassed += test_int_pointer_not(   totalNumTests,  "Testing array_allocate is not null",  pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_allocate size",         currArraySize, 0 );
    
    cout << endl << ">>>>> Inserting 5 at back <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, currArraySize+1, 5);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 1 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0), 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }

    cout << endl << ">>>>> Inserting 3 at back <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, currArraySize, 3);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 2 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0), 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(1)",     array_get_element_at(pArray, currArraySize, 1), 3 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(1)",     false );   
    }
    
    cout << endl << ">>>>> Inserting 2 at front <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, 0, 2);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 3 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(1)",     array_get_element_at(pArray, currArraySize, 1), 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(1)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0), 2 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    
    cout << endl << ">>>>> Inserting -5 at front <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, -5, -5);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 4 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0), -5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    
    cout << endl << ">>>>> Inserting 20 at back <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, 30, 20);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 5 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(4)",     array_get_element_at(pArray, currArraySize, 4), 20 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(4)",     false );   
    }
    
    cout << endl << ">>>>> Inserting 12 before position 2 <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, 2, 12);
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 6 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(1)",     array_get_element_at(pArray, currArraySize, 1), 2 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(1)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(2)",     array_get_element_at(pArray, currArraySize, 2), 12 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(2)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(3)",     array_get_element_at(pArray, currArraySize, 3), 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(3)",     false );   
    }
    
    cout << endl << ">>>>> Checking min/max within array <<<<<" << endl;
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_min",                   array_min(pArray, currArraySize), -5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_min()",                 false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_max",                   array_max(pArray, currArraySize), 20 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_max()",                 false );   
    }
    
    cout << endl << ">>>>> Removing last element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, currArraySize);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 5 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(4)",     array_get_element_at(pArray, currArraySize, currArraySize-1) , 3 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(4)",     false );   
    }
    
    cout << endl << ">>>>> Removing first element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 0);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 4 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0) , 2 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    
    cout << endl << ">>>>> Removing last element <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, currArraySize, 12);
    totalPassed += test_int(               totalNumTests,  "Testing array_find(12)",              array_find(pArray, currArraySize, 12), 1 );
    totalPassed += test_int(               totalNumTests,  "Testing array_find(25)",              array_find(pArray, currArraySize, 25), -1 );
    totalPassed += test_int(               totalNumTests,  "Testing array_find(3)",               array_find(pArray, currArraySize, 3), 3 );

    cout << endl << ">>>>> Removing last element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, currArraySize);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 4 );

    cout << endl << ">>>>> Removing element at position 1 <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 1);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 3 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0) , 2 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(1)",     array_get_element_at(pArray, currArraySize, 1) , 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(1)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(2)",     array_get_element_at(pArray, currArraySize, 2) , 3 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(2)",     false );   
    }

    cout << endl << ">>>>> Removing first element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, -2);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 2 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0) , 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(1)",     array_get_element_at(pArray, currArraySize, 1) , 3 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(1)",     false );   
    }

    cout << endl << ">>>>> Removing last element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 2);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 1 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, currArraySize-1) , 5 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }

    cout << endl << ">>>>> Removing last element <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 2);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 0 );

    cout << endl << ">>>>> Querying empty array <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 2);
    totalPassed += test_int(               totalNumTests,  "Testing array_remove size",           currArraySize , 0 );
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_min",                   array_min(pArray, currArraySize) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_min",                   true );   
    }
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_max",                   array_max(pArray, currArraySize) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_max",                   true );   
    }
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     true );   
    }

    cout << endl << ">>>>> Deallocating empty array <<<<<" << endl;
    array_deallocate(pArray, currArraySize);
    totalPassed += test_int_pointer(       totalNumTests,  "Testing array_deallocate is null",    pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_deallocate size",       currArraySize , 0 );

    cout << endl << ">>>>> Querying null array <<<<<" << endl;
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_min",                   array_min(pArray, currArraySize) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_min",                   true );   
    }
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_max",                   array_max(pArray, currArraySize) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_max",                   true );   
    }
    totalPassed += test_int(               totalNumTests,  "Testing array_find(1)",               array_find(pArray, currArraySize, 1), -1 );
    try {
        totalPassed += test_exception_not( totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0) && false );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     true );   
    }
    
    cout << endl << ">>>>> Removing from null array <<<<<" << endl;
    array_remove_from_position(pArray, currArraySize, 1);
    totalPassed += test_int_pointer(       totalNumTests,  "Testing array is null",               pArray , nullptr );

    cout << endl << ">>>>> Inserting to null array <<<<<" << endl;
    array_insert_at_position(pArray, currArraySize, 2, 12);
    totalPassed += test_int_pointer_not(   totalNumTests,  "Testing array is not null",           pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_insert size",           currArraySize , 1 );
    try {
        totalPassed += test_int(           totalNumTests,  "Testing array_get_element_at(0)",     array_get_element_at(pArray, currArraySize, 0), 12 );
    } catch (...) {
        totalPassed += test_exception(     totalNumTests,  "Testing array_get_element_at(0)",     false );   
    }

    cout << endl << ">>>>> Dellocating array, setting pointer to null and size to zero <<<<<" << endl;
    array_deallocate(pArray, currArraySize);
    totalPassed += test_int_pointer(       totalNumTests,  "Testing array_deallocate is null",    pArray , nullptr );
    totalPassed += test_int(               totalNumTests,  "Testing array_deallocate size",       currArraySize , 0 );
    
    cout << endl;
    cout << "Tests Passed: " << setw(3) << right << totalPassed << " / " << setw(3) << totalNumTests << " (" << setprecision(0) << fixed << totalPassed * 100.0f / totalNumTests << "%)" << endl << endl;
 
    return (totalPassed == totalNumTests);
}