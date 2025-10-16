#ifndef NVS_FLASH_H
#define NVS_FLASH_H

#include "esp_err.h"

#define ESP_ERR_NVS_NO_FREE_PAGES (-1001)
#define ESP_ERR_NVS_NEW_VERSION_FOUND (-1002)

esp_err_t nvs_flash_init(void);
esp_err_t nvs_flash_erase(void);

#endif // NVS_FLASH_H