#include "intcode.h"
#include <cassert>
#include <condition_variable>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int Intcode::get_op(int in) {
  int op = in % 100;
  op = (op == 99) ? 0 : op;
  return op;
}

vector<int> Intcode::get_modes(int in, int num_params) {
  vector<int> modes;
  int mod = 1000;
  for (int i = 0; i < num_params; i++) {
    int mode = (in % mod) / (mod / 10);
    assert((mode == 0) || (mode == 1));
    modes.push_back(mode);
    mod *= 10;
  }
  return modes;
}

vector<reference_wrapper<int>> Intcode::get_params(vector<int> modes) {
  vector<reference_wrapper<int>> params;
  int i = 1;
  for (int mode : modes) {
    // position mode
    if (mode == 0) {
      params.push_back(program[program[pc + i]]);
    }
    // immediate mode
    else {
      params.push_back(program[pc + i]);
    }
    i++;
  }
  return params;
}

Intcode::Intcode(string fn) {
  program_name = "Program 0";
  output = 0;
  ifstream in(fn);
  char line[10];
  while (in.getline(line, 10, ',')) {
    instructions.push_back(stoi(line));
  }
  output_device = nullptr;
}

void Intcode::modify_program(int index, int value) {
  instructions[index] = value;
}

int Intcode::get_mem(int index) { return program[index]; }

int Intcode::get_output() { return output; }

void Intcode::run_program() {
  pc = 0;
  const int op_args[] = {0, 3, 3, 1, 1, 2, 2, 3, 3};
  // copy program as we'll be modifying memory
  program = instructions;
  bool update_pc = true;

  while (1) {
    int inst = program[pc];
    int op = get_op(inst);
    int args = op_args[op];
    auto modes = get_modes(inst, args);
    auto params = get_params(modes);

    switch (op) {
      case 0:
        return;
      case 1:
        params[2].get() = params[0] + params[1];
        break;
      case 2:
        params[2].get() = params[0] * params[1];
        break;
      case 3: {
        unique_lock<mutex> lk(mut);
        cv.wait(lk, [this] { return !input.empty(); });
        params[0].get() = input.front();
        input.pop();
        lk.unlock();
      } break;
      case 4:
        output = params[0];
        if (output_device != nullptr) {
          {
            lock_guard<mutex> lk(output_device->get_mutex());
            output_device->push_input({output});
          }
          output_device->get_cv().notify_one();
        }
        break;
      case 5:
        if (params[0]) {
          pc = params[1];
          update_pc = false;
        }
        break;
      case 6:
        if (!params[0]) {
          pc = params[1];
          update_pc = false;
        }
        break;
      case 7:
        if (params[0] < params[1]) {
          params[2].get() = 1;
        } else {
          params[2].get() = 0;
        }
        break;
      case 8:
        if (params[0] == params[1]) {
          params[2].get() = 1;
        } else {
          params[2].get() = 0;
        }
        break;
      default:
        cout << "ERROR! Illegal opcode. Aborting" << endl;
        return;
    }

    if (update_pc) {
      pc += args + 1;
    } else {
      update_pc = true;
    }
  }
}

void Intcode::print_instructions() {
  for (int x : instructions) {
    cout << x << endl;
  }
}

void Intcode::set_output_device(Intcode *od) { output_device = od; }

void Intcode::push_input(initializer_list<int> ins) {
  for (auto in : ins) {
    input.push(in);
  }
}

mutex &Intcode::get_mutex() { return mut; }

condition_variable &Intcode::get_cv() { return cv; }

void Intcode::set_program_name(string pn) { program_name = pn; }
