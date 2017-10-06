/** 
* @file binary_tree.cpp
* @brief Tree structures functions
* @author Nuno Venturinha
* @author João Borrego
*/

#include "tree.hpp"

namespace BinTree {

    BinTree::Node* newNode(int value)
    {
        Node *new_node = (Node *)malloc(sizeof(Node));
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

    BinTree::Node *insert(BinTree::Node *root, const char *prefix, int value)
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

    int remove(BinTree::Node *root, const char *prefix)
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

    int find(BinTree::Node *root, const char *address)
    {
        char key = *address;
        int aux = NOT_FOUND;

        if (root == NULL)
        {
            aux = END_REACHED;
        }
        else
        {
            if (key == '\0')
                aux = root->value;
            else if (key == '0')
                aux = find(root->left, address+1);
            else if (key == '1')
                aux = find(root->right, address+1);
            if (aux == END_REACHED)
                aux = root->value;
        }
        return aux;
    }

    BinTree::Node *destroy(BinTree::Node *root)
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
            << "└─[" << root->value << "]"
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

    void printPrefix(BinTree::Node *root, char *prefix, int depth)
    {
        if (root != NULL)
        {
            if(root->value != 0)
            {
                prefix[depth] = '\0';
                std::cout << prefix << " " << root->value << std::endl;
            }
            
            prefix[depth] = '0';
            printPrefix(root->left, prefix, depth+1);
            
            prefix[depth] = '1';
            printPrefix(root->right, prefix, depth+1);
        }
    }
}

namespace QuadTree {

    QuadTree::Node *newNode(int value)
    {
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->value = value;
        for (int i = 0; i < 4; i++)
            new_node->children[i] = NULL;
        return new_node;
    }

    QuadTree::Node *insert(QuadTree::Node *root, const char *prefix, int value)
    {

        char key[2];

        Node *aux = root;

        if (root == NULL)
            aux = newNode(EMPTY_NODE);
        if (*prefix == '\0')
            aux->value = value;
        else
        {
            key[0] = prefix[0];
            key[1] = prefix[1];
            /* TODO - Make pretty maybe */
            if (key[0] == '0' && key[1] == '0')
                aux->children[0b00] = insert(aux->children[0b00], prefix+2, value); 
            else if (key[0] == '0' && key[1] == '1')
                aux->children[0b01] = insert(aux->children[0b01], prefix+2, value);
            else if (key[0] == '1' && key[1] == '0')
                aux->children[0b10] = insert(aux->children[0b10], prefix+2, value);
            else if (key[0] == '1' && key[1] == '1')
                aux->children[0b11] = insert(aux->children[0b11], prefix+2, value);
        }
        return aux;
    }

    void convert(BinTree::Node *bin_root, QuadTree::Node **quad_root,
        char *prefix, int depth)
    {
        if (bin_root != NULL)
        {
            if (bin_root->value != EMPTY_NODE)
            {
                /* If the prefix has an even number of bits */
                if (depth % 2 == 0)
                {
                    prefix[depth] = '\0';
                    *quad_root = insert(*quad_root, prefix, bin_root->value);
                }
                else
                {
                    prefix[depth] = '0';
                    *quad_root = insert(*quad_root, prefix, bin_root->value);
                    prefix[depth] = '1';
                    *quad_root = insert(*quad_root, prefix, bin_root->value);
                    prefix[depth] = '\0';
                }
            }
            prefix[depth] = '0';
            convert(bin_root->left, quad_root, prefix, depth+1);
            prefix[depth] = '1';
            convert(bin_root->right, quad_root, prefix, depth+1);
            prefix[depth] = '\0';
        }
    }

    QuadTree::Node *destroy(QuadTree::Node *root)
    {
        if (root != NULL)
        {
            for (int i = 0; i < 4; i++)
                root->children[i] = destroy(root->children[i]);
            delete(root);
        }
        return NULL;
    }

    void print(QuadTree::Node *root, int depth)
    {
        if (root != NULL)
        {
            std::cout
            << std::setw(depth+1) << " "
            << "└─[" << root->value << "]"
            << std::endl;

            for (int i = 0; i < 4; i++)
                print(root->children[i], depth+1);
        }
        else
        {
            std::cout
            << std::setw(depth+1) << " "
            << "└─[NULL]"
            << std::endl;
        }
    }

    void printPrefix(QuadTree::Node *root, char *prefix, int depth)
    {
        if (root != NULL)
        {
            if(root->value != 0)
            {
                prefix[depth] = '\0';
                std::cout << prefix << " " << root->value << std::endl;
            }
            
            prefix[depth] = '0'; prefix[depth+1] = '0';
            printPrefix(root->children[0b00], prefix, depth+2);
            prefix[depth] = '0'; prefix[depth+1] = '1';
            printPrefix(root->children[0b01], prefix, depth+2);
            prefix[depth] = '1'; prefix[depth+1] = '0';
            printPrefix(root->children[0b10], prefix, depth+2);
            prefix[depth] = '1'; prefix[depth+1] = '1';
            printPrefix(root->children[0b11], prefix, depth+2);
        }
    }
}
