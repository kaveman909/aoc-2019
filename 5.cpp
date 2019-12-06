#include <iostream>
#include "intcode.h"

using namespace std;

int main(void) {
  Intcode ic("in.5.txt");
  ic.run_program(1);
  cout << "Part 1: " << ic.get_output() << endl;
  return 0;
}