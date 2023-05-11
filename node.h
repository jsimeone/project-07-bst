/**
 * Header file for the Node class. A simple node that knows its key, parent, and children.
 * @file node.h
 * @author Joseph Simeone
 * @date May 11, 2023
 */

#ifndef NODE_H
#define NODE_H

class Node {
    private:
    Node() = delete;
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int new_key, Node* new_parent);
};

#endif // NODE_H