#include "sabre_esp32/test.hpp"
#include <gtest/gtest.h>

TEST(Test, Sum)
{
    ASSERT_EQ(sum(10, 20), 30);
}

TEST(Test, SumALowerThen1)
{
    ASSERT_EQ(sum(0, 20), 0);
}
