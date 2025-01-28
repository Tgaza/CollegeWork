/* CSCI 200: Assignment 4 : A4 - Wild Left Center Right Simulation
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#ifndef NODE_H
#define NODE_H

/**
 * @brief A single element of a linked list
 * 
 */
template <typename T>
struct Node {
	T value;
	Node<T>* pNext;
	Node<T>* pPrev;
};

#endif