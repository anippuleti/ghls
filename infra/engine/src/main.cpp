#include <iostream>

#include "simTime.hpp"

int main() {
  ghls::SimTime t;
  std::cout << "SimTime: " << ghls::conv2str(t) << std::endl;
  return 0;
}
