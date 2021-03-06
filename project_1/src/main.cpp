/** 
* @file main.cpp
* @brief Main project executable for prefix tables
*
* Detailed description
*
* @author Nuno Venturinha
* @author João Borrego
*/

#include "menu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
   BinTree::Node *bin_root = NULL;
   QuadTree::Node *quad_root = NULL;
   
   if (argc == 2)
   {
   		bin_root = Prefix::prefixBinTree(argv[1]);
   }

   Menu::printOptions();
   Menu::loop(&bin_root, &quad_root);
}
