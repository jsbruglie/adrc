/** 
* @file menu.hpp
* @brief Interface header file
* @author Nuno Venturinha
* @author João Borrego
*/

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include "prefix.hpp"

#define MENU_READ_FILE                  1
#define MENU_PRINT_TABLE                2
#define MENU_LOOKUP                     3
#define MENU_INSERT_PREFIX              4
#define MENU_DELETE_PREFIX              5
#define MENU_CONVERT                    6
#define MENU_PRINT_TABLE_EVEN_LENGTH    7
#define MENU_QUIT                       0

#define PROMPT "> "

namespace Menu {

    /**
     * @brief Prints menu options
     */
    void printOptions();
    
    /**
     * @brief Main menu program loop
     * @param bin_root The binary prefix tree root
     * @param quad_root The quad prefix tree root
     */
    void loop(BinTree::Node **bin_root, QuadTree::Node **quad_root);

    /**
     * @brief Creates a binary prefix tree from a file.
     * @return The root of the binary prefix tree
     */
    BinTree::Node *readFile();

    /**
     * @brief Searches for a next-hop value in a prefix tree for a given address
     * @param bin_root The root of the binary prefix tree
     */
    void lookup(BinTree::Node *bin_root);

    /**
     * @brief Inserts a given prefix and next-hop value in a prefix tree
     * @param bin_root The root of the binary prefix tree
     * @return The root of the binary prefix tree
     */
    BinTree::Node *insertPrefix(BinTree::Node *bin_root);

    /**
     * @brief Removes a prefix from a binary prefix tree
     * @param bin_root The root of a binary prefix tree
     */
    void deletePrefix(BinTree::Node *bin_root);

    /**
     * @brief Frees resources and exits the program
     * @param bin_root The root of the binary prefix tree
     * @param quad_root The root of the quad prefix tree
     */
    void quit(BinTree::Node **bin_root, QuadTree::Node **quad_root);

    /**
     * @brief      Determines if binary string.
     * @param[in]  str   The string
     * @return     True if binary string, False otherwise.
     */
    bool isBinaryString(const std::string &str);
}

#endif