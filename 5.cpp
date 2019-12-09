#include <iostream>
#include "intcode.h"

using namespace std;

int main([[maybe_unused]] int argc, char *argv[]) {
  Intcode ic(argv[1]);
  ic.push_input({1});
  ic.run_program();
  cout << "Part 1: " << ic.get_output() << endl;
  ic.push_input({5});
  ic.run_program();
  cout << "Part 2: " << ic.get_output() << endl;
  return 0;
}
