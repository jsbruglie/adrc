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

/**
 * @brief Prints the usage command
 * @param bin The file name of the main application (argv[0])
 */
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
