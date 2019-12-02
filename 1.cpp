#include <fstream>
#include <iostream>

using namespace std;

int get_fuel(int in) {
  return (in / 3) - 2;
}

int get_extra_fuel(int in) {
  int sum = 0;
  while (in > 0) {
    in = get_fuel(in);
    if (in > 0) {
      sum += in;
    }
  }
  return sum;
}

int main(int argc, char * argv[]) {
  ifstream in(argv[1]);
  int line;
  int sum = 0;
  int sum2 = 0;
  while (in >> line) {
    sum += get_fuel(line);
    sum2 += get_extra_fuel(line);
  }
  cout << "Part 1: " << sum << endl;
  cout << "Part 2: " << sum2 << endl;
}
