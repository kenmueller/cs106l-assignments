#include "class.h"

int run_autograder();

int main() {
  assignment assignment_1("Assignment 1", 10);

  assignment_1.set_points(20);
  assignment_1.print_name_and_points();

  return run_autograder();
}

#include "utils.hpp"
