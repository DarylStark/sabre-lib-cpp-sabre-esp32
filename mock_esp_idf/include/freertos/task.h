#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>

struct tskTaskControlBlock;
typedef struct tskTaskControlBlock *TaskHandle_t;
typedef int BaseType_t;

typedef void (*TaskFunction_t)(void *);
typedef unsigned int UBaseType_t;

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName,
                       const uint16_t usStackDepth, void *pvParameters,
                       UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask);

void vTaskDelete(TaskHandle_t xTaskToDelete);
void vTaskDelay(const TickType_t xTicksToDelay);

#endif
