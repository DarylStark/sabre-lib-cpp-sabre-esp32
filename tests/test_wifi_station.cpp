#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/wifi/wifi.hpp>
#include <sabre_esp32/wifi/wifi_station.hpp>

using namespace sabre::esp32;

class WifiStationTest : public ::testing::Test
{
protected:
    // Shared variable for all tests in this suite
    ip_event_got_ip_t _ip;

    // Setup logic, runs before each test
    void SetUp() override
    {
        _ip.ip_info.ip.addr = 0xC0A80064;      // 192.168.0.100
        _ip.ip_info.netmask.addr = 0xFFFFFF00; // 255.255.255.0
        _ip.ip_info.gw.addr = 0xC0A80001;      // 192.168.0.1
    }
};

TEST_F(WifiStationTest, Init)
{
    WifiStation station;
    station.init();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST_F(WifiStationTest, DoubleInit)
{
    WifiStation station;
    station.init();
    mockoc.clear();
    station.init();
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
    ASSERT_FALSE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST_F(WifiStationTest, InitializeBeforeConnect)
{
    WifiStation station;
    station.connect("TestSSID", "TestPassword");
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}
TEST_F(WifiStationTest, DontInitializeBeforeConnectIfAlreadyInitialized)
{
    WifiStation station;
    station.init();
    mockoc.clear();
    station.connect("TestSSID", "TestPassword");
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
    ASSERT_FALSE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST_F(WifiStationTest, Disconnect)
{
    WifiStation station;
    station.init();
    station.connect("TestSSID", "TestPassword");
    station.disconnect();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_disconnect"));
    ASSERT_FALSE(station.is_connected());
}

TEST_F(WifiStationTest, WifiConnectedEvent)
{
    WifiStation station;
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
}

TEST_F(WifiStationTest, WifiDisConnectedEvent)
{
    WifiStation station;
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_DISCONNECTED, nullptr);
    ASSERT_FALSE(station.is_connected());
}

TEST_F(WifiStationTest, WifiHasIPEvent)
{
    WifiStation station;
    station.ip_event_handler("IP", IP_EVENT_STA_GOT_IP, &_ip);
    ASSERT_TRUE(station.has_ipv4_address());
}

TEST_F(WifiStationTest, WifiHasLostIPEvent)
{
    WifiStation station;
    station.ip_event_handler("IP", IP_EVENT_STA_GOT_IP, &_ip);
    ASSERT_TRUE(station.has_ipv4_address());
    station.ip_event_handler("IP", IP_EVENT_STA_LOST_IP, nullptr);
    ASSERT_FALSE(station.has_ipv4_address());
}

TEST_F(WifiStationTest, CallWifiEventCallbackConnected)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
}

TEST_F(WifiStationTest, CallWifiEventCallbackDisconnected)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_DISCONNECTED, nullptr);
    ASSERT_FALSE(station.is_connected());
}

TEST_F(WifiStationTest, CallIPEventCallbackGotIP)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_GOT_IP, &_ip);
    ASSERT_TRUE(station.has_ipv4_address());
}

TEST_F(WifiStationTest, CallIPEventCallbackLostIP)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_GOT_IP, &_ip);
    ASSERT_TRUE(station.has_ipv4_address());
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_LOST_IP, nullptr);
    ASSERT_FALSE(station.has_ipv4_address());
}