#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> map(0);

struct AstInfo {
  double angle;
  int visible;
};

int destroy_ast(size_t ia, size_t ja, double angle) {
  int x200 = 0;
  int y200 = 0;
  double mag = 100000;
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map.front().size(); j++) {
      // don't consider yourself as visible, and we don't care about
      // non-asteroid spots
      if (((ia == i) && (ja == j)) || !map[i][j]) {
        continue;
      }
      int y = i - ia;
      int x = j - ja;
      double mag2 = sqrt(x * x + y * y);
      double angle2 = atan2(x, -y);
      if (angle2 < 0) {
        angle2 += 2 * numbers::pi;
      }
      if (angle2 == angle) {
        if (mag2 < mag) {
          mag = mag2;
          x200 = j;
          y200 = i;
        }
      }
    }
  }
  return x200 * 100 + y200;
}

AstInfo visible(size_t ia, size_t ja) {
  vector<double> angles(map.size() * map.front().size());

  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map.front().size(); j++) {
      // don't consider yourself as visible, and we don't care about
      // non-asteroid spots
      if (((ia == i) && (ja == j)) || !map[i][j]) {
        continue;
      }
      int y = i - ia;
      int x = j - ja;
      double angle = atan2(x, -y);
      if (angle < 0) {
        angle += 2 * numbers::pi;
      }
      angles[i * map.size() + j] = angle;
    }
  }
  // sort the angles for the upcoming unique()
  sort(angles.begin(), angles.end());

  auto unique_it = unique(angles.begin(), angles.end());
  double angle_200 = angles.size() >= 200 ? angles[199] : 0;

  AstInfo ai;
  ai.angle = angle_200;
  ai.visible = distance(angles.begin(), unique_it);

  return ai;
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
  double angle_200 = 0;
  int i_max = 0;
  int j_max = 0;
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map.front().size(); j++) {
      // if it's not an asteroid, continue
      if (!map[i][j]) {
        continue;
      }
      // found an asteroid; find how many it can see
      AstInfo ai = visible(i, j);
      if (ai.visible > max_asteroids) {
        max_asteroids = ai.visible;
        i_max = i;
        j_max = j;
        angle_200 = ai.angle;
      }
    }
  }
  cout << "Part 1: " << max_asteroids << endl;
  cout << "Part 2: " << destroy_ast(i_max, j_max, angle_200) << endl;
  return 0;
}
