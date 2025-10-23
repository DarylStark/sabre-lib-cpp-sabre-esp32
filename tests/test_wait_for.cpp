#include <gtest/gtest.h>
#include <mockoc.hpp>
#include <sabre_esp32/utility/wait_for.hpp>

using namespace sabre::esp32;

TEST(WaitFor, TestWaitingFor)
{
    uint32_t counter = 0;
    WaitFor wf = WaitFor([&counter]() { return counter++ > 5; }, 1000, 10);
    wf();
    ASSERT_TRUE(mockoc.was_called("vTaskDelay"));
}