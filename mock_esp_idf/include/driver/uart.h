#ifndef UART_H_
#define UART_H_

typedef struct {
    int baud_rate;
    uart_word_length_t data_bits;
    uart_parity_t parity;
    uart_stop_bits_t stop_bits;
    uart_hw_flowcontrol_t flow_ctrl;
    uint8_t rx_flow_ctrl_thresh;
    union {
        uart_sclk_t source_clk;
        lp_uart_sclk_t lp_source_clk;
    };
    struct {
        uint32_t allow_pd: 1;
        uint32_t backup_before_sleep: 1;
    } flags;                            
} uart_config_t;

#endif
