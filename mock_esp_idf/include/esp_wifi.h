#ifndef ESP_WIFI_H
#define ESP_WIFI_H

#include "esp_err.h"
#include "esp_event.h"
#include "esp_wifi_types_generic.h"

typedef struct
{
    // wifi_osi_funcs_t*      osi_funcs;
    // wpa_crypto_funcs_t     wpa_crypto_funcs;
    int static_rx_buf_num;
    int dynamic_rx_buf_num;
    int tx_buf_type;
    int static_tx_buf_num;
    int dynamic_tx_buf_num;
    int rx_mgmt_buf_type;
    int rx_mgmt_buf_num;
    int cache_tx_buf_num;
    int csi_enable;
    int ampdu_rx_enable;
    int ampdu_tx_enable;
    int amsdu_tx_enable;
    int nvs_enable;
    int nano_enable;
    int rx_ba_win;
    int wifi_task_core_id;
    int beacon_max_len;
    int mgmt_sbuf_num;
    uint64_t feature_caps;
    bool sta_disconnected_pm;
    int espnow_max_encrypt_num;
    int tx_hetb_queue_num;
    bool dump_hesigb_enable;
    int magic;
} wifi_init_config_t;

#define ESP_ERR_WIFI_NOT_INIT                                                  \
    (ESP_ERR_WIFI_BASE +                                                       \
     1) /*!< WiFi driver was not installed by esp_wifi_init */
#define ESP_ERR_WIFI_NOT_STARTED                                               \
    (ESP_ERR_WIFI_BASE +                                                       \
     2) /*!< WiFi driver was not started by esp_wifi_start */
#define ESP_ERR_WIFI_NOT_STOPPED                                               \
    (ESP_ERR_WIFI_BASE + 3) /*!< WiFi driver was not stopped by esp_wifi_stop  \
                             */
#define ESP_ERR_WIFI_IF (ESP_ERR_WIFI_BASE + 4)   /*!< WiFi interface error */
#define ESP_ERR_WIFI_MODE (ESP_ERR_WIFI_BASE + 5) /*!< WiFi mode error */
#define ESP_ERR_WIFI_STATE                                                     \
    (ESP_ERR_WIFI_BASE + 6) /*!< WiFi internal state error */
#define ESP_ERR_WIFI_CONN                                                      \
    (ESP_ERR_WIFI_BASE +                                                       \
     7) /*!< WiFi internal control block of station or soft-AP error */
#define ESP_ERR_WIFI_NVS                                                       \
    (ESP_ERR_WIFI_BASE + 8) /*!< WiFi internal NVS module error */
#define ESP_ERR_WIFI_MAC                                                       \
    (ESP_ERR_WIFI_BASE + 9)                        /*!< MAC address is invalid \
                                                    */
#define ESP_ERR_WIFI_SSID (ESP_ERR_WIFI_BASE + 10) /*!< SSID is invalid */
#define ESP_ERR_WIFI_PASSWORD                                                  \
    (ESP_ERR_WIFI_BASE + 11) /*!< Password is invalid */
#define ESP_ERR_WIFI_TIMEOUT (ESP_ERR_WIFI_BASE + 12) /*!< Timeout error */
#define ESP_ERR_WIFI_WAKE_FAIL                                                 \
    (ESP_ERR_WIFI_BASE +                                                       \
     13) /*!< WiFi is in sleep state(RF closed) and wakeup fail */
#define ESP_ERR_WIFI_WOULD_BLOCK                                               \
    (ESP_ERR_WIFI_BASE + 14) /*!< The caller would block */
#define ESP_ERR_WIFI_NOT_CONNECT                                               \
    (ESP_ERR_WIFI_BASE + 15) /*!< Station still in disconnect status */
#define ESP_ERR_WIFI_POST                                                      \
    (ESP_ERR_WIFI_BASE + 18) /*!< Failed to post the event to WiFi task */
#define ESP_ERR_WIFI_INIT_STATE                                                \
    (ESP_ERR_WIFI_BASE +                                                       \
     19) /*!< Invalid WiFi state when init/deinit is called */
#define ESP_ERR_WIFI_STOP_STATE                                                \
    (ESP_ERR_WIFI_BASE + 20) /*!< Returned when WiFi is stopping */
#define ESP_ERR_WIFI_NOT_ASSOC                                                 \
    (ESP_ERR_WIFI_BASE + 21) /*!< The WiFi connection is not associated */
#define ESP_ERR_WIFI_TX_DISALLOW                                               \
    (ESP_ERR_WIFI_BASE + 22) /*!< The WiFi TX is disallowed */
#define ESP_ERR_WIFI_TWT_FULL                                                  \
    (ESP_ERR_WIFI_BASE + 23) /*!< no available flow id */
