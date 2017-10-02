/** 
 * @file binary_tree.hpp
 * @brief Binary tree header file
 * @author Nuno Venturinha
 * @author João Borrego
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define EMPTY_NODE 0

#include <stdlib.h>
#include <stdint.h>

#include <sstream>
#include <iostream>
#include <iomanip>

namespace BinTree {

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
    * @param prefix The prefix string
    * @param value The value of the node to be inserted
    * @returns The root of the resulting tree
    */
   BinTree::Node *insert(BinTree::Node *root, char *prefix, uint8_t value);

   /** 
    * @brief Destroys a tree recursively
    * @param root The root of the tree
    * @returns NULL
    */
   BinTree::Node *destroy(BinTree::Node *root);

   /** 
    * @brief Prints a tree recursively
    * @param root The root of the tree
    */
   void print(BinTree::Node *root, int depth=0);
}

#endif