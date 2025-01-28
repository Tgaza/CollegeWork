/* CSCI 200: Lab 4C : A Templated Linked List Class
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#include "Node.hpp"
#include <exception>
#include <iostream>

using namespace std;


#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
template <typename T>
class LinkedList {
	public:
		LinkedList();
		LinkedList(const LinkedList<T>& OTHER);
		~LinkedList();
		LinkedList& operator=(const LinkedList<T>& OTHER);
		T get(const int POS) const;
		int find(const T TARGET) const;
		void insert(const int POS, const T VALUE);
		T max() const;
		T min() const;
		void remove(const int POS);
		void set(const int POS, const T VALUE);
		unsigned int size() const;
		Node<T>* mMakeNodeForValue(const T VALUE);
		void printVals() const;

	private:
		Node<T>* mpHead;
		Node<T>* mpTail;
		unsigned int mSize;
		void linked_list_add_value_to_back(Node<T>*& pHead, Node<T>*& pTail, const T VALUE);
		void linked_list_add_value_to_front(Node<T>*& pHead, Node<T>*& pTail, const T VALUE);
		void linked_list_remove_node_at_front(Node<T>*& pHead, Node<T>*& pTail);
		void linked_list_remove_node_at_back(Node<T>*& pHead, Node<T>*& pTail);
};


#endif // !LINKED_LIST_H


// Method Definitions


template <typename T>
LinkedList<T>::LinkedList() {
	mpHead = nullptr;
	mpTail = nullptr;
	mSize = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& OTHER) {
	mpHead = nullptr;
	mpTail = nullptr;
	mSize = 0;
	if (OTHER.size() != 0) {
		this->mpHead = mMakeNodeForValue(OTHER.get(0));
		this->mpTail = this->mpHead;
		for (unsigned int i = 0; i < OTHER.size(); i++) {
			this->insert(mSize + 1, OTHER.get(i));
		}
	}else {
		mpHead = nullptr;
		mpTail = nullptr;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	if (mpHead != nullptr) {
		Node<T>* pCurrNode = mpHead;
		Node<T>* target = pCurrNode;
		while (pCurrNode != nullptr) {
			pCurrNode = pCurrNode->pNext;
			delete target;
			target = pCurrNode;
		}
	}
	mSize = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& OTHER) {
	this->~LinkedList();
	if (OTHER.size() != 0) {
		this->mpHead = mMakeNodeForValue(OTHER.get(0));
		this->mpTail = this->mpHead;
		for (unsigned int i = 0; i < OTHER.size(); i++) {
			this->insert(mSize + 1, OTHER.get(i));
		}
	}
	else {
		mpHead = nullptr;
		mpTail = nullptr;
	}
	return *this;
}

template <typename T>
void LinkedList<T>::printVals() const {
	const Node<T>* temp = mpHead;
	for (unsigned int i = 0; i < mSize; i++) {
		cout << temp->value << ", ";
		temp = temp->pNext;
	}
	cout << endl;
}

template <typename T>
T LinkedList<T>::get(const int POS) const {
	const Node<T>* pCURR_NODE = mpHead;
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

template <typename T>
int LinkedList<T>::find(const T TARGET) const {
	const Node<T>* pCURR_NODE = mpHead;
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

template <typename T>
void LinkedList<T>::insert(const int POS, const T VALUE) {
	// if position is before the beginning, add to front
	if (POS <= 0 || mpHead == nullptr) {
		linked_list_add_value_to_front(mpHead, mpTail, VALUE);
	}
	else {
		Node<T>* pCurrNode = mpHead;
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
			Node<T>* pNewNode = mMakeNodeForValue(VALUE);
			pNewNode->pNext = pCurrNode->pNext;
			pNewNode->pPrev = pCurrNode;
			pCurrNode->pNext->pPrev = pNewNode;
			pCurrNode->pNext = pNewNode;
		}
	}
	mSize++;
}

template <typename T>
T LinkedList<T>::max() const {
	const Node<T>* pCURR_NODE = mpHead;

	// if list is empty
	if (pCURR_NODE == nullptr) {
		// throw exception
		throw out_of_range("list is empty");
	}

	// traverse list tracking max value present

	T maxVal = pCURR_NODE->value;
	while (pCURR_NODE != nullptr) {
		if (maxVal < pCURR_NODE->value) {
			maxVal = pCURR_NODE->value;
		}
		pCURR_NODE = pCURR_NODE->pNext;
	}
	return maxVal;
}

template <typename T>
T LinkedList<T>::min() const {
	const Node<T>* pCURR_NODE = mpHead;

	// if list is empty
	if (pCURR_NODE == nullptr) {
		// throw exception
		throw out_of_range("list is empty");
	}

	// traverse list tracking min value present
	T minVal = pCURR_NODE->value;
	while (pCURR_NODE != nullptr) {
		if (minVal > pCURR_NODE->value) {
			minVal = pCURR_NODE->value;
		}
		pCURR_NODE = pCURR_NODE->pNext;
	}
	return minVal;
}

template <typename T>
void LinkedList<T>::remove(const int POS) {
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
		Node<T>* pCurrNode = mpHead;
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
			Node<T>* target = pCurrNode;
			pCurrNode = pCurrNode->pNext;
			pCurrNode->pPrev = target->pPrev;
			target->pPrev->pNext = pCurrNode;
			// delete current node
			delete target;
		}
	}
	mSize--;
}

template <typename T>
void LinkedList<T>::set(const int POS, const T VALUE) {
	// if trying to set an invalid spot, or list is empty - do nothing
	if (POS >= 0 && mpHead != nullptr) {
		Node<T>* pCurrNode = mpHead;
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

template <typename T>
unsigned int LinkedList<T>::size() const{
	return mSize;
}

template <typename T>
Node<T>* LinkedList<T>::mMakeNodeForValue(const T VALUE) {
	Node<T>* pNode = new Node<T>;
	pNode->value = VALUE;
	pNode->pNext = nullptr;
	pNode->pPrev = nullptr;
	return pNode;
}

template <typename T>
void LinkedList<T>::linked_list_add_value_to_front(Node<T>*& pHead, Node<T>*& pTail, const T VALUE) {
	// make a new node
	Node<T>* pNewNode = mMakeNodeForValue(VALUE);
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

template <typename T>
void LinkedList<T>::linked_list_add_value_to_back(Node<T>*& pHead, Node<T>*& pTail, const T VALUE) {
	// make new node
	Node<T>* pNewNode = mMakeNodeForValue(VALUE);
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

template <typename T>
void LinkedList<T>::linked_list_remove_node_at_front(Node<T>*& pHead, Node<T>*& pTail) {
	// if list is empty - do nothing
	if (pHead == nullptr) return;
	// store pointer to current head
	Node<T>* pCurrNode = pHead;
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

template <typename T>
void LinkedList<T>::linked_list_remove_node_at_back(Node<T>*& pHead, Node<T>*& pTail) {
	// if list is empty, do nothing
	if (pTail == nullptr) return;
	// store pointer to current tail
	Node<T>* target = pTail;
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
