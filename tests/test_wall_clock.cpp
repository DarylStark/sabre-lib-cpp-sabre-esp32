#include <gtest/gtest.h>
#include <sabre_esp32/system/wall_clock.hpp>

using namespace sabre::esp32;

TEST(WallClock, GetCurrentTime)
{
    WallClock clock;
    clock.set_now_ms(1234567890);
    ASSERT_EQ(clock.now_ms(), 1234567890);
}