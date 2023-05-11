/**
 * Methods for the Node class 
 * @file node.cpp
 * @author Joseph Simeone
 * @date May 11, 2023
 */

#include "node.h"

/**
 * Constructs a new Node object
 * @param new_key A new integer key for the Node
 * @param new_parent A Node pointer to the new node's parent Node.
 */
Node::Node(int new_key, Node* new_parent) {
    key = new_key;
    left = nullptr;
    right = nullptr;
    parent = new_parent;
}