#define ESP_ERR_WIFI_TWT_SETUP_TIMEOUT                                         \
    (ESP_ERR_WIFI_BASE +                                                       \
     24) /*!< Timeout of receiving twt setup response frame, timeout times can \
            be set during twt setup */
#define ESP_ERR_WIFI_TWT_SETUP_TXFAIL                                          \
    (ESP_ERR_WIFI_BASE + 25) /*!< TWT setup frame tx failed */
#define ESP_ERR_WIFI_TWT_SETUP_REJECT                                          \
    (ESP_ERR_WIFI_BASE +                                                       \
     26) /*!< The twt setup request was rejected by the AP */
#define ESP_ERR_WIFI_DISCARD (ESP_ERR_WIFI_BASE + 27) /*!< Discard frame */
#define ESP_ERR_WIFI_ROC_IN_PROGRESS                                           \
    (ESP_ERR_WIFI_BASE + 28) /*!< ROC op is in progress */
#define WIFI_STATIC_TX_BUFFER_NUM CONFIG_ESP_WIFI_STATIC_TX_BUFFER_NUM
#define WIFI_STATIC_TX_BUFFER_NUM 0
#define WIFI_CACHE_TX_BUFFER_NUM CONFIG_ESP_WIFI_CACHE_TX_BUFFER_NUM
#define WIFI_CACHE_TX_BUFFER_NUM 0
#define WIFI_DYNAMIC_TX_BUFFER_NUM CONFIG_ESP_WIFI_DYNAMIC_TX_BUFFER_NUM
#define WIFI_DYNAMIC_TX_BUFFER_NUM 0
#define WIFI_RX_MGMT_BUF_NUM_DEF CONFIG_ESP_WIFI_RX_MGMT_BUF_NUM_DEF
#define WIFI_RX_MGMT_BUF_NUM_DEF 0
#define WIFI_CSI_ENABLED 1
#define WIFI_CSI_ENABLED 0
#define WIFI_AMPDU_RX_ENABLED 1
#define WIFI_AMPDU_RX_ENABLED 0
#define WIFI_AMPDU_TX_ENABLED 1
#define WIFI_AMPDU_TX_ENABLED 0
#define WIFI_AMSDU_TX_ENABLED 1
#define WIFI_AMSDU_TX_ENABLED 0
#define WIFI_NVS_ENABLED 1
#define WIFI_NVS_ENABLED 0
#define WIFI_NANO_FORMAT_ENABLED 1
#define WIFI_NANO_FORMAT_ENABLED 0
#define WIFI_INIT_CONFIG_MAGIC 0x1F2F3F4F
#define WIFI_DEFAULT_RX_BA_WIN CONFIG_ESP_WIFI_RX_BA_WIN
#define WIFI_DEFAULT_RX_BA_WIN 0 /* unused if ampdu_rx_enable == false */
#define WIFI_TASK_CORE_ID 1
#define WIFI_TASK_CORE_ID 0
#define WIFI_SOFTAP_BEACON_MAX_LEN CONFIG_ESP_WIFI_SOFTAP_BEACON_MAX_LEN
#define WIFI_SOFTAP_BEACON_MAX_LEN 752
#define WIFI_MGMT_SBUF_NUM CONFIG_ESP_WIFI_MGMT_SBUF_NUM
#define WIFI_MGMT_SBUF_NUM 32
#define WIFI_STA_DISCONNECTED_PM_ENABLED true
#define WIFI_STA_DISCONNECTED_PM_ENABLED false
#define WIFI_ENABLE_WPA3_SAE (1 << 0)
#define WIFI_ENABLE_WPA3_SAE 0
#define WIFI_ENABLE_CACHE_TX_BUFFER (1 << 1)
#define WIFI_ENABLE_CACHE_TX_BUFFER 0
#define WIFI_FTM_INITIATOR (1 << 2)
#define WIFI_FTM_INITIATOR 0
#define WIFI_FTM_RESPONDER (1 << 3)
#define WIFI_FTM_RESPONDER 0
#define WIFI_ENABLE_GCMP (1 << 4)
#define WIFI_ENABLE_GCMP 0
#define WIFI_ENABLE_GMAC (1 << 5)
#define WIFI_ENABLE_GMAC 0
#define WIFI_ENABLE_11R (1 << 6)
#define WIFI_ENABLE_11R 0
#define WIFI_ENABLE_ENTERPRISE (1 << 7)
#define WIFI_ENABLE_ENTERPRISE 0
#define WIFI_DUMP_HESIGB_ENABLED true
#define WIFI_DUMP_HESIGB_ENABLED false
#define WIFI_TX_HETB_QUEUE_NUM CONFIG_ESP_WIFI_TX_HETB_QUEUE_NUM
#define WIFI_TX_HETB_QUEUE_NUM 1
#define WIFI_ENABLE_BSS_MAX_IDLE (1 << 8)
#define WIFI_ENABLE_BSS_MAX_IDLE 0
#define CONFIG_FEATURE_WPA3_SAE_BIT (1 << 0)
#define CONFIG_FEATURE_CACHE_TX_BUF_BIT (1 << 1)
#define CONFIG_FEATURE_FTM_INITIATOR_BIT (1 << 2)
#define CONFIG_FEATURE_FTM_RESPONDER_BIT (1 << 3)
#define CONFIG_FEATURE_GCMP_BIT (1 << 4)
#define CONFIG_FEATURE_GMAC_BIT (1 << 5)
#define CONFIG_FEATURE_11R_BIT (1 << 6)
#define CONFIG_FEATURE_WIFI_ENT_BIT (1 << 7)
#define CONFIG_FEATURE_BSS_MAX_IDLE_BIT (1 << 8)
#define ESP_WIFI_CONNECTIONLESS_INTERVAL_DEFAULT_MODE 0
#define CONFIG_ESP_WIFI_STATIC_RX_BUFFER_NUM 10
#define CONFIG_ESP_WIFI_TX_BUFFER_TYPE 0
#define CONFIG_ESP_WIFI_STATIC_RX_BUFFER_NUM 10
#define CONFIG_ESP_WIFI_ESPNOW_MAX_ENCRYPT_NUM 0
#define CONFIG_ESP_WIFI_DYNAMIC_RX_MGMT_BUF 0
#define CONFIG_ESP_WIFI_DYNAMIC_RX_BUFFER_NUM 10

