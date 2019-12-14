#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>

#define PRINT
#include "util.h"

using namespace std;

template <typename T>
int get_energy(T const &v) {
  return accumulate(v.begin(), v.end(), 0,
                    [](int a, int b) { return abs(a) + abs(b); });
}

template <typename T>
int get_energy_total(T const &p, T const &v) {
  int total = 0;
  for (size_t planet = 0; planet < p.size(); planet++) {
    total += get_energy(p[planet]) * get_energy(v[planet]);
  }
  return total;
}

template <typename T>
void apply_gravity(T const &p, T &v) {
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = i + 1; j < v.size(); j++) {
      for (size_t k = 0; k < v.front().size(); k++) {
        if (p[i][k] > p[j][k]) {
          v[i][k]--;
          v[j][k]++;
        } else if (p[i][k] < p[j][k]) {
          v[i][k]++;
          v[j][k]--;
        }  // else, positions are the same so do nothing
      }
    }
  }
}

template <typename T>
void apply_velocity(T &p, T const &v) {
  for (size_t i = 0; i < p.size(); i++) {
    transform(p[i].begin(), p[i].end(), v[i].begin(), p[i].begin(),
              plus<int>());
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  ifstream f(argv[1]);
  array<array<int, 3>, 4> positions;
  array<array<int, 3>, 4> velocities = {0};

  // get the positions from the input data
  for (int i = 0; i < 4; i++) {
    char line[40];
    cmatch matches;

    f.getline(line, 40);
    regex_match(line, matches,
                regex(R"(<x=([-\d]+), y=([-\d]+), z=([-\d]+)>)"));
    for (int j = 0; j < 3; j++) {
      positions[i][j] = stoi(matches[j + 1]);
    }
  }

  for (int i = 0; i < 1000; i++) {
    apply_gravity(positions, velocities);
    apply_velocity(positions, velocities);
  }

  cout << "Part 1: " << get_energy_total(positions, velocities) << endl;

  return 0;
}
