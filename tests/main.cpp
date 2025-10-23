#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/wifi/wifi.hpp>

class MyGlobalListener : public ::testing::EmptyTestEventListener
{
public:
    void OnTestStart(const ::testing::TestInfo &test_info) override
    {
        mockoc.clear();
        mock_mcu.clear();
        auto wifi = sabre::esp32::Wifi::get_instance();
        wifi->reset();
        wifi->set_default_start_timeout(10);
    }
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MyGlobalListener);
    return RUN_ALL_TESTS();
}