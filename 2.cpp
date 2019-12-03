#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream in(argv[1]);
  string line;
  // read in the single line from the file
  in >> line;

  // parse the csv line into ints, fill a vector
  string opcode;
  vector<int> opcodes_ref;

  stringstream stream(line);
  while (getline(stream, opcode, ',')) {
    opcodes_ref.push_back(stoi(opcode));
  }

  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      vector<int> opcodes = opcodes_ref;  // copy by value the reference program
      opcodes[1] = noun;
      opcodes[2] = verb;
      int i_op = 0;  // current opcode index
      while (opcodes[i_op] != 99) {
        int op = opcodes[i_op];
        int a = opcodes[opcodes[i_op + 1]];
        int b = opcodes[opcodes[i_op + 2]];
        int c = opcodes[i_op + 3];
        int result;

        if (op == 1) {
          result = a + b;
        } else if (op == 2) {
          result = a * b;
        } else {
          cout << "Error!" << endl;
          break;
        }
        opcodes[c] = result;
        i_op += 4;
      }
      if ((noun == 12) && (verb == 2)) {
        cout << "Part 1: " << opcodes[0] << endl;
      }
      if (opcodes[0] == 19690720) {
        cout << "Part 2: " << 100 * noun + verb << endl;
      }
    }
  }
  return 0;
}