#include "test_suite.h"
#include "LinkedList.h"

#include <iomanip>
#include <iostream>
using namespace std;

const int MESSAGE_WIDTH = 30;

int test_int(int &testNum, const string MESSAGE, const int LHS, const int RHS)  {
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

int test_node_pointer(int &testNum, const string MESSAGE, const Node* LHS, const Node* RHS)  {
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

int test_node_pointer_not(int &testNum, const string MESSAGE, const Node* LHS, const Node* RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS != RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" == Unexpected: \"" << RHS << "\"\n";
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

void print_header(const std::string SECTION_HEADER) {
    cout << endl;
    const int MSG_LEN = SECTION_HEADER.length();
    const int BOX_WIDTH = MESSAGE_WIDTH*2 + 2;
    const int PADDING_LEFT = (BOX_WIDTH - MSG_LEN) / 2 ;
    const int PADDING_RIGHT = (BOX_WIDTH - MSG_LEN) / 2 + (MSG_LEN % 2 ? 0 : -1);
    cout << "/" << setw(MESSAGE_WIDTH*2) << setfill('-') << right << "\\" << endl;
    cout << setw(PADDING_LEFT) << left << setfill(' ') << "|" << SECTION_HEADER << setw(PADDING_RIGHT) << right << "|";
    cout << endl;
    cout << "\\" << setw(MESSAGE_WIDTH*2) << setfill('-') << right << "/" << endl;
    cout << setfill(' ');
}

bool run_all_tests()  {
    int totalPassed = 0, totalNumTests = 0;

    LinkedList linkedList;

    print_header("Testing Initial Empty List - List {}");

    totalPassed += test_int( totalNumTests, "Testing linked list is empty", linkedList.size(), 0);

    print_header("Inserting value 3 at position 0 - List {3}");

    linkedList.insert(0, 3);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 1);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }

    print_header("Inserting value 5 at position 1 - List {3, 5}");

    linkedList.insert(1, 5);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 2);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }

    print_header("Inserting value 1 at position 1 - List {3, 1, 5}");

    linkedList.insert(1,1);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    
    print_header("Getting positions out of range - List {3, 1, 5}");

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(-3)", linkedList.get(-3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-3)", true );  
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(-1)", linkedList.get(-1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );  
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );  
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(5)", linkedList.get(5) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );  
    }

    print_header("Inserting value 2 at position -1 - List {2, 3, 1, 5}");

    linkedList.insert(-1, 2);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 4);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 2);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", false );    
    }

    print_header("Inserting value 4 at position 6 - List {2, 3, 1, 5, 4}");
    
    linkedList.insert(6, 4);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 5);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 2);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(4)", linkedList.get(4), 4);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", false );    
    }

    print_header("Testing accessing the list - List {2, 3, 1, 5, 4}");

    totalPassed += test_int( totalNumTests, "Testing min", linkedList.min(), 1);

    totalPassed += test_int( totalNumTests, "Testing max", linkedList.max(), 5);

    totalPassed += test_int( totalNumTests, "Testing find(0)", linkedList.find(0), -1);
    totalPassed += test_int( totalNumTests, "Testing find(1)", linkedList.find(1), 2);
    totalPassed += test_int( totalNumTests, "Testing find(2)", linkedList.find(2), 0);
    totalPassed += test_int( totalNumTests, "Testing find(3)", linkedList.find(3), 1);
    totalPassed += test_int( totalNumTests, "Testing find(4)", linkedList.find(4), 4);
    totalPassed += test_int( totalNumTests, "Testing find(5)", linkedList.find(5), 3);
    totalPassed += test_int( totalNumTests, "Testing find(6)", linkedList.find(6), -1);

    print_header("Removing element 0 - List {3, 1, 5, 4}");

    linkedList.remove(0);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 4);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), 4);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(4)", linkedList.get(4) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );    
    }

    print_header("Removing element 3 - List {3, 1, 5}");

    linkedList.remove(3);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(4)", linkedList.get(4) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );    
    }

    print_header("Removing element 1 - List {3, 5}");

    linkedList.remove(1);
    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 2);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 3);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(2)", linkedList.get(2) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(4)", linkedList.get(4) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );    
    }

    print_header("Removing element -1 - List {5}");

    linkedList.remove(-1);
    
    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 1);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 5);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(1)", linkedList.get(1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(2)", linkedList.get(2) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(4)", linkedList.get(4) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );    
    }

    print_header("Removing element 4 - List {}");

    linkedList.remove(4);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(0)", linkedList.get(0) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(1)", linkedList.get(1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(2)", linkedList.get(2) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(4)", linkedList.get(4) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );    
    }

    print_header("Performing Tests on empty list - List {}");

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);

    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), -1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );  
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), -1);
    }  catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );  
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(-1)", linkedList.get(-1), -1);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );  
    }

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing min", linkedList.min() && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing min", true );    
    }

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing max", linkedList.max() && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing max", true );    
    }

    totalPassed += test_int( totalNumTests, "Testing find(1)", linkedList.find(1), -1);

    print_header("Removing element 0 from empty list - List {}");

    linkedList.remove(0);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);

    print_header("Removing element -2 from empty list - List {}");

    linkedList.remove(-2);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);

    print_header("Removing element 2 from empty list - List {}");

    linkedList.remove(2);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);

    print_header("Inserting value 7 at position 0 - List {7}");

    linkedList.insert(0, 7);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 1);

    print_header("Inserting value 11 at position 0 - List {11, 7}");

    linkedList.insert(0, 11);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 2);

    print_header("Inserting value 13 at position 0 - List {13, 11, 7}");

    linkedList.insert(0, 13);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);

    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 11);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }

    print_header("Setting position 1 to 15 - List {13, 15, 7}");
    
    linkedList.set(1, 15);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }

    print_header("Setting position -1 to 17 - List {13, 15, 7}");

    linkedList.set(-1, 17);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(-1)", linkedList.get(-1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 7);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }

    print_header("Setting position 4 to 17 - List {13, 15, 7}");

    linkedList.set(4, 17);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(-1)", linkedList.get(-1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 7);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }

    print_header("Setting position 2 to 13 - List {13, 15, 13}");
    
    linkedList.set(2, 13);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }

    print_header("Inserting value 15 to positiong 5 - List {13, 15, 13, 15}");
    
    linkedList.insert(5, 15);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 4);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", false );    
    }

    print_header("Testing accessing the list - List {13, 15, 13, 15}");

    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(-1)", linkedList.get(-1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(3)", linkedList.get(3), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", false );    
    }

    try {
        totalPassed += test_int( totalNumTests, "Testing min", linkedList.min(), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing min", false );    
    }

    try {
        totalPassed += test_int( totalNumTests, "Testing max", linkedList.max(), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing max", false );    
    }

    totalPassed += test_int( totalNumTests, "Testing find(13)", linkedList.find(13), 0);
    totalPassed += test_int( totalNumTests, "Testing find(15)", linkedList.find(15), 1);
    totalPassed += test_int( totalNumTests, "Testing find(5)", linkedList.find(5), -1);

    print_header("Removing element 0 - List {15, 13, 15}");

    linkedList.remove(0);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 3);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(2)", linkedList.get(2), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(3)", linkedList.get(3) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );    
    }

    print_header("Removing element 0 - List {13, 15}");

    linkedList.remove(0);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 2);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_int( totalNumTests, "Testing get(1)", linkedList.get(1), 15);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(2)", linkedList.get(2) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );    
    }

    print_header("Removing element 1 - List {13}");

    linkedList.remove(1);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 1);
    try {
        totalPassed += test_int( totalNumTests, "Testing get(0)", linkedList.get(0), 13);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );    
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(1)", linkedList.get(1) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );    
    }

    print_header("Removing element 1 - List {}");

    linkedList.remove(1);

    totalPassed += test_int( totalNumTests, "Testing size", linkedList.size(), 0);
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get(0)", linkedList.get(0) && false);
    } catch (std::out_of_range oore) {
        totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );    
    }

    print_header("Completion Check");

    totalPassed += test_int( totalNumTests, "Testing All Tests Passed", totalPassed, totalNumTests);
    
    cout << endl;
    cout << "Tests Passed: " << setw(3) << right << totalPassed << " / " << setw(3) << totalNumTests << " (" << setprecision(0) << fixed << totalPassed * 100.0f / totalNumTests << "%)" << endl << endl;
    return (totalPassed == totalNumTests);
}