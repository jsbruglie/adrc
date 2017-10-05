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
/** TODO */
#define EMPTY_NODE 0
/** TODO */
#define NOT_FOUND 0
/** TODO */
#define KEEP 1
/** TODO */
#define REMOVE -1
/** TODO */
#define END_REACHED -2

namespace BinTree {

    /** @brief Structure for storing a node of the binary tree */
    typedef struct TreeNodeStruct
    {
        /** Node value */
        uint8_t value;
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
    BinTree::Node *newNode(uint8_t value);

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
    BinTree::Node *insert(BinTree::Node *root, char *prefix, uint8_t value);

    /**
     * @brief Removes a given prefix from the tree
     *
     * Handles the removal of a prefix and resulting orphaned nodes
     *
     * @param The root of the tree
     * @param The prefix to be removed
     * @return A flag with the result of the operation
     */
    int remove(BinTree::Node *root, char *prefix);

    /**
     * @brief Searches for the value of a node for a given address
     * @param root The root of the tree
     * @param address The binary representation of a left/right path in the tree
     * @return The value of the node or a status flag if not found
     */
    int find(BinTree::Node *root, char *address);

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

namespace QuadTree {

    /** @brief Structure for storing a node of the quad tree */
    typedef struct TreeNodeStruct
    {
        /** Node value */
        uint8_t value;
        /** Node children array */
        struct TreeNodeStruct *children[4];
    }Node;
}

#endif