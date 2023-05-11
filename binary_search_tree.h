/**
 * Header file for the Binary_Search_Tree class. Class for binary search trees and testing different removal methods on them
 * @file binary_search_tree.h
 * @author Joseph Simeone
 * @date May 11, 2023
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "node.h"

class Binary_Search_Tree {
private:
    Node* root;
public:
    Binary_Search_Tree();
    bool should_jr;
    bool empty();
    void insert(int new_key);
    void recursive_insert(Node* current, int new_key);
    int get_depth(int count, Node* current);
    void display();
    void recursive_display(Node* current);
    Node* locate(int key);
    Node* recursive_locate(int key, Node* current);
    Node* largest_to_left(Node* n);

    bool is_left_child(Node* n);
    void remove(Node* n);
    void two_children_remove(Node* n);
    void jr_remove(Node* n);
};

#endif // BINARY_SEARCH_TREE_H