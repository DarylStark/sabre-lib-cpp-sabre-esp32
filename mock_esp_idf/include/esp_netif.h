#ifndef ESP_NETIF_H
#define ESP_NETIF_H

#include "esp_err.h"

typedef struct
{
    esp_netif_t *esp_netif;
    esp_netif_ip_info_t ip_info;
    bool ip_changed;
} ip_event_got_ip_t;

esp_err_t esp_netif_init(void);
esp_err_t esp_netif_deinit(void);

#endif
