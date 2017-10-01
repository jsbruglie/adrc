/** 
 * @file binary_tree.cpp
 * @brief Binary tree functions
 * @author Nuno Venturinha
 * @author João Borrego
 */

#include "binary_tree.hpp"

namespace Tree {

   Tree::Node* newNode(uint8_t value){
      Node *new_node = (Node*) malloc(sizeof(Node));
      new_node->value = value;
      new_node->left = NULL;
      new_node->right = NULL;
      return new_node;
   }

   Tree::Node* insert(Tree::Node *root, uint8_t value){
      if (root == NULL){
         return newNode(value);
      } else if (value <= root->value){
         root->left = insert(root->left, value);
      } else{
         root->right = insert(root->right, value);
      }
      return root;
   }

   Tree::Node* destroy(Tree::Node *root){
      if(root != NULL){
         root->left = destroy(root->left);
         root->right = destroy(root->right);
         delete(root);
      }
      return NULL;
   }

   void print(Tree::Node *root, int depth){

      if (root != NULL){
         std::cout
         << std::setw(depth) << " "
         << "[" << (int) root->value << "]"
         << std::endl;
    
         print(root->left,depth+1);
         print(root->right,depth+1);
      } else{
         std::cout
         << std::setw(depth+1) << "X"
         << std::endl;
      }
   }

}