#ifndef ESP_NETIF_H
#define ESP_NETIF_H

#include "esp_err.h"
#include <cstdint>
#include <stdbool.h>

struct esp_ip4_addr
{
    uint32_t addr; /*!< IPv4 address */
};

typedef struct esp_ip4_addr esp_ip4_addr_t;

typedef struct esp_netif_obj esp_netif_t;
typedef struct esp_netif_ip_info
{
    esp_ip4_addr_t ip;      /*!< IP address */
    esp_ip4_addr_t netmask; /*!< Netmask */
    esp_ip4_addr_t gw;      /*!< Gateway address */
} esp_netif_ip_info_t;

typedef struct
{
    esp_netif_t *esp_netif;
    esp_netif_ip_info_t ip_info;
    bool ip_changed;
} ip_event_got_ip_t;

esp_err_t esp_netif_init(void);
esp_err_t esp_netif_deinit(void);

esp_err_t esp_netif_create_default_wifi_sta(void);
esp_err_t esp_netif_create_default_wifi_ap(void);

#endif
