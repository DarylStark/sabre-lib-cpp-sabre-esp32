#include "../../include/freertos/task.h"
#include <mockoc.hpp>

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName,
                       const uint16_t usStackDepth, void *pvParameters,
                       UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask)
{
    return mock_call(
        "xTaskCreate",
        [](TaskFunction_t pxTaskCode, const char *const pcName,
           const uint16_t usStackDepth, void *pvParameters,
           UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask)
        {
            *pxCreatedTask = reinterpret_cast<TaskHandle_t>(0x1);
            pxTaskCode(pvParameters);
            return 1;
        },
        pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority,
        pxCreatedTask);
}

void vTaskDelete(TaskHandle_t xTaskToDelete)
{
    mock_call(
        "vTaskDelete", [](TaskHandle_t xTaskToDelete) {}, xTaskToDelete);
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    mock_call(
        "vTaskDelay", [](const TickType_t xTicksToDelay) {}, xTicksToDelay);
}
