#include "../include/esp_sntp.h"
#include <mockoc.hpp>

sntp_sync_status_t sntp_get_sync_status(void)
{
    return mock_call(
        "sntp_get_sync_status", []() { return SNTP_SYNC_STATUS_COMPLETED; });
}

void esp_sntp_init(void)
{
    mock_call(
        "esp_sntp_init", []() {});
}

void esp_sntp_setservername(uint8_t idx, const char *server)
{
    mock_call(
        "esp_sntp_setservername", [](uint8_t idx, const char *server) {}, idx,
        server);
}

void esp_sntp_stop(void)
{
    mock_call(
        "esp_sntp_stop", []() {});
}
