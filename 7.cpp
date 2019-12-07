#include <algorithm>
#include <array>
#include <iostream>
#include "intcode.h"

using namespace std;

int main([[maybe_unused]] int argc, char* argv[]) {
  Intcode ic(argv[1]);
  array<int, 5> settings = {0, 1, 2, 3, 4};
  int max_signal = 0;
  do {
    int output = 0;
    for (int setting : settings) {
      ic.run_program(setting, output);
      output = ic.get_output();
    }
    if (output > max_signal) {
      max_signal = output;
    }
  } while (next_permutation(settings.begin(), settings.end()));
  cout << "Part 1: " << max_signal << endl;
  return 0;
}