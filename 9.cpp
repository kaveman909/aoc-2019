#include <cassert>
#include <iostream>
#include "intcode.h"

using namespace std;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  Intcode ic(argv[1]);
  for (auto &x : {1, 2}) {
    ic.push_input({x});
    ic.run_program();
    cout << "Part " << x << ": " << ic.get_output() << endl;
  }

  return 0;
}