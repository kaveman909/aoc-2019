#include <iostream>
#include "intcode.h"

using namespace std;

int main([[maybe_unused]] int argc, char *argv[]) {
  Intcode ic(argv[1]);
  ic.modify_program(1, 12);
  ic.modify_program(2, 2);
  ic.run_program(0);
  cout << "Part 1: " << ic.get_mem(0) << endl;
  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      ic.modify_program(1, noun);
      ic.modify_program(2, verb);
      ic.run_program(0);
      if (ic.get_mem(0) == 19690720) {
        cout << "Part 2: " << 100 * noun + verb << endl;
        return 0;
      }
    }
  }
  return 0;
}
