#include "mock_mcu.hpp"

MockMCU::MockMCU(const MockMCUConfiguration config)
    : _gpio_bank(config.gpio_count), _time_synced(false)
{
}

void MockMCU::clear()
{
    _gpio_bank.clear();
    _time_synced = false;
    _mqtt_event_callback = nullptr;
    _wifi_event_callbacks.clear();
    _mqtt_event_arg = nullptr;
    _wifi_event_arg = nullptr;
    _time = 0;
}

GPIOBank &MockMCU::gpio_bank()
{
    return _gpio_bank;
}

void MockMCU::set_time_synced(bool synced)
{
    _time_synced = synced;
}

bool MockMCU::get_time_sync_status() const
{
    return _time_synced;
}

void MockMCU::set_mqtt_event_callback(esp_event_handler_t callback, void *args)
{
    _mqtt_event_callback = callback;
    _mqtt_event_arg = args;
}

void MockMCU::call_mqtt_event_callback(int32_t event_id, void *event_data)
{
    if (_mqtt_event_callback)
    {
        _mqtt_event_callback(_mqtt_event_arg, "MQTT_EVENT", event_id,
                             event_data);
    }
}

void MockMCU::set_time(uint64_t time_in_ms)
{
    _time = time_in_ms;
}

uint64_t MockMCU::get_time() const
{
    return _time;
}

void MockMCU::set_wifi_event_callback(esp_event_handler_t callback, void *args)
{
    _wifi_event_callbacks.push_back(std::make_pair(callback, args));
}

void MockMCU::call_wifi_event_callback(int32_t event_id, void *event_data)
{
    for (auto &callback_information : _wifi_event_callbacks)
        callback_information.first(callback_information.second, "WIFI_EVENT",
                                   event_id, event_data);
}