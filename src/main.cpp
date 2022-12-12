#include <cstdlib>
#include <cstring>
#include <iostream>

#include "driver.h"
#include "tree.h"

using namespace Pascal;

int main(const int argc, const char **argv) {
  /** check for the right # of arguments **/
  if (argc == 2) {
    /** instantiate driver object **/
    Pascal::Driver driver;

    /** example for piping input from terminal, i.e., using cat **/
    if (std::strncmp(argv[1], "-o", 2) == 0)
      driver.parse(std::cin);

    /** simple help menu **/
    /* else if (std::strncmp(argv[1], "-h", 2) == 0) { */
    /*   std::cout << "use -o for pipe to std::cin\n"; */
    /*   std::cout << "just give a filename to count from a file\n"; */
    /*   std::cout << "use -h to get this menu\n"; */
    /*   return (EXIT_SUCCESS); */
    /* } */

    /** example reading input from a file **/
    else
      /** assume file, prod code, use stat to check **/
      driver.parse(argv[1]);

    if (!driver.parse_tree)
      std::cout << driver.parse_tree->str() << std::endl;

    /* driver.print(std::cout) << "\n"; */
  } else {
    /** exit with failure condition **/
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
