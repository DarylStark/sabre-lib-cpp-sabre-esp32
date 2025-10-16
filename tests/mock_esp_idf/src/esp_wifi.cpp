#include "esp_wifi.h"
#include "esp_event.h"
#include <mockoc.hpp>

const esp_event_base_t WIFI_EVENT = "wifi_event";
const esp_event_base_t IP_EVENT = "ip_event";

esp_err_t esp_wifi_set_mode(wifi_mode_t mode)
{
    return mock_call(
        "esp_wifi_set_mode", [](wifi_mode_t mode) { return ESP_OK; }, mode);
}

esp_err_t esp_wifi_init(const wifi_init_config_t *config)
{
    return mock_call(
        "esp_wifi_init",
        [](const wifi_init_config_t *config) { return ESP_OK; }, config);
}

esp_err_t esp_wifi_start(void)
{
    return mock_call(
        "esp_wifi_start", []() { return ESP_OK; });
}

esp_err_t esp_wifi_stop(void)
{
    return mock_call(
        "esp_wifi_stop", []() { return ESP_OK; });
}

esp_err_t esp_wifi_deinit(void)
{
    return mock_call(
        "esp_wifi_deinit", []() { return ESP_OK; });
}

esp_err_t esp_wifi_connect(void)
{
    return mock_call(
        "esp_wifi_connect", []() { return ESP_OK; });
}

esp_err_t esp_wifi_disconnect(void)
{
    return mock_call(
        "esp_wifi_disconnect", []() { return ESP_OK; });
}

esp_err_t esp_wifi_set_config(wifi_interface_t ifx, wifi_config_t *conf)
{
    return mock_call(
        "esp_wifi_set_config",
        [](wifi_interface_t ifx, wifi_config_t *conf) { return ESP_OK; }, ifx,
        conf);
}