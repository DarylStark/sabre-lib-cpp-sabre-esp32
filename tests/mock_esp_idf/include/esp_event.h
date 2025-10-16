#ifndef ESP_EVENT_H
#define ESP_EVENT_H

#include "esp_err.h"
#include "esp_event_base.h"
#include <stdint.h>

#define ESP_EVENT_ANY_ID -1

esp_err_t esp_event_loop_create_default(void);
esp_err_t esp_event_handler_register(esp_event_base_t event_base,
                                     int32_t event_id,
                                     esp_event_handler_t event_handler,
                                     void *event_handler_arg);
esp_err_t esp_event_handler_unregister(esp_event_base_t event_base,
                                       int32_t event_id,
                                       esp_event_handler_t event_handler);

#endif
