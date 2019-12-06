#include <string>
#include <vector>

using namespace std;

class Intcode {
 private:
  vector<int> instructions;
  vector<int> program;
  int pc;  // program counter
  int input;
  int output;

  int get_op(int in);
  vector<int> get_modes(int in, int num_params);
  vector<int> get_params(vector<int> modes);

 public:
  Intcode(string fn);

  void modify_program(int index, int value);
  int get_mem(int index);
  int get_output();
  void run_program(int pinput);
  void print_instructions();
};