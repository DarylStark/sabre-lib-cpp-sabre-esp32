#include "../include/nvs_flash.h"
#include <mockoc.hpp>

esp_err_t nvs_flash_init(void)
{
    return mock_call(
        "nvs_flash_init", []() { return ESP_ERR_NVS_NO_FREE_PAGES; });
}

esp_err_t nvs_flash_erase(void)
{
    return mock_call(
        "nvs_flash_erase", []() { return ESP_OK; });
}
