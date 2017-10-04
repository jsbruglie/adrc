/** 
* @file main.cpp
* @brief Main project executable for prefix tables
*
* Detailed description
*
* @author Nuno Venturinha
* @author João Borrego
*/

#include "prefix.hpp"

#include <iostream>

using namespace std;

void readFile()
{
    
    std::ifstream infile("test_files/PrefixTable.txt");
    char *prefix = (char *)malloc(256 * (sizeof(char)));
    int next_hop;

    BinTree::Node *root = NULL;

    while (infile >> prefix >> next_hop)
    {
        /*
        std::cout
        << "Prefix: " << prefix
        << " Next Hop: " << next_hop << std::endl;
        */
        root = BinTree::insert(root, prefix, next_hop);
    }

    BinTree::print(root);
    std::cout << "Removing prefix 0" << std::endl;
    BinTree::remove(root, (char*)"0");
    BinTree::print(root);
}

void printUsage(char *bin){
   cout << bin << " [path/to/input_file]" << endl;
}

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      printUsage(argv[0]);
   }
   else
   {
      BinTree::Node *root = Prefix::prefixBinTree(argv[1]);
      
      cout << "[INFO] Printing tree." << endl;
      BinTree::print(root);
      
      Prefix::lookUp(root, (char*) "0010");
   }
}
