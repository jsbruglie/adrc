/** 
* @file prefix.hpp
* @brief Prefix tree header file
* @author Nuno Venturinha
* @author João Borrego
*/

#ifndef PREFIX_H
#define PREFIX_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

#include "tree.hpp"

/** The maximum allowed length for a prefix */
#define MAX_PREFIX_LEN 256

namespace Prefix {

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param text_file
     * @return The root of the created prefix tree
     */
    BinTree::Node *prefixBinTree(const char *text_file);

    /**
     * @brief Prints a prefix table given the corresponding prefix tree
     * @param root The root of the prefix tree
     */
    void printTable(BinTree::Node *root);

    /**
     * @brief Searches for a next-hop value in a prefix tree for a given address
     * @param root The root of the prefix tree
     * @param address The destination address
     * @return Next-hop value
     */
    int lookup(BinTree::Node *root, const char *address);

    /**
     * @brief Inserts a given prefix and next-hop value in a prefix tree
     * @param root The root of the prefix tree
     * @param prefix The prefix to be inserted
     * @param next_hop The next-hop value
     * @return The root of the prefix tree
     */
    BinTree::Node *insertPrefix(BinTree::Node *root, const char *prefix, int next_hop);

    /**
     * @brief Removes a prefix from a prefix tree
     * @param root The root of the prefix tree
     */
    void deletePrefix(BinTree::Node *root, const char *prefix);

    /**
     * @brief Creates a two-bit prefix tree from a binary prefix tree 
     * @param root The root of the binary prefix tree
     * @return The root of the quad prefix tree
     */
    QuadTree::Node *binaryToTwoBit(BinTree::Node *root);

    /**
     * @brief Prints a prefix table for a given two-bit prefix tree
     * @param root The root of the quad prefix tree
     */
    void printTableEven(QuadTree::Node *root);
}

#endif