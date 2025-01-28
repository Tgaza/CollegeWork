/* CSCI 200: Lab 4C : A Templated Linked List Class
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
    /**
     * @brief the value of this Node
     * 
     */
    T value;
    /**
     * @brief pointer to the next element of the linked list
     * 
     */
    Node<T> *pNext;
    /**
     * @brief pointer to the previous element of the linked list
     * 
     */
    Node<T> *pPrev;
};

#endif