#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {
  ifstream in(argv[1]);
  string line;
  // read in the single line from the file
  in >> line;

  // parse the csv line into ints, fill a vector
  string opcode;
  vector<int> opcodes;
  stringstream stream(line);
  while (getline(stream, opcode, ',')) {
    opcodes.push_back(stoi(opcode));
  }
  // replace entries 1 and 2 for the '1202' program
  opcodes[1] = 12;
  opcodes[2] = 2;
  int i_op = 0; // current opcode index
  while (opcodes[i_op] != 99) {
    int op = opcodes[i_op];
    int a = opcodes[opcodes[i_op + 1]];
    int b = opcodes[opcodes[i_op + 2]];
    int c = opcodes[i_op + 3];
    int result;

    if (op == 1) {
      result = a + b;
    }
    else if (op == 2) {
      result = a * b;
    }
    else {
      cout << "Error!" << endl;
      break;
    }
    opcodes[c] = result;
    i_op += 4;
  }
  cout << "Part 1: " << opcodes[0] << endl;
}