/* CSCI 200: Lab 4B : Linked List Class Test Suite
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#include "Node.h"

using namespace std;


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList {
	public:
		LinkedList();
		~LinkedList();
		int get(const int POS);
		int find(const int TARGET);
		void insert(const int POS, const int VALUE);
		int max();
		int min();
		void remove(const int POS);
		void set(const int POS, const int VALUE);
		unsigned int size();
		Node* mMakeNodeForValue(const int VALUE);

	private:
		Node* mpHead;
		Node* mpTail;
		unsigned int mSize;
		void linked_list_add_value_to_back(Node*& pHead, Node*& pTail, const int VALUE);
		void linked_list_add_value_to_front(Node*& pHead, Node*& pTail, const int VALUE);
		void linked_list_remove_node_at_front(Node*& pHead, Node*& pTail);
		void linked_list_remove_node_at_back(Node*& pHead, Node*& pTail);
};


#endif // !LINKED_LIST_H
