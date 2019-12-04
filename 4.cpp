#include <iostream>
#include <regex>
#include <string>

using namespace std;

bool monotonic(string);
int passwords(regex);

// int lo = 356261;
// int hi = 846303;

int lo = 136760;
int hi = 595730;

int main(int argc, char* argv[]) {
  int total = 0;

  regex r1(R"((\d)\1)");
  regex r2(R"((^|(\d)(?!\2))(\d)\3(?!\3))");

  cout << "Part 1: " << passwords(r1) << endl;
  cout << "Part 2: " << passwords(r2) << endl;

  return 0;
}

bool monotonic(string xs) {
  for (int i = 0; i < 5; i++) {
    if (stoi(xs.substr(i, 1)) > stoi(xs.substr(i + 1, 1))) {
      return false;
    }
  }
  return true;
}

int passwords(regex r) {
  int total = 0;
  for (int x = lo; x < hi; x++) {
    string xs = to_string(x);

    if (!regex_search(xs, r)) {
      continue;
    }

    if (!monotonic(xs)) {
      continue;
    }

    total++;
  }
  return total;
}
