#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/wifi/wifi.hpp>
#include <thread>

TEST(Wifi, SingletonInstance)
{
    auto &wifi1 = sabre::esp32::Wifi::get_instance();
    auto &wifi2 = sabre::esp32::Wifi::get_instance();

    ASSERT_EQ(wifi1, wifi2);
}

TEST(Wifi, Initialization)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->init();
    ASSERT_TRUE(mockoc.was_called("esp_netif_init"));
    ASSERT_TRUE(mockoc.was_called("esp_event_loop_create_default"));
    ASSERT_TRUE(mockoc.was_called("esp_wifi_init"));
}

TEST(Wifi, InitializationDouble)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->init();
    mockoc.clear();
    wifi->init();
    ASSERT_FALSE(mockoc.was_called("esp_netif_init"));
    ASSERT_FALSE(mockoc.was_called("esp_event_loop_create_default"));
    ASSERT_FALSE(mockoc.was_called("esp_wifi_init"));
}

TEST(Wifi, Start)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    std::thread event_thread(
        [&wifi]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_STA_START, nullptr);
        });
    wifi->init();
    wifi->start(50);
    event_thread.join();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_start"));
    ASSERT_TRUE(wifi->is_started());
}

TEST(Wifi, StartFail)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->reset();
    wifi->init();
    wifi->start(10);
    ASSERT_FALSE(wifi->is_started());
}

TEST(Wifi, StartDouble)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    std::thread event_thread(
        [&wifi]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_STA_START, nullptr);
        });
    wifi->init();
    wifi->start();
    event_thread.join();
    mockoc.clear();
    wifi->start();
    ASSERT_FALSE(mockoc.was_called("esp_wifi_start"));
}

TEST(Wifi, Deinitialize)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->init();
    wifi->deinitialize();
    ASSERT_TRUE(mockoc.was_called("esp_wifi_deinit"));
    ASSERT_TRUE(mockoc.was_called("esp_netif_deinit"));
}

TEST(Wifi, EnableStationMode)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::STATION);
    ASSERT_TRUE(wifi->station_enabled());
}

TEST(Wifi, DisableStationMode)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::STATION);
    ASSERT_TRUE(wifi->station_enabled());
    wifi->remove_mode(sabre::esp32::WifiMode::STATION);
    ASSERT_FALSE(wifi->station_enabled());
}

TEST(Wifi, EnableSoftAPMode)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::SOFT_AP);
    ASSERT_TRUE(wifi->soft_ap_enabled());
}

TEST(Wifi, DisableSoftAPMode)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::SOFT_AP);
    ASSERT_TRUE(wifi->soft_ap_enabled());
    wifi->remove_mode(sabre::esp32::WifiMode::SOFT_AP);
    ASSERT_FALSE(wifi->soft_ap_enabled());
}

TEST(Wifi, EnableBothModes)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::SOFT_AP);
    wifi->add_mode(sabre::esp32::WifiMode::STATION);
    ASSERT_TRUE(wifi->soft_ap_enabled());
    ASSERT_TRUE(wifi->station_enabled());
}

TEST(Wifi, DeinitializeWithEnabledModes)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->add_mode(sabre::esp32::WifiMode::SOFT_AP);
    wifi->add_mode(sabre::esp32::WifiMode::STATION);
    wifi->deinitialize();
    ASSERT_FALSE(mockoc.was_called("esp_wifi_deinit"));
}

TEST(Wifi, StopWifiByEventSTA)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    std::thread event_thread(
        [&wifi]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_STA_START, nullptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_STA_STOP, nullptr);
        });
    wifi->init();
    wifi->start();
    event_thread.join();
    ASSERT_FALSE(wifi->is_started());
}

TEST(Wifi, StopWifiByEventAP)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    std::thread event_thread(
        [&wifi]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_AP_START, nullptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            wifi->handle_event(0, WIFI_EVENT_AP_STOP, nullptr);
        });
    wifi->init();
    wifi->start();
    event_thread.join();
    ASSERT_FALSE(wifi->is_started());
}

TEST(Wifi, RunEventCallback)
{
    auto &wifi = sabre::esp32::Wifi::get_instance();
    wifi->init();
    mock_mcu.call_wifi_event_callback(WIFI_EVENT_STA_START, nullptr);
    ASSERT_TRUE(wifi->is_started());
}