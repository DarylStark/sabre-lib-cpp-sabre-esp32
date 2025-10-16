#ifndef UART_H_
#define UART_H_

#include "../esp_err.h"
#include "freertos/FreeRTOS.h"
#include <cstddef>

#define UART_PIN_NO_CHANGE (-1)

typedef enum
{
    UART_NUM_0,
    UART_NUM_1,
#if SOC_UART_HP_NUM > 2
    UART_NUM_2,
#endif
#if SOC_UART_HP_NUM > 3
    UART_NUM_3,
#endif
#if SOC_UART_HP_NUM > 4
    UART_NUM_4,
#endif
#if (SOC_UART_LP_NUM >= 1)
    LP_UART_NUM_0,
#endif
    UART_NUM_MAX,
} uart_port_t;

typedef enum
{
    UART_DATA_5_BITS = 0x0, /*!< word length: 5bits*/
    UART_DATA_6_BITS = 0x1, /*!< word length: 6bits*/
    UART_DATA_7_BITS = 0x2, /*!< word length: 7bits*/
    UART_DATA_8_BITS = 0x3, /*!< word length: 8bits*/
    UART_DATA_BITS_MAX = 0x4,
} uart_word_length_t;

typedef enum
{
    UART_PARITY_DISABLE = 0x0, /*!< Disable UART parity*/
    UART_PARITY_EVEN = 0x2,    /*!< Enable UART even parity*/
    UART_PARITY_ODD = 0x3      /*!< Enable UART odd parity*/
} uart_parity_t;

typedef enum
{
    UART_STOP_BITS_1 = 0x1,   /*!< stop bit: 1bit*/
    UART_STOP_BITS_1_5 = 0x2, /*!< stop bit: 1.5bits*/
    UART_STOP_BITS_2 = 0x3,   /*!< stop bit: 2bits*/
    UART_STOP_BITS_MAX = 0x4,
} uart_stop_bits_t;

typedef enum
{
    UART_HW_FLOWCTRL_DISABLE = 0x0, /*!< disable hardware flow control*/
    UART_HW_FLOWCTRL_RTS = 0x1,     /*!< enable RX hardware flow control (rts)*/
    UART_HW_FLOWCTRL_CTS = 0x2,     /*!< enable TX hardware flow control (cts)*/
    UART_HW_FLOWCTRL_CTS_RTS = 0x3, /*!< enable hardware flow control*/
    UART_HW_FLOWCTRL_MAX = 0x4,
} uart_hw_flowcontrol_t;

typedef enum
{
    UART_SCLK_DEFAULT = 0,
    UART_SCLK_XTAL,
    UART_SCLK_APB,
    UART_SCLK_REF_TICK
} uart_sclk_t;

typedef enum
{
    LP_UART_SCLK_DEFAULT = 0
} lp_uart_sclk_t;

typedef struct
{
    int baud_rate;
    uart_word_length_t data_bits;
    uart_parity_t parity;
    uart_stop_bits_t stop_bits;
    uart_hw_flowcontrol_t flow_ctrl;
    uint8_t rx_flow_ctrl_thresh;
    union
    {
        uart_sclk_t source_clk;
        lp_uart_sclk_t lp_source_clk;
    };
    struct
    {
        uint32_t allow_pd : 1;
        uint32_t backup_before_sleep : 1;
    } flags;
} uart_config_t;

esp_err_t uart_param_config(uart_port_t uart_num,
                            const uart_config_t *uart_config);
esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num,
                       int rts_io_num, int cts_io_num);
esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size,
                              int tx_buffer_size, int queue_size,
                              QueueHandle_t *uart_queue, int intr_alloc_flags);
esp_err_t uart_driver_delete(uart_port_t uart_num);
esp_err_t uart_write_bytes(uart_port_t uart_num, const char *src, size_t size);
int uart_read_bytes(uart_port_t uart_num, void *buf, uint32_t length,
                    TickType_t ticks_to_wait);
esp_err_t uart_flush_input(uart_port_t uart_num);

#endif
