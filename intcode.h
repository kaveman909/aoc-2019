#include <queue>
#include <string>
#include <vector>

using namespace std;

class Intcode {
 private:
  vector<int> instructions;
  vector<int> program;
  int pc;  // program counter
  queue<int> input;
  int output;

  int get_op(int in);
  vector<int> get_modes(int in, int num_params);
  vector<int*> get_params(vector<int> modes);
  void run_program_common();

 public:
  Intcode(string fn);

  void modify_program(int index, int value);
  int get_mem(int index);
  int get_output();

  void run_program();
  void run_program(int i1);
  void run_program(int i1, int i2);

  void print_instructions();
};