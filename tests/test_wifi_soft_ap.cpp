#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/wifi/wifi.hpp>
#include <sabre_esp32/wifi/wifi_soft_ap.hpp>

using namespace sabre::esp32;

TEST(WifiSoftAPTest, Init)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_create_default_wifi_ap"));
}

TEST(WifiSoftAPTest, DoubleInit)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    mockoc.clear();
    soft_ap.init();
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
    ASSERT_FALSE(mockoc.was_called("esp_netif_create_default_wifi_ap"));
}

TEST(WifiSoftAPTest, CheckMissingWifimode)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    auto &wifi = Wifi::get_instance();
    ASSERT_FALSE(wifi->soft_ap_enabled());
}

TEST(WifiSoftAPTest, CorrectModeAfterStart)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    soft_ap.start("SSID", "Password");
    auto &wifi = Wifi::get_instance();
    ASSERT_TRUE(wifi->soft_ap_enabled());
}

TEST(WifiSoftAPTest, Start)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    soft_ap.start("SSID", "Password");
    ASSERT_TRUE(mockoc.was_called("esp_wifi_set_config"));
}

TEST(WifiSoftAPTest, Stop)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    soft_ap.start("SSID", "Password");
    soft_ap.stop();
    auto &wifi = Wifi::get_instance();
    ASSERT_FALSE(wifi->soft_ap_enabled());
}

TEST(WifiSoftAPTest, DestructorRemovesSoftAPMode)
{
    {
        WifiSoftAP soft_ap;
        soft_ap.init();
        soft_ap.start("SSID", "Password");
    }
    auto &wifi = Wifi::get_instance();
    ASSERT_FALSE(wifi->soft_ap_enabled());
}

TEST(WifiSoftAPTest, CallEventHandler)
{
    WifiSoftAP soft_ap;
    soft_ap.init();
    soft_ap.start("SSID", "Password");
    ASSERT_NO_THROW(
        mock_mcu.call_wifi_event_callback(WIFI_EVENT_AP_STACONNECTED, nullptr));
    ASSERT_NO_THROW(mock_mcu.call_wifi_event_callback(
        WIFI_EVENT_AP_STADISCONNECTED, nullptr));
}
