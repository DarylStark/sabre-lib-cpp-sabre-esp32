#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/factory.hpp>

class FactoryTest : public ::testing::Test
{
protected:
    sabre::esp32::Factory _factory;
    void SetUp() override
    {
        mockoc.clear();
        mock_mcu.clear();
    }
};

TEST_F(FactoryTest, CreateUARTObject)
{
    auto obj = _factory.create_uart_object(1, 9600, 17, 16);
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::UART));
}
TEST_F(FactoryTest, CreateInputGPIO)
{
    auto obj = _factory.create_input_gpio(4);
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::InputGPIO));
}

TEST_F(FactoryTest, CreateOutputGPIO)
{
    auto obj = _factory.create_output_gpio(4);
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::OutputGPIO));
}

TEST_F(FactoryTest, CreateWifiStation)
{
    auto obj = _factory.create_wifi_station();
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::WifiStation));
}

TEST_F(FactoryTest, CreateWifiSoftAP)
{
    auto obj = _factory.create_wifi_soft_ap();
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::WifiSoftAP));
}

TEST_F(FactoryTest, CreateMQTTClient)
{
    auto obj = _factory.create_mqtt_client();
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::MQTTClient));
}

TEST_F(FactoryTest, CreateWaitFor)
{
    auto obj = _factory.create_wait_for([]() { return true; }, 1000, 100);
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::WaitFor));
}

TEST_F(FactoryTest, CreateNTPClient)
{
    auto obj = _factory.create_ntp_client("pool.ntp.org");
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::NTPClient));
}

TEST_F(FactoryTest, CreateWallClock)
{
    auto obj = _factory.create_wall_clock();
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::WallClock));
}

TEST_F(FactoryTest, CreateService)
{
    auto obj = _factory.create_service([]() {});
    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(sabre::esp32::Service));
}