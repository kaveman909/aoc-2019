#include <iostream>
#include <string>

#ifdef PRINT
#define print(p) print_(#p, (p))
#else
#define print(p)
#endif

template <typename T>
void print_(std::string p, T t) {
  std::cout << p << ": " << t << std::endl;
}
