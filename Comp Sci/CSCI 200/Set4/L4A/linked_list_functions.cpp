/* CSCI 200: Lab 4A : Linked List Test Suite
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#include "linked_list_functions.h"
#include "Node.h"

#include <exception>
#include <iostream>
#include <string>

using namespace std;

Node* linked_list_make_node(const int VALUE) {
    Node* pNode = new Node;
    pNode->value = VALUE;
    pNode->pNext = nullptr;
    pNode->pPrev = nullptr;
    return pNode;
}

void linked_list_add_value_to_front(Node*& pHead, Node*& pTail, const int VALUE) {
    // make a new node
    Node* pNewNode = linked_list_make_node(VALUE);      
    // if list is initially empty
    if (pHead == nullptr) {
        // head and tail are the new node                       
        pHead = pNewNode;
        pTail = pNewNode;
    }
    else {
        // otherwise, chain into existing node
            // link new node and head, update head
        pNewNode->pNext = pHead;
        pNewNode->pPrev = nullptr;
        pHead->pPrev = pNewNode;
        pHead = pNewNode;
    }
}

int linked_list_get_size(const Node* const P_HEAD, const Node* const P_TAIL) {
    const Node* pCURR_NODE = P_HEAD;
    int counter = 0;
    // advance through list until end and count number of jumps
    while (pCURR_NODE != nullptr) {
        counter++;
        pCURR_NODE = pCURR_NODE->pNext;
    }
    return counter;
}

int linked_list_get_value_at_position(const Node* const P_HEAD, const Node* const P_TAIL, const int POS) {
    const Node* pCURR_NODE = P_HEAD;
    int counter = 0;
    // advance through list until end and count number of jumps
    while (counter < POS && pCURR_NODE != nullptr) {
        counter++;
        pCURR_NODE = pCURR_NODE->pNext;
    }
    // if valid position, return value
    if (pCURR_NODE != nullptr && POS >= 0) {
        return pCURR_NODE->value;
    }else{
        // otherwise throw excepetion
        throw out_of_range("Position out of bounds of list");
    }
}

void linked_list_set_value_at_position(Node* const P_head, Node* const P_tail, const int POS, const int VALUE) {
    // if trying to set an invalid spot, or list is empty - do nothing
    if (POS >= 0 && P_head != nullptr) {
        Node* pCurrNode = P_head;
        int counter = 0;
        // advance through list until end and count number of jumps
        while (counter < POS && pCurrNode != nullptr){
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
        // if valid position, change value
        if (pCurrNode != nullptr) {
            pCurrNode->value = VALUE;
        }
        // otherwise do nothing
    }
}

void linked_list_remove_node_at_front(Node*& pHead, Node*& pTail) {
    // if list is empty - do nothing
    if(pHead == nullptr) return;
    // store pointer to current head
    Node* pCurrNode = pHead;
    // advance head
    pHead = pHead->pNext;
    // if we're now pointing at nothing, list only had one element
    if (pHead == nullptr) {
        //  set tail to also be null so it points to nothing
        pTail = nullptr;
    }else {
        // otherwise, list still has elements
        // set back pointer to be null
        pHead->pPrev = nullptr;
    }
    // delete former head
    delete pCurrNode;
}

void linked_list_add_value_to_back(Node*& pHead, Node*& pTail, const int VALUE) {
    // make new node
    Node* pNewNode = linked_list_make_node(VALUE);
    // if list is initially empty
    if (pHead == nullptr) {
        // head and tail are the new node                       
        pHead = pNewNode;
        pTail = pNewNode;
    }else {
        // otherwise, chain off existing node
        // link new node and tail, update tail
        pNewNode->pPrev = pTail;
        pTail->pNext = pNewNode;
        pTail = pNewNode;
    }
}

void linked_list_remove_node_at_back(Node*& pHead, Node*& pTail) {
    // if list is empty, do nothing
    if(pTail == nullptr) return;
    // store pointer to current tail
    Node* target = pTail;
    // move tail backwards
    pTail = pTail->pPrev;
    // if we're now pointing at nothing, list only had one element
    if (pTail == nullptr) {
        //  set head to also be null so it points to nothing
        pHead = nullptr;
    }else {
    // otherwise, list still has elements
        // set next pointer to be null
        pTail->pNext = nullptr;
    }
    // delete former tail
    delete target;
}

void linked_list_add_value_before_position(Node*& pHead, Node*& pTail, const int POS, const int VALUE) {
    // if position is before the beginning, add to front
    if(POS <= 0 || pHead == nullptr) {
        linked_list_add_value_to_front(pHead, pTail, VALUE);
    } else {
        Node* pCurrNode = pHead;
        int counter = 0;
        // advance through list until end and count number of jumps
        while (counter < POS-1 && pCurrNode != nullptr) {
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
        // if we have gone past the end
        if(pCurrNode == nullptr) {
            // add to back
            linked_list_add_value_to_back(pHead, pTail, VALUE);
        } else {
            // otherwise add before target position
            Node* pNewNode = linked_list_make_node(VALUE);
            pNewNode->pNext = pCurrNode->pNext;
            pNewNode->pPrev = pCurrNode;
            pCurrNode->pNext->pPrev = pNewNode;
            pCurrNode->pNext = pNewNode;
        }
    }
}

int linked_list_min(const Node* const P_HEAD, const Node* const P_TAIL) {
    const Node* pCURR_NODE = P_HEAD;

    // if list is empty
    if(pCURR_NODE == nullptr) {
        // throw exception
        throw out_of_range("list is empty");
    }

    // traverse list tracking min value present
    int minVal = pCURR_NODE->value;
    while (pCURR_NODE != nullptr) {
        if (minVal > pCURR_NODE->value) {
            minVal = pCURR_NODE->value;
        }
        pCURR_NODE = pCURR_NODE->pNext;
    }
    return minVal;
}

int linked_list_max(const Node* const P_HEAD, const Node* const P_TAIL) {
    const Node* pCURR_NODE = P_HEAD;
    
    // if list is empty
    if(pCURR_NODE == nullptr) {
        // throw exception
        throw out_of_range("list is empty");
    }

    // traverse list tracking max value present

    int maxVal = pCURR_NODE->value;
    while (pCURR_NODE != nullptr) {
        if (maxVal < pCURR_NODE->value) {
            maxVal = pCURR_NODE->value;
        }
        pCURR_NODE = pCURR_NODE->pNext;
    }
    return maxVal;
}

int linked_list_find(const Node* const P_HEAD, const Node* const P_TAIL, const int TARGET) {
    const Node* pCURR_NODE = P_HEAD;
    int counter = 0;
    // advance through list until end and target is found or end reached
    while ( pCURR_NODE != nullptr && pCURR_NODE->value != TARGET) {
        counter++;
        pCURR_NODE = pCURR_NODE->pNext;
    }
    // return found position or -1 if end of list reached
    if (pCURR_NODE == nullptr) {
        counter = -1;
    }
    return counter;
}

void linked_list_remove_node_at_position(Node*& pHead, Node*& pTail, const int POS) {
    // if list is empty
    if(pHead == nullptr) {
        // do nothing
        return;
    } 
    // if position is before start of list
    else if(POS <= 0) {
        // remove from front
        linked_list_remove_node_at_front(pHead, pTail);
    } else {
        Node* pCurrNode = pHead;
        int counter = 0;
        // advance through list until end and count number of jumps
        while (counter < POS && pCurrNode != nullptr) {
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
        // if we have gone to tail or further
        if(pCurrNode == nullptr || pCurrNode == pTail) {
            // remove from back
            linked_list_remove_node_at_back(pHead, pTail);
        } else {
            // unlink current node
            Node* target = pCurrNode;
            pCurrNode = pCurrNode->pNext;
            pCurrNode->pPrev = target->pPrev;
            target->pPrev->pNext = pCurrNode;
            // delete current node
            delete target;
        }
    }
}