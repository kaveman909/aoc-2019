#include <iostream>
#include <queue>

int main(void) {
  std::queue<int> q;
  q.push(2);
  q.push(5);
  std::cout << q.front() << std::endl;
  q.pop();
  std::cout << q.front() << std::endl;
  return 0;
}