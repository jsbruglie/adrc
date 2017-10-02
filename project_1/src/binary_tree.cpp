/** 
* @file binary_tree.cpp
* @brief Binary BinTree functions
* @author Nuno Venturinha
* @author João Borrego
*/

#include "binary_tree.hpp"

namespace BinTree {

    BinTree::Node* newNode(uint8_t value){
        Node *new_node = (Node*) malloc(sizeof(Node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    BinTree::Node* insert(BinTree::Node *root, char *prefix, uint8_t value){

        char key = *prefix;
        Node *cur = root;

        if (root == NULL){
            cur = newNode(EMPTY_NODE);
        } if (key == '\0'){ 
            cur->value = value;
        } else if (key == '0'){
            std::cout << key << std::endl;
            cur->left = insert(cur->left, prefix+1, value); 
        } else if (key == '1'){
            std::cout << key << std::endl;
            cur->right = insert(cur->right, prefix+1, value);
        }
        return cur;
    }

    BinTree::Node* destroy(BinTree::Node *root){
        if(root != NULL){
            root->left = destroy(root->left);
            root->right = destroy(root->right);
            delete(root);
        }
        return NULL;
    }

    void print(BinTree::Node *root, int depth){

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