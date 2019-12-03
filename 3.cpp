#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// create giant 2d vector for grid
const int GRID_SIZE = 20000;
vector<vector<int> > grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

// create vector for manhattan dists
vector<int> manhat;

void follow_path(vector<string>, int);

int main(int argc, char *argv[]) {
  ifstream in(argv[1]);
  string wire1;
  in >> wire1;

  string wire2;
  in >> wire2;

  vector<string> wire1v;
  vector<string> wire2v;
  stringstream wire1ss(wire1);
  stringstream wire2ss(wire2);

  string wiredir;

  while (getline(wire1ss, wiredir, ',')) {
    wire1v.push_back(wiredir);
  }
  while (getline(wire2ss, wiredir, ',')) {
    wire2v.push_back(wiredir);
  }

  follow_path(wire1v, 1);
  follow_path(wire2v, 2);
  int min_manhat_idx =
      distance(manhat.begin(), min_element(manhat.begin(), manhat.end()));
  cout << "Part 1: " << manhat[min_manhat_idx] << endl;
  return 0;
}

void follow_path(vector<string> wirev, int wiren) {
  // x and y coords that will be changing as we follow the map
  int x = GRID_SIZE / 2;
  int y = GRID_SIZE / 2;
  for (string inst : wirev) {
    const char dir = inst.at(0);
    const int mag = stoi(inst.substr(1));
    const int sign = (dir == 'U' || dir == 'R') ? 1 : -1;
    int *d = (dir == 'R') || (dir == 'L') ? &x : &y;

    for (int step = 0; step < mag; step++) {
      *d += sign;
      if (grid[x][y] == 0) {
        grid[x][y] = wiren;
      } else if (grid[x][y] != wiren) {
        grid[x][y] = 3;
        manhat.push_back(abs(x - (GRID_SIZE / 2)) + abs(y - (GRID_SIZE / 2)));
      }
    }
  }
}
