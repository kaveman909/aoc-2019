#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> get_lineage(string begin, vector<string> &left,
                           vector<string> &right) {
  vector<string> lineage;
  string target = begin;
  do {
    for (int i = 0; i < (int)right.size(); i++) {
      if (target == right[i]) {
        target = left[i];
        lineage.push_back(target);
        break;
      }
    }
  } while (target != "COM");
  return lineage;
}

int main([[maybe_unused]] int argc, char *argv[]) {
  ifstream in(argv[1]);
  char line[10];

  vector<string> left;
  vector<string> right;

  while (in) {
    in.getline(line, 10, ')');
    left.push_back(line);
    in.getline(line, 10);
    right.push_back(line);
  }

  vector<string> left_list;
  vector<string> right_list;

  // start by looking for "COM"
  left_list.push_back("COM");
  int total = 0;
  int orbit = 1;

  while (left_list.size() != 0) {
    for (auto item : left_list) {
      for (int i = 0; i < (int)left.size(); i++) {
        if (item == left[i]) {
          right_list.push_back(right[i]);
          total += orbit;
        }
      }
    }
    left_list = right_list;
    right_list.clear();
    orbit += 1;
  }
  cout << "Part 1: " << total << endl;
  // part 2... reverse problem!
  vector<string> you = get_lineage("YOU", left, right);
  vector<string> san = get_lineage("SAN", left, right);

  for (auto item : you) {
    auto san_it = find(san.begin(), san.end(), item);
    if (san_it != san.end()) {
      // found the most recent common ancestor
      int san_index = distance(san.begin(), san_it);
      auto you_it = find(you.begin(), you.end(), item);
      int you_index = distance(you.begin(), you_it);
      cout << "Part 2: " << san_index + you_index << endl;
      break;
    }
  }

  return 0;
}
