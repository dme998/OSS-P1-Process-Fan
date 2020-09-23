#include <iostream>
#include <stdio.h>
#include <unistd.h>

int main() {
  int i;
  std::cout << "I am testsim!  WAITING!" << std::endl;
  sleep(3);
  std::cout << "..Done!" << std::endl;
  return 0;
}
