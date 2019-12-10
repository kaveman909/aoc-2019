#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Intcode {
 private:
  vector<long> instructions;
  vector<long> program;
  int pc;  // program counter
  int rb;  // relative base
  queue<long> input;
  long output;
  Intcode *output_device;
  mutex mut;
  condition_variable cv;
  string program_name;
  bool debug;

  int get_op(int in);
  vector<int> get_modes(long in, int num_params);
  vector<reference_wrapper<long>> get_params(vector<int> modes);

 public:
  Intcode(string fn);
  Intcode() = delete;

  void modify_program(int index, int value);
  long get_mem(int index);
  long get_output();
  mutex &get_mutex();
  condition_variable &get_cv();

  void set_output_device(Intcode *od);
  void push_input(initializer_list<long> in);
  void set_program_name(string pn);
  void set_debug(bool dbg);

  void run_program();

  void print_instructions();
};