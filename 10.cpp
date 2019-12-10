#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> map(0);

int visible(size_t ia, size_t ja) {
  vector<double> angles(map.size() * map.front().size());

  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map.front().size(); j++) {
      // don't consider yourself as visible, and we don't care about
      // non-asteroid spots
      if (((ia == i) && (ja == j)) || !map[i][j]) {
        continue;
      }
      int deltai = ia - i;
      int deltaj = ja - j;
      angles[i * map.size() + j] = atan2(deltaj, deltai);
    }
  }
  // sort the angles for the upcoming unique()
  sort(angles.begin(), angles.end());

  return distance(angles.begin(), unique(angles.begin(), angles.end()));
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  ifstream in(argv[1]);

  char line[50];
  while (in.getline(line, 50)) {
    map.push_back(vector<int>(0));
    for (size_t i = 0; i < strlen(line); i++) {
      map.back().push_back(line[i] == '.' ? 0 : 1);
    }
  }

  int max_asteroids = 0;
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map.front().size(); j++) {
      // if it's not an asteroid, continue
      if (!map[i][j]) {
        continue;
      }
      // found an asteroid; find how many it can see
      int vis = visible(i, j);
      if (vis > max_asteroids) {
        max_asteroids = vis;
      }
    }
  }
  cout << "Part 1: " << max_asteroids << endl;
  return 0;
}
