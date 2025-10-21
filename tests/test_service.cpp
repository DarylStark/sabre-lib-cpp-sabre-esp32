#include <gtest/gtest.h>
#include <mockoc.hpp>
#include <sabre_esp32/service/service.hpp>

using namespace sabre::esp32;

TEST(Service, TestStoppingBeforeStarting)
{
    Service service([]() {});
    service.stop();
    ASSERT_FALSE(mockoc.was_called("vTaskDelete"));
}

TEST(Service, TestStartCallsTaskCreate)
{
    Service service([]() {});
    service.start();
    ASSERT_TRUE(mockoc.was_called("xTaskCreate"));
}

TEST(Service, TestStopped)
{
    Service service([]() {});
    service.start();
    service.stop();
    ASSERT_TRUE(mockoc.was_called("vTaskDelete"));
}

TEST(Service, TestRunner)
{
    bool ran = false;
    Service service([&ran]() { ran = true; });
    service.start();
    ASSERT_TRUE(ran);
}