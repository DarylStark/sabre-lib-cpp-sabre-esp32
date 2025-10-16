#include "../include/esp_event.h"
#include <mockoc.hpp>

esp_err_t esp_event_loop_create_default(void)
{
    return mock_call(
        "esp_event_loop_create_default", []() { return ESP_OK; });
}

esp_err_t esp_event_handler_register(esp_event_base_t event_base,
                                     int32_t event_id,
                                     esp_event_handler_t event_handler,
                                     void *event_handler_arg)
{
    return mock_call(
        "esp_event_handler_register",
        [](esp_event_base_t event_base, int32_t event_id,
           esp_event_handler_t event_handler, void *event_handler_arg)
        { return ESP_OK; },
        event_base, event_id, event_handler, event_handler_arg);
}

esp_err_t esp_event_handler_unregister(esp_event_base_t event_base,
                                       int32_t event_id,
                                       esp_event_handler_t event_handler)
{
    return mock_call(
        "esp_event_handler_unregister",
        [](esp_event_base_t event_base, int32_t event_id,
           esp_event_handler_t event_handler) { return ESP_OK; },
        event_base, event_id, event_handler);
}
