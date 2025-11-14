#include <iostream>
#include "greeter.h"

int main() {
    Greeter g;
    std::cout << g.greet("World") << std::endl;
    return 0;
}