#define WIFI_FEATURE_CAPS                                                      \
    (WIFI_ENABLE_WPA3_SAE | WIFI_ENABLE_CACHE_TX_BUFFER | WIFI_FTM_INITIATOR | \
     WIFI_FTM_RESPONDER | WIFI_ENABLE_GCMP | WIFI_ENABLE_GMAC |                \
     WIFI_ENABLE_11R | WIFI_ENABLE_ENTERPRISE | WIFI_ENABLE_BSS_MAX_IDLE)

#define WIFI_INIT_CONFIG_DEFAULT()                                             \
    {.static_rx_buf_num = CONFIG_ESP_WIFI_STATIC_RX_BUFFER_NUM,                \
     .dynamic_rx_buf_num = CONFIG_ESP_WIFI_DYNAMIC_RX_BUFFER_NUM,              \
     .tx_buf_type = CONFIG_ESP_WIFI_TX_BUFFER_TYPE,                            \
     .static_tx_buf_num = WIFI_STATIC_TX_BUFFER_NUM,                           \
     .dynamic_tx_buf_num = WIFI_DYNAMIC_TX_BUFFER_NUM,                         \
     .rx_mgmt_buf_type = CONFIG_ESP_WIFI_DYNAMIC_RX_MGMT_BUF,                  \
     .rx_mgmt_buf_num = WIFI_RX_MGMT_BUF_NUM_DEF,                              \
     .cache_tx_buf_num = WIFI_CACHE_TX_BUFFER_NUM,                             \
     .csi_enable = WIFI_CSI_ENABLED,                                           \
     .ampdu_rx_enable = WIFI_AMPDU_RX_ENABLED,                                 \
     .ampdu_tx_enable = WIFI_AMPDU_TX_ENABLED,                                 \
     .amsdu_tx_enable = WIFI_AMSDU_TX_ENABLED,                                 \
     .nvs_enable = WIFI_NVS_ENABLED,                                           \
     .nano_enable = WIFI_NANO_FORMAT_ENABLED,                                  \
     .rx_ba_win = WIFI_DEFAULT_RX_BA_WIN,                                      \
     .wifi_task_core_id = WIFI_TASK_CORE_ID,                                   \
     .beacon_max_len = WIFI_SOFTAP_BEACON_MAX_LEN,                             \
     .mgmt_sbuf_num = WIFI_MGMT_SBUF_NUM,                                      \
     .feature_caps = WIFI_FEATURE_CAPS,                                        \
     .sta_disconnected_pm = WIFI_STA_DISCONNECTED_PM_ENABLED,                  \
     .espnow_max_encrypt_num = CONFIG_ESP_WIFI_ESPNOW_MAX_ENCRYPT_NUM,         \
     .tx_hetb_queue_num = WIFI_TX_HETB_QUEUE_NUM,                              \
     .dump_hesigb_enable = WIFI_DUMP_HESIGB_ENABLED,                           \
     .magic = WIFI_INIT_CONFIG_MAGIC};

esp_err_t esp_wifi_set_mode(wifi_mode_t mode);
esp_err_t esp_wifi_init(const wifi_init_config_t *config);
esp_err_t esp_wifi_start(void);
esp_err_t esp_wifi_stop(void);
esp_err_t esp_wifi_deinit(void);
esp_err_t esp_wifi_connect(void);

#endif
