/** 
* @file prefix.cpp
* @brief Prefix tree header file
* @author Nuno Venturinha
* @author João Borrego
*/

#include "prefix.hpp"

namespace Prefix {

    BinTree::Node *prefixBinTree(const char *text_file)
    {
        BinTree::Node *root = NULL;

        std::ifstream infile(text_file);
        if (infile)
        {
            char prefix[MAX_PREFIX_LEN] = {'\0'};

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
    
    void printTable(BinTree::Node *root)
    {
        char prefix[MAX_PREFIX_LEN] = {'\0'};
        BinTree::printPrefix(root, prefix);
    }
    
    int lookup(BinTree::Node *root, const char *address)
    {
        int rv = BinTree::find(root, address);
        if (rv == NOT_FOUND || rv == END_REACHED)
            std::cout << "[INFO] Address " << address <<  " is unreachable." << std::endl;
        else
            std::cout << "[INFO] Found next-hop " << rv << " for address " << address << std::endl;
        return rv;
    }
    
    BinTree::Node *insertPrefix(BinTree::Node *root, const char *prefix, int next_hop)
    {
        return BinTree::insert(root, prefix, next_hop);
    }
    
    void deletePrefix(BinTree::Node *root, const char *prefix)
    {
        if (BinTree::remove(root, prefix) == NOT_FOUND)
            std::cout << "[INFO] Could not find desired prefix" << std::endl;
    }
    
    QuadTree::Node *binaryToTwoBit(BinTree::Node *root)
    {
        
        QuadTree::Node *quad_root = NULL;
        char prefix[MAX_PREFIX_LEN] = {'\0'};
        QuadTree::convert(root, &quad_root, prefix);
        return quad_root;
    }
    
    void printTableEven(QuadTree::Node *root)
    {
        char prefix[MAX_PREFIX_LEN] = {'\0'};
        QuadTree::printPrefix(root, prefix);
    }
}