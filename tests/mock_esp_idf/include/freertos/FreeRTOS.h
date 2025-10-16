#ifndef FREERTOS_H_
#define FREERTOS_H_

#include <stdint.h>

typedef void *QueueHandle_t;
typedef uint32_t TickType_t;

#define configTICK_RATE_HZ 1000

#define portTICK_PERIOD_MS ((TickType_t)1000 / configTICK_RATE_HZ)

#endif // FREERTOS_H_