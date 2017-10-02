/** 
* @file main.cpp
* @brief Main project executable for prefix tables
*
* Detailed description
*
* @author Nuno Venturinha
* @author João Borrego
*/

#include "binary_tree.hpp"

#include <fstream>
#include <string>
#include <iostream>

void readFile(){
    
    std::ifstream infile("test_files/PrefixTable.txt");
    char *prefix = (char *)malloc(256 * (sizeof(char)));
    int next_hop;

    BinTree::Node *root = NULL;

    while (infile >> prefix >> next_hop){
        std::cout
        << "Prefix: " << prefix
        << " Next Hop: " << next_hop << std::endl;

        root = BinTree::insert(root, prefix, next_hop);
    }

    BinTree::print(root);
}

int main(){

   readFile();

    return 0;
}
