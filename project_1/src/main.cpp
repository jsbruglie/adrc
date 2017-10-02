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

void testTree(){
   Tree::Node *root = NULL;
   root = Tree::insert(root, 1);
   root = Tree::insert(root, 4);
   root = Tree::insert(root, 5);
   root = Tree::insert(root, 0);
   root = Tree::insert(root, 7);
   root = Tree::insert(root, 10);
   root = Tree::insert(root, 22);
   Tree::print(root);
   root = Tree::destroy(root);
   Tree::print(root);
}

void printFile(){
	std::string file_name = "test_files/PrefixTable.txt";
	std::ifstream infile(file_name);
	char *prefix = (char *)malloc(256 * (sizeof(char)));
	int next_hop;
	while (infile >> prefix >> next_hop){
		std::cout
		<< "Prefix: " << prefix
		<< " Next Hop: " << next_hop << std::endl;
	}
}

int main(){
   
   printFile();

   return 0;
}
