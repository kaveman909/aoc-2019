#include "intcode.h"
#include <cassert>
#include <fstream>
#include <iostream>
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

vector<int> Intcode::get_params(vector<int> modes) {
  vector<int> params;
  int i = 1;
  int param;
  for (int mode : modes) {
    // position mode
    if (mode == 0) {
      param = program[program[pc + i]];
    }
    // immediate mode
    else {
      param = program[pc + i];
    }
    params.push_back(param);
    i++;
  }
  return params;
}

Intcode::Intcode(string fn) {
  ifstream in(fn);
  char line[10];
  while (in.getline(line, 10, ',')) {
    instructions.push_back(stoi(line));
  }
}

void Intcode::modify_program(int index, int value) {
  instructions[index] = value;
}

int Intcode::get_mem(int index) { return program[index]; }

int Intcode::get_output() { return output; }

void Intcode::run_program_common() {
  pc = 0;
  const int op_args[] = {0, 3, 3, 1, 1, 2, 2, 3, 3};
  // copy program as we'll be modifying memory
  program = instructions;
  bool update_pc = true;

  while (1) {
    int inst = program[pc];
    int op = get_op(inst);
    int args = op_args[op];
    vector<int> modes = get_modes(inst, args);
    vector<int> params = get_params(modes);

    switch (op) {
      case 0:
        return;
      case 1:
        program[program[pc + 3]] = params[0] + params[1];
        break;
      case 2:
        program[program[pc + 3]] = params[0] * params[1];
        break;
      case 3:
        program[program[pc + 1]] = input.front();
        input.pop();
        break;
      case 4:
        output = params[0];
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
          program[program[pc + 3]] = 1;
        } else {
          program[program[pc + 3]] = 0;
        }
        break;
      case 8:
        if (params[0] == params[1]) {
          program[program[pc + 3]] = 1;
        } else {
          program[program[pc + 3]] = 0;
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

void Intcode::run_program() { run_program_common(); }

void Intcode::run_program(int i1) {
  input.push(i1);
  run_program_common();
}

void Intcode::run_program(int i1, int i2) {
  input.push(i1);
  input.push(i2);
  run_program_common();
}

void Intcode::print_instructions() {
  for (int x : instructions) {
    cout << x << endl;
  }
}
