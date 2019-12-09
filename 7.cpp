#include <algorithm>
#include <array>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <thread>
#include "intcode.h"

using namespace std;

const int NUM_OF_AMPS = 5;

int main(int argc, char *argv[]) {
  assert(argc == 2);
  array<int, 5> settings = {0, 1, 2, 3, 4};
  Intcode ic(argv[1]);
  int max_signal = 0;
  do {
    int output = 0;
    for (int setting : settings) {
      ic.push_input({setting, output});
      ic.run_program();
      output = ic.get_output();
    }
    if (output > max_signal) {
      max_signal = output;
    }
  } while (next_permutation(settings.begin(), settings.end()));
  cout << "Part 1: " << max_signal << endl;

  // Begin Part 2

  settings = {5, 6, 7, 8, 9};
  max_signal = 0;
  do {
    vector<Intcode *> amps(NUM_OF_AMPS);
    vector<thread> threads;

    for (auto &amp : amps) {
      amp = new Intcode(argv[1]);
    }

    for (int i = 0; i < NUM_OF_AMPS; i++) {
      // Set each amps output device as the next one in the sequence.  The
      // modulo will take care of the last amp pointing back to the first one.
      amps[i]->set_program_name("P" + to_string(i + 1));
      amps[i]->set_output_device(amps[(i + 1) % NUM_OF_AMPS]);
      // each amps first input should be its 'phase setting'
      amps[i]->push_input({settings[i]});
      if (i == 0) {
        // the first amp starts with a signal of '0' applied per instructions
        amps[i]->push_input({0});
      }
      // start amp thread
      threads.push_back(thread(&Intcode::run_program, amps[i]));
    }

    // wait for all threads to finish
    for (auto &th : threads) {
      th.join();
    }
    // only care about the output of Amp E (last one)
    int output = amps[NUM_OF_AMPS - 1]->get_output();
    if (output > max_signal) {
      max_signal = output;
    }
  } while (next_permutation(settings.begin(), settings.end()));
  cout << "Part 2: " << max_signal << endl;

  return 0;
}