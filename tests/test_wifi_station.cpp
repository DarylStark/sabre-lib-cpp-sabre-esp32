#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/wifi/wifi.hpp>
#include <sabre_esp32/wifi/wifi_station.hpp>

using namespace sabre::esp32;

TEST(WifiStation, Init)
{
    WifiStation station;
    station.init();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST(WifiStation, DoubleInit)
{
    WifiStation station;
    station.init();
    mockoc.clear();
    station.init();
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
    ASSERT_FALSE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST(WifiStation, InitializeBeforeConnect)
{
    WifiStation station;
    station.connect("TestSSID", "TestPassword");
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}
TEST(WifiStation, DontInitializeBeforeConnectIfAlreadyInitialized)
{
    WifiStation station;
    station.init();
    mockoc.clear();
    station.connect("TestSSID", "TestPassword");
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
    ASSERT_FALSE(mockoc.was_called("esp_netif_create_default_wifi_sta"));
}

TEST(WifiStation, Disconnect)
{
    WifiStation station;
    station.init();
    station.connect("TestSSID", "TestPassword");
    station.disconnect();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_disconnect"));
    ASSERT_FALSE(station.is_connected());
}

TEST(WifiStation, WifiConnectedEvent)
{
    WifiStation station;
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
}

TEST(WifiStation, WifiDisConnectedEvent)
{
    WifiStation station;
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
    station.wifi_event_handler("WIFI", WIFI_EVENT_STA_DISCONNECTED, nullptr);
    ASSERT_FALSE(station.is_connected());
}

TEST(WifiStation, WifiHasIPEvent)
{
    ip_event_got_ip_t ip;
    WifiStation station;
    station.ip_event_handler("IP", IP_EVENT_STA_GOT_IP, &ip);
    ASSERT_TRUE(station.has_ipv4_address());
}

TEST(WifiStation, WifiHasLostIPEvent)
{
    ip_event_got_ip_t ip;
    WifiStation station;
    station.ip_event_handler("IP", IP_EVENT_STA_GOT_IP, &ip);
    ASSERT_TRUE(station.has_ipv4_address());
    station.ip_event_handler("IP", IP_EVENT_STA_LOST_IP, nullptr);
    ASSERT_FALSE(station.has_ipv4_address());
}

TEST(WifiStation, CallWifiEventCallbackConnected)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
}

TEST(WifiStation, CallWifiEventCallbackDisconnected)
{
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_CONNECTED, nullptr);
    ASSERT_TRUE(station.is_connected());
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_DISCONNECTED, nullptr);
    ASSERT_FALSE(station.is_connected());
}

TEST(WifiStation, CallIPEventCallbackGotIP)
{
    ip_event_got_ip_t ip;
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_GOT_IP, &ip);
    ASSERT_TRUE(station.has_ipv4_address());
}

TEST(WifiStation, CallIPEventCallbackLostIP)
{
    ip_event_got_ip_t ip;
    WifiStation station;
    station.init();
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_GOT_IP, &ip);
    ASSERT_TRUE(station.has_ipv4_address());
    mock_mcu.call_wifi_event_callback(IP_EVENT_STA_LOST_IP, nullptr);
    ASSERT_FALSE(station.has_ipv4_address());
}