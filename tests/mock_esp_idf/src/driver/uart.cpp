#include "../../include/driver/uart.h"
#include <mockoc.hpp>

esp_err_t uart_param_config(uart_port_t uart_num,
                            const uart_config_t *uart_config)
{
    return mock_call(
        "uart_param_config",
        [](uart_port_t uart_num, const uart_config_t *uart_config)
        { return ESP_OK; },
        uart_num, uart_config);
}

esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num,
                       int rts_io_num, int cts_io_num)
{
    return mock_call(
        "uart_set_pin",
        [](uart_port_t uart_num, int tx_io_num, int rx_io_num, int rts_io_num,
           int cts_io_num) { return ESP_OK; },
        uart_num, tx_io_num, rx_io_num, rts_io_num, cts_io_num);
}

esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size,
                              int tx_buffer_size, int queue_size,
                              QueueHandle_t *uart_queue, int intr_alloc_flags)
{
    return mock_call(
        "uart_driver_install",
        [](uart_port_t uart_num, int rx_buffer_size, int tx_buffer_size,
           int queue_size, QueueHandle_t *uart_queue, int intr_alloc_flags)
        {
            if (uart_queue)
                *uart_queue = nullptr;
            return ESP_OK;
        },
        uart_num, rx_buffer_size, tx_buffer_size, queue_size, uart_queue,
        intr_alloc_flags);
}

esp_err_t uart_driver_delete(uart_port_t uart_num)
{
    return mock_call(
        "uart_driver_delete", [](uart_port_t uart_num) { return ESP_OK; },
        uart_num);
}

esp_err_t uart_write_bytes(uart_port_t uart_num, const char *src, size_t size)
{
    return mock_call(
        "uart_write_bytes",
        [](uart_port_t uart_num, const char *src, size_t size)
        { return ESP_OK; },
        uart_num, src, size);
}

int uart_read_bytes(uart_port_t uart_num, void *buf, uint32_t length,
                    TickType_t ticks_to_wait)
{
    return mock_call(
        "uart_read_bytes",
        [](uart_port_t uart_num, void *buf, uint32_t length,
           TickType_t ticks_to_wait) { return 0; },
        uart_num, buf, length, ticks_to_wait);
}

esp_err_t uart_flush_input(uart_port_t uart_num)
{
    return mock_call(
        "uart_flush_input", [](uart_port_t uart_num) { return ESP_OK; },
        uart_num);
}
