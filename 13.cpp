#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>
#include "intcode.h"

#define PRINT
#include "util.h"

using namespace std;

const int GRID_DIM = 50;
vector<vector<int>> grid(GRID_DIM, vector<int>(GRID_DIM, 0));

void output_cb(Intcode *ic) {
  if (ic->outputq.size() == 3) {
    unsigned int x, y, id;
    for (auto thing : {&x, &y, &id}) {
      *thing = ic->outputq.front();
      ic->outputq.pop();
    }
    assert(id < 5);
    grid[y][x] = id;
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  Intcode prog(argv[1]);
  prog.set_cb(output_cb);
  prog.run_program();

  int block_tiles = 0;
  for (auto &row : grid) {
    block_tiles +=
        count_if(row.begin(), row.end(), [](int tile) { return tile == 2; });
  }

  cout << "Part 1: " << block_tiles << endl;

  return 0;
}
