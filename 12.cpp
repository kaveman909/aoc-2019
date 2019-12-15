#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#define PRINT
#include "util.h"

using namespace std;

typedef array<int, 3> P;
typedef array<P, 4> SS;
typedef array<int, 4> PInfo;

ostream &operator<<(ostream &os, const PInfo &input) {
  for (auto const &i : input) {
    os << i << '\t';
  }
  return os;
}

ostream &operator<<(ostream &os, const P &input) {
  for (auto const &i : input) {
    os << i << '\t';
  }
  return os;
}

ostream &operator<<(ostream &os, vector<int> &input) {
  for (auto const &i : input) {
    os << i << '\t';
  }
  return os;
}

ostream &operator<<(ostream &os, vector<P> &input) {
  for (auto const &i : input) {
    os << i << endl;
  }
  return os;
}

ostream &operator<<(ostream &os, const SS &input) {
  for (auto const &i : input) {
    os << i << endl;
  }
  return os;
}

int get_energy(P const &v) {
  return accumulate(v.begin(), v.end(), 0,
                    [](int a, int b) { return abs(a) + abs(b); });
}

int get_energy_total(SS const &p, SS const &v) {
  int total = 0;
  for (size_t planet = 0; planet < p.size(); planet++) {
    total += get_energy(p[planet]) * get_energy(v[planet]);
  }
  return total;
}

void apply_gravity(SS const &p, SS &v) {
  SS g = {0};
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = i + 1; j < v.size(); j++) {
      for (size_t k = 0; k < v.front().size(); k++) {
        if (p[i][k] > p[j][k]) {
          v[i][k]--;
          g[i][k]--;
          v[j][k]++;
          g[j][k]++;
        } else if (p[i][k] < p[j][k]) {
          v[i][k]++;
          g[i][k]++;
          v[j][k]--;
          g[j][k]--;
        }  // else, positions are the same so do nothing
      }
    }
  }
}

void apply_velocity(SS &p, SS const &v) {
  for (size_t i = 0; i < p.size(); i++) {
    transform(p[i].begin(), p[i].end(), v[i].begin(), p[i].begin(),
              plus<int>());
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  ifstream f(argv[1]);
  SS positions;
  SS velocities = {0};

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

  const int SEARCH_SIZE = 500000;

  vector<P> planet_history(SEARCH_SIZE);
  const int PLANET_TO_RECORD = 2;

  for (int i = 0; i < SEARCH_SIZE; i++) {
    // record history of only a single planet... may be flawed
    planet_history[i] = positions[PLANET_TO_RECORD];
    apply_gravity(positions, velocities);
    apply_velocity(positions, velocities);
    if (i == 1000 - 1) {
      cout << "Part 1: " << get_energy_total(positions, velocities) << endl;
    }
  }

  const int COMPARE_SIZE = 5;
  vector<P> ref_entries(planet_history.begin(),
                        planet_history.begin() + COMPARE_SIZE);
  vector<int> xc(COMPARE_SIZE);
  vector<int> yc(COMPARE_SIZE);
  vector<int> zc(COMPARE_SIZE);
  for (int i = 0; i < COMPARE_SIZE; i++) {
    xc[i] = ref_entries[i][0];
    yc[i] = ref_entries[i][1];
    zc[i] = ref_entries[i][2];
  }
  bool foundx = false;
  bool foundy = false;
  bool foundz = false;
  long xidx = 0;
  long yidx = 0;
  long zidx = 0;
  for (int i = 1; i < SEARCH_SIZE - COMPARE_SIZE; i++) {
    vector<int> x(COMPARE_SIZE);
    vector<int> y(COMPARE_SIZE);
    vector<int> z(COMPARE_SIZE);
    for (int j = 0; j < COMPARE_SIZE; j++) {
      x[j] = planet_history[i + j][0];
      y[j] = planet_history[i + j][1];
      z[j] = planet_history[i + j][2];
    }
    bool xm = xc == x;
    bool ym = yc == y;
    bool zm = zc == z;
    if (xm && !foundx) {
      xidx = i;
      foundx = true;
    }
    if (ym && !foundy) {
      yidx = i;
      foundy = true;
    }
    if (zm && !foundz) {
      zidx = i;
      foundz = true;
    }
    if (foundx && foundy && foundz) {
      break;
    }
  }
  long lcm0 = lcm(xidx, yidx);
  long lcm1 = lcm(lcm0, zidx);

  cout << "Part 2: " << lcm1 << endl;

  return 0;
}
