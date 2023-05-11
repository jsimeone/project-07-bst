/**
 * Methods for the Binary_Search_Tree class
 * @file binary_search_tree.cpp
 * @author Joseph Simeone
 * @date May 11, 2023
 */

#include "binary_search_tree.h"
#include <iostream>
using namespace std;

/**
 * Construct a new, empty Binary_Search_Tree object
 */
Binary_Search_Tree::Binary_Search_Tree() {
    root = nullptr;
    should_jr = false;
}

/**
 * Check whether a BST is empty
 * @return A boolean value representing whether the tree is empty
 */
bool Binary_Search_Tree::empty() {
    return root == nullptr;
}

/**
 * Insert a new Node with given key into the tree
 * @param new_key An integer key for the new Node
 */
void Binary_Search_Tree::insert(int new_key) {
    if (empty()) {
        root = new Node(new_key, nullptr);
        return;
    }
    recursive_insert(root, new_key);
}

/**
 * Uses recursion to insert a Node into its proper place in the tree
 * @param current A Node pointer to the node to start recursing from
 * @param new_key An integer key for the new Node
 */
void Binary_Search_Tree::recursive_insert(Node* current, int new_key) {
    if (current->key > new_key) {
        if (current->left == nullptr) {
            current->left = new Node(new_key, current);
            return;
        }
        recursive_insert(current->left, new_key);
    } else {
        if (current->right == nullptr) {
            current->right = new Node(new_key, current);
            return;
        }
        recursive_insert(current->right, new_key);
    }
}

/**
 * Get the depth of a binary search tree. What is the maximum number of steps one can take to get from the top to bottom
 * @param count An integer key to start counting depth from. Should usually be zero when calling from outside this function
 * @param current A Node pointer to the node to start recursing from
 * @return An integer representing depth
 */
int Binary_Search_Tree::get_depth(int count, Node* current) {
    int count_left = 0;
    int count_right = 0;

    if (current->left != nullptr) {
        count_left = get_depth(count, current->left);
    }
    if (current->right != nullptr) {
        count_right = get_depth(count, current->right);
    }

    return count + max(count_left, count_right) + 1;
}

/**
 * Display the BST
 */
void Binary_Search_Tree::display() {
    recursive_display(root);
    cout << endl;
}

/**
 * Uses recursion to display the entire tree
 * @param current A Node pointer to the node to start recursing from. Should probably be root when calling from outside this function
 */
void Binary_Search_Tree::recursive_display(Node* current) {
    cout << "key: " << current->key << " parent: ";
    if (current->parent != nullptr) {
        cout << current->parent->key << endl;
    } else {
        cout << "none" << endl;
    }
    if (current->left != nullptr) {
        recursive_display(current->left);
    }  
    if (current->right != nullptr) {
        recursive_display(current->right);
    } 
}

/**
 * Find the Node with a given key in the BST
 * @param key The key to locate
 * @return A Node pointer to the Node with given key
 */
Node* Binary_Search_Tree::locate(int key) {
    return recursive_locate(key, root);
}

/**
 * Use recursion to locate a Node with given key in the tree.
 * @param key The key to search for
 * @param current A Node pointer to the node to start recursing from
 * @return A Node pointer to the Node with given key
 */
Node* Binary_Search_Tree::recursive_locate(int key, Node* current) {
    if (current == nullptr) {
        return nullptr;
    }
    if (current->key == key) {
        return current;
    } else if (current->key > key) {
        Node* value = recursive_locate(key, current->left);
        return value;
    } else {
        Node* value = recursive_locate(key, current->right);
        return value;
    }
}

/**
 * Find the largest Node to the left of a given Node
 * @param n A Node pointer to the node to check
 * @return A Node pointer to the largest left Node
 */
Node* Binary_Search_Tree::largest_to_left(Node* n) {
    if (n->left == nullptr) {
        return nullptr;
    }
    Node* current = n->left;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

/**
 * Check whether a Node is the left child of its parent
 * @param n The Node pointer to check the parent of
 * @return Whether or not the given Node is the left child of its parent
 */
bool Binary_Search_Tree::is_left_child(Node* n) {
    if (n == n->parent->left) {
        return true;
    }
    return false;
}

/**
 * Remove a Node pointer from a tree or call the appropriate auxiliary method to do so
 * @param n A pointer to the Node to remove
 */
void Binary_Search_Tree::remove(Node* n) {
    if (n->left == nullptr && n->right == nullptr) {
        if (is_left_child(n)) {
            n->parent->left = nullptr;
        } else {
            n->parent->right = nullptr;
        }
        cout << "Removal result:" << endl;
        display();
    } else if ((n->left != nullptr && n->right == nullptr)||(n->left == nullptr && n->right != nullptr)) {

        if (n->left != nullptr) {
            n->left->parent = n->parent;
        } else {
            n->right->parent = n->parent;
        }

        if (n->left != nullptr) {
            if (is_left_child(n)) {
                n->parent->left = n->left;
            } else {
                n->parent->right = n->left;
            }
        } else {
            if (is_left_child(n)) {
                n->parent->left = n->right;
            } else {
                n->parent->right = n->right;
            }
        }
        cout << "Removal result:" << endl;
        display();
    } else {
        if (should_jr) {
            jr_remove(n);
        } else {
            two_children_remove(n);
        }
    }
}

/**
 * Remove a Node with two children using the normal method
 * @param n A pointer to the Node to remove
 */
void Binary_Search_Tree::two_children_remove(Node* n) {
    Node* largest_left = largest_to_left(n);
    n->key = largest_left->key;
    remove(largest_left);
    cout << "Height of normal remove: " << get_depth(0, root) << endl;
}

/**
 * Remove a Node with two children using the JR removal method
 * @param n A pointer to the Node to remove
 */
void Binary_Search_Tree::jr_remove(Node* n) {
    Node* largest_left = largest_to_left(n);
    largest_left->right = n->right;

    if (n == root) {
        n->left->parent = nullptr;
        root = n->left;

        if (n->right != nullptr) {
            n->right->parent = largest_left;
        }
    } else if (!is_left_child(n)) {
        largest_left->right->parent = largest_left;
        n->parent->right = n->left;
        n->left->parent = n->parent;
    } else {
        n->parent->left = n->left;
        n->left->parent = n->parent;
        n->right->parent = largest_left;
    }
    cout << "JR removal result:" << endl;
    display();
    cout << "Height of JR remove: " << get_depth(0, root) << endl;
}