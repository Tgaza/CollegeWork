#include "test_suite.h"
#include "linked_list_functions.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int MESSAGE_WIDTH = 40;

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

    Node *pHead = nullptr;
    Node *pTail = nullptr;

    print_header("Checking head and tail are null - List is {}");

    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list head is null", pHead, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list tail is null", pTail, nullptr);

    print_header("Adding value 3 to front of list - List is {3}");

    linked_list_add_value_to_front(pHead, pTail, 3);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 3);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    print_header("Adding value 5 to front of list - List is {5, 3}");

    linked_list_add_value_to_front(pHead, pTail, 5);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 5);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing head next is not null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing tail previous is not null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing head and tail are not the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    print_header("Adding value 7 to front of list - List is {7, 5, 3}");

    linked_list_add_value_to_front(pHead, pTail, 7);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Checking positions out of range - List is {7, 5, 3}");
    
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get_value_at_position(-1)", linked_list_get_value_at_position(pHead, pTail, -1) && false);
    } catch (...) {
        totalPassed += test_exception(     totalNumTests, "Testing get_value_at_position(-1)", true );   
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3) && false);
    } catch (...) {
        totalPassed += test_exception(     totalNumTests, "Testing get_value_at_position(3)", true );   
    }
    try {
        totalPassed += test_exception_not( totalNumTests, "Testing get_value_at_position(5)", linked_list_get_value_at_position(pHead, pTail, 5) && false);
    } catch (...) {
        totalPassed += test_exception(     totalNumTests, "Testing get_value_at_position(5)", true );   
    }

    print_header("Setting element 1 to 4 - List is {7, 4, 3}");

    linked_list_set_value_at_position(pHead, pTail, 1, 4);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Setting element 0 to 2 - List is {2, 4, 3}");

    linked_list_set_value_at_position(pHead, pTail, 0, 2);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Setting element 2 to -6 - List is {2, 4, -6}");

    linked_list_set_value_at_position(pHead, pTail, 2, -6);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Setting element -1 to -8 - List is {2, 4, -6}");

    linked_list_set_value_at_position(pHead, pTail, -1, -8);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Setting element 3 to 10 - List is {2, 4, -6}");

    linked_list_set_value_at_position(pHead, pTail, 3, 10);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Setting element 5 to 0 - List is {2, 4, -6}");

    linked_list_set_value_at_position(pHead, pTail, 5, 0);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Removing node from front - List is {4, -6}");

    linked_list_remove_node_at_front(pHead, pTail);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 4);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing head next is not null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing tail previous is not null", pTail->pPrev, nullptr);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Removing node from front - List is {-6}");

    linked_list_remove_node_at_front(pHead, pTail);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, -6);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -6);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), -6);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Removing node from front - List is {}");

    linked_list_remove_node_at_front(pHead, pTail);

    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list head is null", pHead, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list tail is null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Adding value 7 to back of list - List is {7}");

    linked_list_add_value_to_back(pHead, pTail, 7);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    print_header("Adding value 5 to back of list - List is {7, 5}");

    linked_list_add_value_to_back(pHead, pTail, 5);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing head next is not null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing tail previous is not null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing head and tail are not the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    print_header("Adding value 3 to back of list - List is {7, 5, 3}");

    linked_list_add_value_to_back(pHead, pTail, 3);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 3);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Removing node from back - List is {7, 5}");

    linked_list_remove_node_at_back(pHead, pTail);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing head next is not null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing tail previous is not null", pTail->pPrev, nullptr);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Removing node from back - List is {7}");

    linked_list_remove_node_at_back(pHead, pTail);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 7);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Removing node from back - List is {}");

    linked_list_remove_node_at_back(pHead, pTail);

    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list head is null", pHead, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list tail is null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", true );   
    }

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }

    print_header("Adding value -1 to position -3 - List is {-1}");

    linked_list_add_value_before_position(pHead, pTail, -3, -1);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, -1);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -1);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), -1);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    print_header("Removing node from front - List is {}");

    linked_list_remove_node_at_front(pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    print_header("Adding value -5 to position 3 - List is {-5}");

    linked_list_add_value_before_position(pHead, pTail, 3, -5);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, -5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, -5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), -5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    print_header("Removing node from front - List is {}");

    linked_list_remove_node_at_front(pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    print_header("Adding value 5 to position 0 - List is {5}");

    linked_list_add_value_before_position(pHead, pTail, 0, 5);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head next is null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail previous is null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer(     totalNumTests, "Testing head and tail are the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    print_header("Adding value 4 to position 0 - List is {4, 5}");

    linked_list_add_value_before_position(pHead, pTail, 0, 4);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list head is not null", pHead, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 4);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing head next is not null", pHead->pNext, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing head previous is null", pHead->pPrev, nullptr);
    
    totalPassed += test_node_pointer_not( totalNumTests, "Testing linked list tail is not null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 5);
    totalPassed += test_node_pointer(     totalNumTests, "Testing tail next is null", pTail->pNext, nullptr);
    totalPassed += test_node_pointer_not( totalNumTests, "Testing tail previous is not null", pTail->pPrev, nullptr);

    totalPassed += test_node_pointer_not( totalNumTests, "Testing head and tail are not the same", pHead, pTail);

    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    print_header("Adding value 2 to position -3 - List is {2, 4, 5}");

    linked_list_add_value_before_position(pHead, pTail, -3, 2);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 5);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    print_header("Adding value 7 to position 7 - List is {2, 4, 5, 7}");

    linked_list_add_value_before_position(pHead, pTail, 7, 7);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 4);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", false );   
    }

    print_header("Adding value -3 to position 1 - List is {2, -3, 4, 5, 7}");

    linked_list_add_value_before_position(pHead, pTail, 1, -3);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 5);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), -3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(4)", linked_list_get_value_at_position(pHead, pTail, 4), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(4)", false );   
    }

    print_header("Adding value 16 to position 4 - List is {2, -3, 4, 5, 16, 7}");

    linked_list_add_value_before_position(pHead, pTail, 4, 16);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 2);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 6);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 2);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), -3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 4);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(4)", linked_list_get_value_at_position(pHead, pTail, 4), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(4)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(5)", linked_list_get_value_at_position(pHead, pTail, 5), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(5)", false );   
    }

    print_header("Checking list min/max - List is {2, -3, 4, 5, 16, 7}");

    try {
        totalPassed += test_int(          totalNumTests, "Testing min", linked_list_min(pHead, pTail), -3);
    } catch  (...) {
        totalPassed += test_exception(    totalNumTests, "Testing min", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing max", linked_list_max(pHead, pTail), 16);
    } catch  (...) {
        totalPassed += test_exception(    totalNumTests, "Testing max", false );   
    }

    print_header("Finding values - List is {2, -3, 4, 5, 16, 7}");

    totalPassed += test_int(              totalNumTests, "Testing find(2)", linked_list_find(pHead, pTail, 2), 0);
    totalPassed += test_int(              totalNumTests, "Testing find(-3)", linked_list_find(pHead, pTail, -3), 1);
    totalPassed += test_int(              totalNumTests, "Testing find(-2)", linked_list_find(pHead, pTail, -2), -1);

    print_header("Setting element 2 to 16 - List is {2, -3, 16, 5, 16, 7}");

    linked_list_set_value_at_position(pHead, pTail, 2, 16);

    totalPassed += test_int(              totalNumTests, "Testing get_element_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 16);

    print_header("Finding values - List is {2, -3, 16, 5, 16, 7}");

    totalPassed += test_int(              totalNumTests, "Testing find(16)", linked_list_find(pHead, pTail, 16), 2);

    print_header("Removing node from position -5 - List is {-3, 16, 5, 16, 7}");

    linked_list_remove_node_at_position(pHead, pTail, -5);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, -3);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 5);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), -3);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(4)", linked_list_get_value_at_position(pHead, pTail, 4), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(4)", false );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(5)", linked_list_get_value_at_position(pHead, pTail, 5) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(5)", true );   
    }

    print_header("Removing node from position 0 - List is {16, 5, 16, 7}");

    linked_list_remove_node_at_position(pHead, pTail, 0);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 7);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 4);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3), 7);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", false );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(4)", linked_list_get_value_at_position(pHead, pTail, 4) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(4)", true );   
    }

    print_header("Removing node from position 8 - List is {16, 5, 16}");

    linked_list_remove_node_at_position(pHead, pTail, 8);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 3);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 5);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", false );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", true );   
    }

    print_header("Removing node from position 1 - List is {16, 16}");

    linked_list_remove_node_at_position(pHead, pTail, 1);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 2);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }
    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", false );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(2)", linked_list_get_value_at_position(pHead, pTail, 2) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(2)", true );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(3)", linked_list_get_value_at_position(pHead, pTail, 3) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(3)", true );   
    }

    print_header("Removing node from position 1 - List is {16}");

    linked_list_remove_node_at_position(pHead, pTail, 1);

    totalPassed += test_int(              totalNumTests, "Testing head value", pHead->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing tail value", pTail->value, 16);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 1);

    try {
        totalPassed += test_int(          totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0), 16);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", false );   
    }
    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(1)", linked_list_get_value_at_position(pHead, pTail, 1) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(1)", true );   
    }

    print_header("Removing node from position 1 - List is {}");

    linked_list_remove_node_at_position(pHead, pTail, 1);

    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list head is null", pHead, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list tail is null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    try {
        totalPassed += test_exception_not(totalNumTests, "Testing get_value_at_position(0)", linked_list_get_value_at_position(pHead, pTail, 0) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing get_value_at_position(0)", true );   
    }

    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list head is null", pHead, nullptr);
    totalPassed += test_node_pointer(     totalNumTests, "Testing linked list tail is null", pTail, nullptr);
    totalPassed += test_int(              totalNumTests, "Testing linked list size", linked_list_get_size(pHead, pTail), 0);

    print_header("Checking min/max/find on empty list - List is {}");

    try {
        totalPassed += test_exception(    totalNumTests, "Testing min", linked_list_min(pHead, pTail) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing min", true );   
    }

    try {
        totalPassed += test_exception(    totalNumTests, "Testing max", linked_list_max(pHead, pTail) && false);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing max", true );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing find(291)", linked_list_find(pHead, pTail, 291), -1);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing find(291)", false );   
    }

    try {
        totalPassed += test_int(          totalNumTests, "Testing size", linked_list_get_size(pHead, pTail), 0);
    } catch (...) {
        totalPassed += test_exception(    totalNumTests, "Testing size", false );   
    }

    print_header("Sanity Check");

    totalPassed += test_int(              totalNumTests, "Testing all tests passed", totalPassed, totalNumTests);

    cout << endl;
    cout << "Tests Passed: " << setw(3) << right << totalPassed << " / " << setw(3) << totalNumTests << " (" << setprecision(0) << fixed << totalPassed * 100.0f / totalNumTests << "%)" << endl << endl;

    return (totalPassed == totalNumTests);
}