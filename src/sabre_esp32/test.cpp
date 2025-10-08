#include "test.hpp"
#include <iostream>

int sum(int a, int b)
{
    std::cout << "Counting!" << std::endl;
    if (a > 1)
        return a + b;
    return 0;
}
