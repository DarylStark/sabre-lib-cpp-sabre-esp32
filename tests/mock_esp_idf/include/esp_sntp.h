#ifndef ESP_SNTP_H
#define ESP_SNTP_H

#include "esp_err.h"
#include <cstdint>

typedef enum
{
    SNTP_SYNC_STATUS_RESET,       // Reset status.
    SNTP_SYNC_STATUS_COMPLETED,   // Time is synchronized.
    SNTP_SYNC_STATUS_IN_PROGRESS, // Smooth time sync in progress.
} sntp_sync_status_t;

sntp_sync_status_t sntp_get_sync_status(void);

#define esp_sntp_get_sync_status sntp_get_sync_status

void esp_sntp_init(void);
void esp_sntp_setservername(uint8_t idx, const char *server);
void esp_sntp_stop(void);

#endif
