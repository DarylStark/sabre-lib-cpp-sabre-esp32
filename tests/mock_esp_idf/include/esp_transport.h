#ifndef ESP_TRANSPORT_H_
#define ESP_TRANSPORT_H_

typedef struct esp_transport_keepalive
{
    bool keep_alive_enable;  /*!< Enable keep-alive timeout */
    int keep_alive_idle;     /*!< Keep-alive idle time (second) */
    int keep_alive_interval; /*!< Keep-alive interval time (second) */
    int keep_alive_count;    /*!< Keep-alive packet retry send count */
} esp_transport_keep_alive_t;

struct esp_transport_item_t
{
    int port;
    char *scheme;
    void *data;
    // connect_func _connect;
    // io_read_func _read;
    // io_func _write;
    // trans_func _close;
    // poll_func _poll_read;
    // poll_func _poll_write;
    // trans_func _destroy;
    // connect_async_func _connect_async;
    // payload_transfer_func _parent_transfer;
    // get_socket_func _get_socket;
    esp_transport_keep_alive_t *keep_alive_cfg;
    struct esp_foundation_transport *foundation;
};

typedef struct esp_transport_item_t *esp_transport_handle_t;
#endif // ESP_TRANSPORT_H_