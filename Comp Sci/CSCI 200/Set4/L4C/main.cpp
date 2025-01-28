/* CSCI 200: Lab 4C : A Templated Linked List Class
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */
#include "LinkedList.hpp"

#include <iostream>
using namespace std;

int main() {

    LinkedList<int> pIntList1 = LinkedList<int>();
    pIntList1.insert(0, 6);
    pIntList1.insert(0, 5);
    pIntList1.insert(5, 7);
    pIntList1.insert(-3, 1);
    pIntList1.insert(1, 2);
    pIntList1.insert(2, 9);
    pIntList1.insert(2, 3);
    pIntList1.printVals();
    pIntList1.set(3,4);
    pIntList1.printVals();
    pIntList1.remove(-2);
    pIntList1.remove(9);
    pIntList1.remove(2);
    cout << pIntList1.get(2) << endl;
    cout << pIntList1.size() << endl;
    pIntList1.printVals();
    LinkedList<int> pIntList2 = LinkedList<int>();
    cout << pIntList2.size() << endl;
    pIntList2 = pIntList1;
    cout << pIntList1.size() << endl;
    cout << pIntList2.size() << endl;
    pIntList1.insert(0, 1);
    pIntList1.insert(0, 0);
    cout << pIntList1.size() << endl;
    cout << pIntList2.size() << endl;
    LinkedList<int> pIntList3(pIntList1);
    pIntList1.insert(10, 8);
    pIntList1.insert(10, 9);

    cout << pIntList1.size() << endl;
    cout << pIntList2.size() << endl;
    cout << pIntList3.size() << endl;

    pIntList1.~LinkedList();
    pIntList2.~LinkedList();
    pIntList3.~LinkedList();


    LinkedList<string> stringList = LinkedList<string>();
    stringList.insert(0, "Hello");
    stringList.insert(1, "World");
    stringList.printVals();
    
    stringList.~LinkedList();

    return 0;
}