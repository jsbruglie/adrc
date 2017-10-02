/** 
* @file prefix.hpp
* @brief Prefix tree header file
* @author Nuno Venturinha
* @author João Borrego
*/

#ifndef PREFIX_H
#define PREFIX_H

namespace Prefix {

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param text_file
     */
    BinTree::Node *prefixBinTree(char *text_file);

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param root
     */
    void printTable(BinTree::Node *root);

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param address
     * @return Next Hop
     */
    int lookUp(BinTree::Node *root, char *address);

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param address
     * @return Next Hop
     */
    int insertPrefix(BinTree::Node *root, char *prefix, int next_hop);

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param root
     * @return Next Hop
     */
    BinTree::Node *deletePrefix(BinTree::Node *root, char *prefix);

    /**
     * @brief 
     * @param root
     * @return Next Hop
     */
    TwoBitTree::Node *binaryToTwoBit(BinTree::Node *root);

    /**
     * @brief Creates a prefix tree from a table in a text file
     * @param root
     */
    void printTable(BinTree::Node *root);
}

#endif