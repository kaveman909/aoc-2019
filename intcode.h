#include <condition_variable>
#include <functional>
#include <mutex>
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
  Intcode *output_device;
  mutex mut;
  condition_variable cv;
  string program_name;

  int get_op(int in);
  vector<int> get_modes(int in, int num_params);
  vector<reference_wrapper<int>> get_params(vector<int> modes);

 public:
  Intcode(string fn);
  Intcode() = delete;

  void modify_program(int index, int value);
  int get_mem(int index);
  int get_output();
  mutex &get_mutex();
  condition_variable &get_cv();

  void set_output_device(Intcode *od);
  void push_input(initializer_list<int> in);
  void set_program_name(string pn);

  void run_program();

  void print_instructions();
};