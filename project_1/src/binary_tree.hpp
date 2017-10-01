/** 
 * @file binary_tree.hpp
 * @brief Binary tree header file
 * @author Nuno Venturinha
 * @author João Borrego
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdint.h>

#include <sstream>
#include <iostream>
#include <iomanip>

namespace Tree {

   /** @brief Structure for storing a node of the binary tree */
   typedef struct TreeNodeStruct{
      /** Node value */
      uint8_t value;
      /** Left child */
      struct TreeNodeStruct *left;
      /** Right child*/
      struct TreeNodeStruct *right;
   }Node;

   /**
    * @brief Inserts a node in a tree
    * @param root The root of the tree
    * @param value The value of the node to be inserted
    * @returns The root of the resulting tree
    */
   Tree::Node *insert(Tree::Node *root, uint8_t value);

   /** 
    * @brief Destroys a tree recursively
    * @param root The root of the tree
    * @returns NULL
    */
   Tree::Node *destroy(Tree::Node *root);

   /** 
    * @brief Prints a tree recursively
    * @param root The root of the tree
    */
   void print(Tree::Node *root, int depth=0);
}

#endif