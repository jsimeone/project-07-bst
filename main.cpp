/**
 * Create and test removal methods on binary search trees! 
 * @file main.cpp
 * @author Joseph Simeone
 * @date May 11, 2023
 */

#include <iostream>
#include <vector>
#include "node.h"
#include "binary_search_tree.h"
#include <fstream>

using namespace std;

/**
 * Display a given vector of integers
 * @param vec vector of integers to display
 */
void display(vector<int> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

/**
 * Construct binary search trees from file and test removal methods
 * @param file_name The name of the file to load trees from
 */
void test_from_file(string file_name) {
    ifstream the_file(file_name);

    if (!the_file.is_open()) {
        cout << "File not found: " << file_name << endl;
        throw invalid_argument("File not found: " + file_name);
    }

    Binary_Search_Tree bst;
    Binary_Search_Tree other_bst;
    other_bst.should_jr = true;
    vector<int> file_input;
    int input = 0;

    while (!the_file.eof()) {
        the_file >> input;
        file_input.push_back(input);
    }

    int element_to_remove = file_input.back();
    file_input.pop_back();
    cout << "Element to remove: " << element_to_remove << endl;
    
    for (size_t i = 0; i < file_input.size(); i++) {
        bst.insert(file_input[i]);
        other_bst.insert(file_input[i]);
    }
    
    cout << "--- REMOVING! ---" << endl;
    bst.remove(bst.locate(element_to_remove));
    other_bst.remove(other_bst.locate(element_to_remove));
}

/**
 * Controls the flow of the program
 */
int main(int argc, char ** argv) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << " <commands file name>" << endl;
        throw invalid_argument("Incorrect argument! Must include testing file path");
    }

    string file_name = argv[1];
    test_from_file(file_name);
}   
