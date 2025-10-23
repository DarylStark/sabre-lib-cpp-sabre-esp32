#include "../include/mqtt_client.h"
#include "mcu.hpp"
#include <mockoc.hpp>

esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client,
                                         esp_mqtt_event_id_t event_id,
                                         esp_event_handler_t event_handler,
                                         void *event_handler_arg)
{
    return mock_call(
        "esp_mqtt_client_register_event",
        [](esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event_id,
           esp_event_handler_t event_handler, void *event_handler_arg)
        {
            mock_mcu.set_mqtt_event_callback(event_handler, event_handler_arg);
            return ESP_OK;
        },
        client, event_id, event_handler, event_handler_arg);
}

esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client)
{
    return mock_call(
        "esp_mqtt_client_destroy",
        [](esp_mqtt_client_handle_t client) { return ESP_OK; }, client);
}

esp_mqtt_client_handle_t esp_mqtt_client_init(const void *config)
{
    return mock_call(
        "esp_mqtt_client_init",
        [](const void *config)
        { return reinterpret_cast<esp_mqtt_client_handle_t>(0x1); },
        config);
}

esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client)
{
    return mock_call(
        "esp_mqtt_client_start",
        [](esp_mqtt_client_handle_t client) { return ESP_OK; }, client);
}

esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client)
{
    return mock_call(
        "esp_mqtt_client_stop",
        [](esp_mqtt_client_handle_t client) { return ESP_OK; }, client);
}

int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client,
                              const char *topic, int qos)
{
    return mock_call(
        "esp_mqtt_client_subscribe",
        [](esp_mqtt_client_handle_t client, const char *topic, int qos)
        { return 0; },
        client, topic, qos);
}

esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client)
{
    return mock_call(
        "esp_mqtt_client_disconnect",
        [](esp_mqtt_client_handle_t client) { return ESP_OK; }, client);
}

int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic,
                            const char *data, int len, int qos, int retain)
{
    return mock_call(
        "esp_mqtt_client_publish",
        [](esp_mqtt_client_handle_t client, const char *topic, const char *data,
           int len, int qos, int retain) { return 0; },
        client, topic, data, len, qos, retain);
}
