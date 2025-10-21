#include <gtest/gtest.h>
#include <mockoc.hpp>
#include <sabre_esp32/uart/uart.hpp>

using namespace sabre::esp32;

TEST(UART, WiteData)
{
    UART uart(UART_NUM_0, 9600, 17, 16);
    uart.write_byte('A');
    ASSERT_TRUE(mockoc.was_called("uart_write_bytes"));
    ASSERT_TRUE(mockoc.last_call_for_function("uart_write_bytes").args[0] ==
                "0");
    ASSERT_EQ(mockoc.last_call_for_function("uart_write_bytes").args[1], "A");
}

TEST(UART, DontAllowDoubleInitialization)
{
    UART uart(UART_NUM_1, 115200, 4, 5);
    uart.initialize();
    mockoc.clear();
    uart.initialize();
    ASSERT_FALSE(mockoc.was_called("uart_driver_install"));
}

TEST(UART, Flush)
{
    UART uart(UART_NUM_1, 115200, 4, 5);
    uart.flush();
    ASSERT_TRUE(mockoc.was_called("uart_flush_input"));
    ASSERT_TRUE(mockoc.last_call_for_function("uart_flush_input").args[0] ==
                "1");
}

TEST(UART, Deinitialize)
{
    UART uart(UART_NUM_1, 115200, 4, 5);
    uart.deinitialize();
    ASSERT_TRUE(mockoc.was_called("uart_driver_delete"));
}

TEST(UART, IsDeinitializedInDestructor)
{
    {
        UART uart(UART_NUM_1, 115200, 4, 5);
    }
    ASSERT_TRUE(mockoc.was_called("uart_driver_delete"));
}