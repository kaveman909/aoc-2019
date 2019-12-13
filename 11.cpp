#include <array>
#include <cassert>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include "intcode.h"

// #define PRINT
#include "util.h"

using namespace std;

// create a large grid for the robot to move around on
// grid is initialized to 0 (black)
const int GRID_SIZE = 100;
vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));
// need a second grid that records if the square has been painted
// (probably smarter way to do this)
vector<vector<int>> painted(GRID_SIZE, vector<int>(GRID_SIZE, 0));
// start the robot in the middle
int x = GRID_SIZE / 2, y = GRID_SIZE / 2;
// robot starts facing up
array<int, 2> facing{0, -1};

void rotate(array<int, 2> &cur_dir, int rot_dir) {
  int new_x;
  int new_y;
  if (rot_dir) {
    new_x = -cur_dir[1];
    new_y = cur_dir[0];
  } else {
    new_x = cur_dir[1];
    new_y = -cur_dir[0];
  }
  cur_dir = {new_x, new_y};
}

void output_cb(Intcode *prog) {
  int color = 0;
  int dir = 0;

  if (prog->outputq.size() == 2) {
    // we've got 2 outputs to process
    color = prog->outputq.front();
    assert(abs(color) < 2);
    prog->outputq.pop();
    dir = prog->outputq.front();
    assert(abs(dir) < 2);
    prog->outputq.pop();
    // 1) color
    grid[y][x] = color;
    painted[y][x] = 1;
    // 2) turn
    rotate(facing, dir);
    // 3) move one space
    x += facing[0];
    y += facing[1];
    // 4) get new color to feed program
    int new_color = grid[y][x];
    prog->push_input({new_color});
    // 5) wait for new outputs...
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  // init the Intcode painting program
  Intcode prog(argv[1]);

  // provide program with initial input
  prog.push_input({grid[y][x]});
  prog.set_cb(output_cb);
  prog.run_program();

  // part 1: calculate total number of grid squares painted
  int total = 0;
  for (auto column : painted) {
    total = accumulate(column.begin(), column.end(), total);
    // cout << "accum: " << total << endl;
  }
  cout << "Part 1: " << total << endl;
  return 0;
}
