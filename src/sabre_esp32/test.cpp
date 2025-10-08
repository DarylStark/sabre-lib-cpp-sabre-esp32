#include "test.hpp"

int sum(int a, int b)
{
    if (a > 1)
        return a + b;
    throw sabre::SabreException("ERROR!");
}
