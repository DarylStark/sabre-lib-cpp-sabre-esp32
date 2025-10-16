#include "../include/esp_netif.h"
#include <mockoc.hpp>

esp_err_t esp_netif_init(void)
{
    return mock_call(
        "esp_netif_init", []() { return ESP_OK; });
}

esp_err_t esp_netif_deinit(void)
{
    return mock_call(
        "esp_netif_deinit", []() { return ESP_OK; });
}

esp_err_t esp_netif_create_default_wifi_sta(void)
{
    return mock_call(
        "esp_netif_create_default_wifi_sta", []() { return ESP_OK; });
}

esp_err_t esp_netif_create_default_wifi_ap(void)
{
    return mock_call(
        "esp_netif_create_default_wifi_ap", []() { return ESP_OK; });
}
