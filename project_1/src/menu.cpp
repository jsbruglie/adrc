/** 
* @file menu.cpp
* @brief Interface functions file
* @author Nuno Venturinha
* @author João Borrego
*/

#include "menu.hpp"

namespace Menu {
    
    void printOptions()
    {
        std::cout << std::endl
        << std::string(30, '#')             << std::endl
        << "# Prefix Tree"                  << std::endl
        << "# 1. Read file"                 << std::endl
        << "# 2. Print prefix table"        << std::endl
        << "# 3. Look up address"           << std::endl
        << "# 4. Insert prefix"             << std::endl
        << "# 5. Delete prefix"             << std::endl
        << "# 6. Convert to two bit tree"   << std::endl
        << "# 7. Print even length table"   << std::endl
        << "# 0. Quit"                      << std::endl
        << std::string(30, '#')             << std::endl;
    };

    void processCommand(int command, BinTree::Node **bin_root, QuadTree::Node **quad_root)
    {
        switch(command)
        {
            case MENU_READ_FILE:
                *bin_root = readFile();
                break;
            case MENU_PRINT_TABLE:
                Prefix::printTable(*bin_root);
                break;
            case MENU_LOOKUP:
                lookup(*bin_root);
                break;
            case MENU_INSERT_PREFIX:
                *bin_root = insertPrefix(*bin_root);
                break;
            case MENU_DELETE_PREFIX:
                deletePrefix(*bin_root);
                break;
            case MENU_CONVERT:
                *quad_root = QuadTree::destroy(*quad_root);
                *quad_root = Prefix::binaryToTwoBit(*bin_root);
                break;
            case MENU_PRINT_TABLE_EVEN_LENGTH:
                Prefix::printTableEven(*quad_root);
                break;
            case MENU_QUIT:
                quit(bin_root, quad_root);
                break;
            default:
                break;
        }
    }

    void loop(BinTree::Node **bin_root, QuadTree::Node **quad_root)
    {
        int command = -1;
        std::string line = "";

        while(std::cout << PROMPT)
        {
            getline(std::cin, line);
            std::stringstream input_stream(line);
            if (input_stream >> command
                && command >= 0 && command <= 7)
            {
                processCommand(command, bin_root, quad_root);
            }
            else
            {
                std::cerr << "[ERROR] Invalid command." << std::endl;
            }
        }
        
    }

    BinTree::Node *readFile()
    {
        std::string line = "";
        std::string file = "";

        std::cout << "[INPUT] Path to file: ";
        
        getline(std::cin, line);
        std::stringstream input_stream(line);
        if (input_stream >> file)
        {
            return Prefix::prefixBinTree(file.c_str());
        }
        return NULL;
    }

    void lookup(BinTree::Node *bin_root)
    {
        std::string line = "";
        std::string address = "";

        std::cout << "[INPUT] Address: ";
        
        getline(std::cin, line);
        std::stringstream input_stream(line);
        if (input_stream >> address)
        {
            if (isBinaryString(address))
                Prefix::lookup(bin_root, address.c_str());
        }
    }

    BinTree::Node *insertPrefix(BinTree::Node *bin_root)
    {
        std::string line = "";
        std::string prefix = "";
        int next_hop = 0;

        std::cout << "[INPUT] Prefix Next-Hop: ";
        
        getline(std::cin, line);
        std::stringstream input_stream(line);
        if (input_stream >> prefix >> next_hop)
        {
            if (isBinaryString(prefix) && next_hop > 0)
                return Prefix::insertPrefix(bin_root, prefix.c_str(), next_hop);
        }
    }

    void deletePrefix(BinTree::Node *bin_root)
    {
        std::string line = "";
        std::string prefix = "";

        std::cout << "[INPUT] Prefix: ";
        
        getline(std::cin, line);
        std::stringstream input_stream(line);
        if (input_stream >> prefix)
        {
            if (isBinaryString(prefix))
                Prefix::deletePrefix(bin_root, prefix.c_str());
        }
    }

    void quit(BinTree::Node **bin_root, QuadTree::Node **quad_root)
    {
        std::cout << "[INFO] Freeing resources and exiting..." << std::endl;
        *bin_root = BinTree::destroy(*bin_root);
        *quad_root = QuadTree::destroy(*quad_root);
        exit(0);
    }

    bool isBinaryString(const std::string &str)
    {
        return str.find_first_not_of("01") == std::string::npos;
    }
}