/** 
* @file binary_tree.cpp
* @brief Tree structures functions
* @author Nuno Venturinha
* @author João Borrego
*/

#include "tree.hpp"

namespace BinTree {

    BinTree::Node* newNode(uint8_t value)
    {
        Node *new_node = (Node*) malloc(sizeof(Node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    bool hasNoChildren(BinTree::Node *root)
    {
        if (root != NULL)
            return (root->left == NULL || root->right == NULL);
        return true;
    }

    BinTree::Node* insert(BinTree::Node *root, char *prefix, uint8_t value)
    {

        char key = *prefix;
        Node *cur = root;

        if (root == NULL)
            cur = newNode(EMPTY_NODE);
        if (key == '\0')
            cur->value = value;
        else if (key == '0')
            cur->left = insert(cur->left, prefix+1, value); 
        else if (key == '1')
            cur->right = insert(cur->right, prefix+1, value);

        return cur;
    }

    int remove(BinTree::Node *root, char *prefix)
    {
        char key = *prefix;
        /** Auxiliary flag to determine wuther a node has to removed or kept */
        int aux = NOT_FOUND;

        if (root != NULL)
        {
            if (key == '\0')
            {
                /* If the desired node has no children it can simply be removed */
                if (hasNoChildren(root))
                {
                    aux = REMOVE;
                }
                else
                {
                    root->value = EMPTY_NODE;
                    aux = KEEP;
                }
            }
            else if (key == '0')
            /* TODO - Maybe the node removal code can be further condensed */
            {
                aux = remove(root->left, prefix+1);
                if (aux == REMOVE)
                {
                    free(root->left);
                    root->left = NULL;
                    aux = (root->value == EMPTY_NODE && root->left == NULL)?
                        REMOVE : KEEP;
                }
            }
            else if (key == '1')
            {
                aux = remove(root->right, prefix+1);
                if (aux == REMOVE)
                {
                    free(root->right);
                    root->right = NULL;
                    aux = (root->value == EMPTY_NODE && root->right == NULL)?
                        REMOVE : KEEP;
                }
            }
        }
        return aux;
    }

    BinTree::Node* destroy(BinTree::Node *root)
    {
        if (root != NULL)
        {
            root->left = destroy(root->left);
            root->right = destroy(root->right);
            delete(root);
        }
        return NULL;
    }

    void print(BinTree::Node *root, int depth)
    {
        if (root != NULL)
        {
            std::cout
            << std::setw(depth+1) << " "
            << "└─[" << (int) root->value << "]"
            << std::endl;

            print(root->left,depth+1);
            print(root->right,depth+1);
        }
        else
        {
            std::cout
            << std::setw(depth+1) << " "
            << "└─[NULL]"
            << std::endl;
        }
    }

}

namespace QuadTree {

}
