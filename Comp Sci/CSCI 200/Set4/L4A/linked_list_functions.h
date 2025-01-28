#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include "Node.h"

/**
 * @brief Creates a pointer to a Node whose value is provided.
 * The next and previous pointers are set to be null pointers.
 * 
 * @param VALUE value to set the newly created Node to
 * @return Node* pointer to the newly created Node
 */
Node* linked_list_make_node(const int VALUE);

/**
 * @brief Adds a new node to the front of the provided linked
 * list.  The new node's value is provided and the new node's
 * next pointer points to the provided linked list head.  Upon
 * completion, head will point to the new node that has been 
 * added to the linked list.  If the list is initially empty,
 * then the tail will also point to this new node.
 * 
 * @param pHead reference to the pointer to the linked list head
 * @param pTail reference to the pointer to the linked list tail
 * @param VALUE value to add to the front of the linked list
 */
void linked_list_add_value_to_front(Node*& pHead, Node*& pTail, const int VALUE);

/**
 * @brief Returns the number of nodes in the linked list
 * from the current Node forward
 * 
 * @param P_HEAD constant pointer to the constant linked list head node
 * @param P_TAIL constant pointer to the constant linked list tail node
 * @return int number of nodes in the linked list
 */
int linked_list_get_size(const Node* const P_HEAD, const Node* const P_TAIL);

/**
 * @brief Returns the value of an element in the linked list.  If the
 * position is out of range, throws std::out_of_range exception.
 * 
 * @param P_HEAD constant pointer to the constant linked list head node
 * @param P_TAIL constant pointer to the constant linked list tail node
 * @param POS element position to retrieve the value at
 * @return int if POS is within range, the corresponding element's value
 * @throws std::out_of_range exception if POS out of range
 */
int linked_list_get_value_at_position(const Node* const P_HEAD, const Node* const P_TAIL, const int POS);

/**
 * @brief Sets the value at a given position within a linked list.  If 
 * position is out of range, does not modify the list.
 * 
 * @param P_head constant pointer to the linked list head
 * @param P_tail constant pointer to the linked list tail
 * @param POS element position to set the value at
 * @param VALUE value to set the node to
 */
void linked_list_set_value_at_position(Node* const P_head, Node* const P_tail, const int POS, const int VALUE);

/**
 * @brief Removes the current head node at the front of the provided linked
 * list.  Upon completion, the head pointer will point to the new head of
 * the list.  If the resultant list is empty, the tail will also be a null
 * pointer.
 * 
 * @param pHead reference to the pointer to the linked list head
 * @param pTail reference to the pointer to the linked list tail
 */
void linked_list_remove_node_at_front(Node*& pHead, Node*& pTail);

/**
 * @brief Adds a new node to the back of the provided linked
 * list.  The new node's value is provided and the new node's
 * next previous points to the provided linked list tail.  Upon
 * completion, tail will point to the new node that has been 
 * added to the linked list.  If the list is initially empty,
 * then the head will also point to this new node.
 * 
 * @param pHead reference to the pointer to the linked list head
 * @param pTail reference to the pointer to the linked list tail
 * @param VALUE value to add to the back of the linked list
 */
void linked_list_add_value_to_back(Node*& pHead, Node*& pTail, const int VALUE);

/**
 * @brief Removes the current tail node at the back of the provided linked
 * list.  Upon completion, the tail pointer will point to the new tail of
 * the list.  If the resultant list is empty, the head will also be a null
 * pointer.
 * 
 * @param pHead reference to the pointer to the linked list head
 * @param pTail reference to the pointer to the linked list tail
 */
void linked_list_remove_node_at_back(Node*& pHead, Node*& pTail);

/**
 * @brief Adds a new node before a given position of the provided linked
 * list.  The new node's value is provided and the new node is inserted 
 * into the correct position within the linked list.  If the target position 
 * is before the front of the list, the new node is added to the front. If
 * the target position is beyond the size of the list, the new node is added
 * to the back.  Upon completion, the head and tail pointers will be updated
 * as appropriate.  If the list is initially empty, then the head and tail 
 * will point to this new node.
 * 
 * @param pHead pointer to the linked list head
 * @param pTail pointer to the linked list tail
 * @param POS element position to set the value before
 * @param VALUE value to set the new node to
 */
void linked_list_add_value_before_position(Node*& pHead, Node*& pTail, const int POS, const int VALUE);

/**
 * @brief Returns the minimum value present in the linked list.  If the
 * linked list is empty, throws std::out_of_range exception
 * 
 * @param P_HEAD constant pointer to the constant linked list head node
 * @param P_TAIL constant pointer to the constant linked list tail node
 * @return int minimum value in the linked list
 * @throws std::out_of_range exception if list is empty
 */
int linked_list_min(const Node* const P_HEAD, const Node* const P_TAIL);

/**
 * @brief Returns the maximum value present in the linked list.  If the
 * linked list is empty, throws std::out_of_range exception
 * 
 * @param P_HEAD constant pointer to the constant linked list head node
 * @param P_TAIL constant pointer to the constant linked list tail node
 * @return int maximum value in the linked list
 * @throws std::out_of_range exception if list is empty
 */
int linked_list_max(const Node* const P_HEAD, const Node* const P_TAIL);

/**
 * @brief Returns the index of the first occurrence of target within
 * the linked list.  If the linked list is empty or target is not found,
 * returns -1.
 * 
 * @param P_HEAD constant pointer to the constant linked list head node (haystack)
 * @param P_TAIL constant pointer to the constant linked list tail node (haystack)
 * @param TARGET value to search for (needle)
 * @return int position of first occurrence.  If not found, -1
 */
int linked_list_find(const Node* const P_HEAD, const Node* const P_TAIL, const int TARGET);

/**
 * @brief Removes a node at a given position of the provided linked
 * list.  If the target position is before the front of the list, the 
 * current head will be removed. If the target position is beyond the 
 * size of the list, the tail will be removed to the back.  Upon 
 * completion, the head and tail pointers will be updated as appropriate.  
 * If the resultant list is empty, then the head and tail will be null 
 * pointers.
 * 
 * @param pHead pointer to the linked list head
 * @param pTail pointer to the linked list tail
 * @param POS element position to remove the node at
 */
void linked_list_remove_node_at_position(Node*& pHead, Node*& pTail, const int POS);

#endif