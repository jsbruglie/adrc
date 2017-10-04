/** 
* @file prefix.cpp
* @brief Prefix tree header file
* @author Nuno Venturinha
* @author João Borrego
*/

#include "prefix.hpp"

namespace Prefix {

    BinTree::Node *prefixBinTree(char *text_file)
    {
        BinTree::Node *root = NULL;

        std::ifstream infile(text_file);
        if (infile)
        {
            char *prefix = (char *)malloc(256 * (sizeof(char)));
            int next_hop;

            while (infile >> prefix >> next_hop)
            {
                root = BinTree::insert(root, prefix, next_hop);
            }
        }
        else
        {
            std::cerr << "[Error] Could not open input file "<< text_file << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return root;
    }
    
    void printTable(BinTree::Node *root);
    
    int lookUp(BinTree::Node *root, char *address);
    
    int insertPrefix(BinTree::Node *root, char *prefix, int next_hop);
    
    BinTree::Node *deletePrefix(BinTree::Node *root, char *prefix);
    
    QuadTree::Node *binaryToTwoBit(BinTree::Node *root);
    
    void printTableEven(BinTree::Node *root);
}