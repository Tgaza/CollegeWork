/* CSCI 200: Lab 4B : Linked List Class Test Suite
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#include "LinkedList.h"
#include "Node.h"
#include <exception>
#include <iostream>

using namespace std;

LinkedList::LinkedList() {
	mpHead = nullptr;
	mpTail = nullptr;
	mSize = 0;
}

LinkedList::~LinkedList() {
	if (mpHead != nullptr) {
		Node* pCurrNode = mpHead;
		Node* target = pCurrNode;
		while (pCurrNode != nullptr) {
			pCurrNode = pCurrNode->pNext;
			delete target;
			target = pCurrNode;
		}
	}
	mSize = 0;
}

int LinkedList::get(const int POS) {
	const Node* pCURR_NODE = mpHead;
	int counter = 0;
	// advance through list until end and count number of jumps
	while (counter < POS && pCURR_NODE != nullptr) {
		counter++;
		pCURR_NODE = pCURR_NODE->pNext;
	}
	// if valid position, return value
	if (pCURR_NODE != nullptr && POS >= 0) {
		return pCURR_NODE->value;
	}
	else {
		// otherwise throw excepetion
		throw out_of_range("Position out of bounds of list");
	}
}

int LinkedList::find(const int TARGET) {
	const Node* pCURR_NODE = mpHead;
	int counter = 0;
	// advance through list until end and target is found or end reached
	while (pCURR_NODE != nullptr && pCURR_NODE->value != TARGET) {
		counter++;
		pCURR_NODE = pCURR_NODE->pNext;
	}
	// return found position or -1 if end of list reached
	if (pCURR_NODE == nullptr) {
		counter = -1;
	}
	return counter;
}

void LinkedList::insert(const int POS, const int VALUE) {
	// if position is before the beginning, add to front
	if (POS <= 0 || mpHead == nullptr) {
		linked_list_add_value_to_front(mpHead, mpTail, VALUE);
	}
	else {
		Node* pCurrNode = mpHead;
		int counter = 0;
		// advance through list until end and count number of jumps
		while (counter < POS - 1 && pCurrNode != nullptr) {
			counter++;
			pCurrNode = pCurrNode->pNext;
		}
		// if we have gone past the end
		if (pCurrNode == nullptr || pCurrNode == mpTail) {
			// add to back
			linked_list_add_value_to_back(mpHead, mpTail, VALUE);
		}
		else {
			// otherwise add before target position
			Node* pNewNode = mMakeNodeForValue(VALUE);
			pNewNode->pNext = pCurrNode->pNext;
			pNewNode->pPrev = pCurrNode;
			pCurrNode->pNext->pPrev = pNewNode;
			pCurrNode->pNext = pNewNode;
		}
	}
}

int LinkedList::max() {
	const Node* pCURR_NODE = mpHead;

	// if list is empty
	if (pCURR_NODE == nullptr) {
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

int LinkedList::min() {
	const Node* pCURR_NODE = mpHead;

	// if list is empty
	if (pCURR_NODE == nullptr) {
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

void LinkedList::remove(const int POS) {
	// if list is empty
	if (mpHead == nullptr) {
		// do nothing
		return;
	}
	// if position is before start of list
	else if (POS <= 0) {
		// remove from front
		linked_list_remove_node_at_front(mpHead, mpTail);
	}
	else {
		Node* pCurrNode = mpHead;
		int counter = 0;
		// advance through list until end and count number of jumps
		while (counter < POS && pCurrNode != nullptr) {
			counter++;
			pCurrNode = pCurrNode->pNext;
		}
		// if we have gone to tail or further
		if (pCurrNode == nullptr || pCurrNode == mpTail) {
			// remove from back
			linked_list_remove_node_at_back(mpHead, mpTail);
		}
		else {
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

void LinkedList::set(const int POS, const int VALUE) {
	// if trying to set an invalid spot, or list is empty - do nothing
	if (POS >= 0 && mpHead != nullptr) {
		Node* pCurrNode = mpHead;
		int counter = 0;
		// advance through list until end and count number of jumps
		while (counter < POS && pCurrNode != nullptr) {
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

unsigned int LinkedList::size() {
	const Node* pCURR_NODE = mpHead;
	int counter = 0;
	// advance through list until end and count number of jumps
	while (pCURR_NODE != nullptr) {
		counter++;
		pCURR_NODE = pCURR_NODE->pNext;
	}
	return counter;
}

Node* LinkedList::mMakeNodeForValue(const int VALUE) {
	Node* pNode = new Node;
	pNode->value = VALUE;
	pNode->pNext = nullptr;
	pNode->pPrev = nullptr;
	return pNode;
}

void LinkedList::linked_list_add_value_to_front(Node*& pHead, Node*& pTail, const int VALUE) {
	// make a new node
	Node* pNewNode = mMakeNodeForValue(VALUE);
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

void LinkedList::linked_list_add_value_to_back(Node*& pHead, Node*& pTail, const int VALUE) {
	// make new node
	Node* pNewNode = mMakeNodeForValue(VALUE);
	// if list is initially empty
	if (pHead == nullptr) {
		// head and tail are the new node                       
		pHead = pNewNode;
		pTail = pNewNode;
	}
	else {
		// otherwise, chain off existing node
		// link new node and tail, update tail
		pNewNode->pPrev = pTail;
		pTail->pNext = pNewNode;
		pTail = pNewNode;
	}
}

void LinkedList::linked_list_remove_node_at_front(Node*& pHead, Node*& pTail) {
	// if list is empty - do nothing
	if (pHead == nullptr) return;
	// store pointer to current head
	Node* pCurrNode = pHead;
	// advance head
	pHead = pHead->pNext;
	// if we're now pointing at nothing, list only had one element
	if (pHead == nullptr) {
		//  set tail to also be null so it points to nothing
		pTail = nullptr;
	}
	else {
		// otherwise, list still has elements
		// set back pointer to be null
		pHead->pPrev = nullptr;
	}
	// delete former head
	delete pCurrNode;
}

void LinkedList::linked_list_remove_node_at_back(Node*& pHead, Node*& pTail) {
	// if list is empty, do nothing
	if (pTail == nullptr) return;
	// store pointer to current tail
	Node* target = pTail;
	// move tail backwards
	pTail = pTail->pPrev;
	// if we're now pointing at nothing, list only had one element
	if (pTail == nullptr) {
		//  set head to also be null so it points to nothing
		pHead = nullptr;
	}
	else {
		// otherwise, list still has elements
			// set next pointer to be null
		pTail->pNext = nullptr;
	}
	// delete former tail
	delete target;
}
