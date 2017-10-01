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

int main(){
   
   testTree();

   return 0;
}