#pragma once

#include "gpio_bank.hpp"
#include <vector>

typedef void (*esp_event_handler_t)(void *event_handler_arg,
                                    const char *event_base, int32_t event_id,
                                    void *event_data);

struct MockMCUConfiguration
{
    int gpio_count;
};

class MockMCU
{
private:
    GPIOBank _gpio_bank;
    bool _time_synced;
    esp_event_handler_t _mqtt_event_callback;
    std::vector<std::pair<esp_event_handler_t, void *>> _wifi_event_callbacks;
    void *_mqtt_event_arg;
    void *_wifi_event_arg;
    uint64_t _time;

public:
    MockMCU(const MockMCUConfiguration config);
    void clear();

    GPIOBank &gpio_bank();

    void set_time_synced(bool synced);
    bool get_time_sync_status() const;

    void set_mqtt_event_callback(esp_event_handler_t callback, void *args);
    void call_mqtt_event_callback(int32_t event_id, void *event_data);

    void set_time(uint64_t time_in_ms);
    uint64_t get_time() const;

    void set_wifi_event_callback(esp_event_handler_t callback, void *args);
    void call_wifi_event_callback(int32_t event_id, void *event_data);
};