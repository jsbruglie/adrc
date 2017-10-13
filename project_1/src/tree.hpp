/** 
* @file tree.hpp
* @brief Tree structures header file
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

/* Constants */

#define EMPTY_NODE 0
#define NONE -1
#define NOT_FOUND -2
#define KEEP -3
#define REMOVE -4
#define END_REACHED -5

#define PRINT_PREFIX_WIDTH 28
#define PRINT_VALUE_WIDTH 5

namespace BinTree {

    /** @brief Structure for storing a node of the binary tree */
    typedef struct TreeNodeStruct
    {
        /** Node value */
        int value;
        /** Left child */
        struct TreeNodeStruct *left;
        /** Right child*/
        struct TreeNodeStruct *right;
    }Node;

    /**
     * @brief Creates a new node with a given value
     * @param value The value of the node
     * @return The created node
     */
    BinTree::Node *newNode(int value);

    /**
     * @brief Determines if it has no children.
     * @param root  The root
     * @return True if has no children, False otherwise.
     */
    bool hasNoChildren(BinTree::Node *root);
    
    /**
     * @brief Inserts a node in a tree
     * @param root The root of the tree
     * @param prefix The prefix string
     * @param value The value of the node to be inserted
     * @returns The root of the resulting tree
     */
    BinTree::Node *insert(BinTree::Node *root, const char *prefix, int value);

    /**
     * @brief Removes a given prefix from the tree
     *
     * Handles the removal of a prefix and resulting orphaned nodes
     *
     * @param The root of the tree
     * @param The prefix to be removed
     * @return A flag with the result of the operation
     */
    int remove(BinTree::Node *root, const char *prefix);

    /**
     * @brief Searches for the value of a node for a given address
     * @param root The root of the tree
     * @param address The binary representation of a left/right path in the tree
     * @return The value of the node or a status flag if not found
     */
    int find(BinTree::Node *root, const char *address);

    /** 
     * @brief Destroys a tree recursively
     * @param root The root of the tree
     * @returns NULL
     */
    BinTree::Node *destroy(BinTree::Node *root);

    /** 
     * @brief Prints a tree recursively
     * @param root The root of the tree
     * @param[in] depth The depth of the recursion
     */
    void print(BinTree::Node *root, int depth=0);
    
    /**
     * @brief Prints the prefix table given a prefix tree
     * @param root The root of the tree
     * @param prefix Auxiliary prefix variable that is passed down the recursion
     * @param[in] depth The depth of the recursion
     */
    void printPrefix(BinTree::Node *root, char *prefix, int depth=0);
}

namespace QuadTree {

    /** @brief Structure for storing a node of the quad tree */
    typedef struct TreeNodeStruct
    {
        /** Node value */
        int value;
        /** Node children array */
        struct TreeNodeStruct *children[4];
    }Node;

    /**
     * @brief Creates a new node with a given value
     * @param value The value of the node
     * @return The created node
     */
    QuadTree::Node *newNode(int value);

    /**
     * @brief Inserts a node in a quad tree
     * @param root The root of the quad tree
     * @param prefix The prefix string
     * @param value The value of the node to be inserted
     * @returns The root of the resulting quad tree
     */
    QuadTree::Node *insert(
        QuadTree::Node *root,
        const char *prefix,
        int value);

    /**
     * @brief Converts a binary prefix tree into a quad prefix tree
     * @param bin_root The root of the binary prefix tree
     * @param quad_root The root of the quad prefix tree
     * @param prefix Aux prefix variable that is passed down the recursion
     * @param[in] depth The depth of the recursion
     */
    void convert(
        BinTree::Node *bin_root,
        QuadTree::Node **quad_root,
        char *prefix,
        int depth = 0);
    
    QuadTree::Node *altConvert(
        BinTree::Node* bin,
        QuadTree::Node *quad);

    /** 
     * @brief Destroys a quad tree recursively
     * @param root The root of the tree
     * @returns NULL
     */
    QuadTree::Node *destroy(QuadTree::Node *root);

    /** 
     * @brief Prints a quad tree recursively
     * @param root The root of the tree
     * @param[in] depth The depth of the recursion
     */
    void print(QuadTree::Node *root, int depth=0);

    /**
     * @brief Prints the prefix table given a quad (two-bit) prefix tree
     * @param root The root of the tree
     * @param prefix Auxiliary prefix variable that is passed down the recursion
     * @param[in] depth The depth of the recursion
     */
    void printPrefix(QuadTree::Node *root, char *prefix, int depth=0);
}

#endif
