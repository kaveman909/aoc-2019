#include <cassert>
#include <iostream>
#include "intcode.h"

using namespace std;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  Intcode ic(argv[1]);
  ic.push_input({1});
  ic.run_program();
  cout << "Part 1: " << ic.get_output() << endl;
  ic.push_input({2});
  ic.run_program();
  cout << "Part 2: " << ic.get_output() << endl;

  return 0;
}