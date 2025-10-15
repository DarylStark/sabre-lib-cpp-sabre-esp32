#ifndef MQTT_CLIENT_H_
#define MQTT_CLIENT_H_

#include "esp_event.h"

typedef enum esp_mqtt_protocol_ver_t
{
    MQTT_PROTOCOL_UNDEFINED = 0,
    MQTT_PROTOCOL_V_3_1,
    MQTT_PROTOCOL_V_3_1_1,
    MQTT_PROTOCOL_V_5,
} esp_mqtt_protocol_ver_t;

typedef enum esp_mqtt_error_type_t
{
    MQTT_ERROR_TYPE_NONE = 0,
    MQTT_ERROR_TYPE_TCP_TRANSPORT,
    MQTT_ERROR_TYPE_CONNECTION_REFUSED,
    MQTT_ERROR_TYPE_SUBSCRIBE_FAILED
} esp_mqtt_error_type_t;

typedef enum esp_mqtt_connect_return_code_t
{
    MQTT_CONNECTION_ACCEPTED = 0,       /*!< Connection accepted  */
    MQTT_CONNECTION_REFUSE_PROTOCOL,    /*!< *MQTT* connection refused reason:
                                         Wrong    protocol */
    MQTT_CONNECTION_REFUSE_ID_REJECTED, /*!< *MQTT* connection refused reason:
                                         ID rejected */
    MQTT_CONNECTION_REFUSE_SERVER_UNAVAILABLE, /*!< *MQTT* connection refused
                                                reason: Server unavailable */
    MQTT_CONNECTION_REFUSE_BAD_USERNAME,  /*!< *MQTT* connection refused reason:
                                           Wrong user */
    MQTT_CONNECTION_REFUSE_NOT_AUTHORIZED /*!< *MQTT* connection refused reason:
                                           Wrong username or password */
} esp_mqtt_connect_return_code_t;

typedef struct esp_mqtt_client *esp_mqtt_client_handle_t;

typedef struct esp_mqtt_error_codes
{
    /* compatible portion of the struct corresponding to struct
     * esp_tls_last_error
     */
    esp_err_t esp_tls_last_esp_err; /*!< last esp_err code reported from esp-tls
                                     component */
    int esp_tls_stack_err; /*!< tls specific error code reported from underlying
                            tls stack */
    int esp_tls_cert_verify_flags; /*!< tls flags reported from underlying tls
                                    stack during certificate verification */
    /* esp-mqtt specific structure extension */
    esp_mqtt_error_type_t
        error_type; /*!< error type referring to the source of the error */
    esp_mqtt_connect_return_code_t
        connect_return_code; /*!< connection refused error code reported from
                              *MQTT* broker on connection */
    /* tcp_transport extension */
    int esp_transport_sock_errno; /*!< errno from the underlying socket */

} esp_mqtt_error_codes_t;

typedef enum esp_mqtt_event_id_t
{
    MQTT_EVENT_ANY = -1,
    MQTT_EVENT_ERROR =
        0, /*!< on error event, additional context: connection return code,
            error handle from esp_tls (if supported) */
    MQTT_EVENT_CONNECTED,    /*!< connected event, additional context:
                              session_present flag */
    MQTT_EVENT_DISCONNECTED, /*!< disconnected event */
    MQTT_EVENT_SUBSCRIBED,   /*!< subscribed event, additional context:
                                - msg_id               message id
                                - error_handle         `error_type` in case
                              subscribing failed
                                - data                 pointer to broker response,
                              check for errors.
                                - data_len             length of the data for this
                              event
                                */
    MQTT_EVENT_UNSUBSCRIBED, /*!< unsubscribed event, additional context: msg_id
                              */
    MQTT_EVENT_PUBLISHED, /*!< published event, additional context:  msg_id */
    MQTT_EVENT_DATA,      /*!< data event, additional context:
                             - msg_id               message id
                             - topic                pointer to the received topic
                             - topic_len            length of the topic
                             - data                 pointer to the received data
                             - data_len             length of the data for this event
                             - current_data_offset  offset of the current data for
                           this event
                             - total_data_len       total length of the data received
                             - retain               retain flag of the message
                             - qos                  QoS level of the message
                             - dup                  dup flag of the message
                             Note: Multiple MQTT_EVENT_DATA could be fired for one
                           message, if it is         longer than internal buffer. In
                           that      case only first event contains topic      pointer      and
                           length,      other contain data only with current data
                           length         and      current data offset updating.
                              */
    MQTT_EVENT_BEFORE_CONNECT, /*!< The event occurs before connecting */
    MQTT_EVENT_DELETED, /*!< Notification on delete of one message from the
                         internal outbox,        if the message couldn't have
                         been sent and acknowledged before expiring defined in
                         OUTBOX_EXPIRED_TIMEOUT_MS.        (events are not
                         posted upon deletion of successfully acknowledged
                         messages)
                           - This event id is posted only if
                         MQTT_REPORT_DELETED_MESSAGES==1
                           - Additional context: msg_id (id of the deleted
                         message).
                           */
    MQTT_USER_EVENT,    /*!< Custom event used to queue tasks into mqtt event
                         handler    All fields from the esp_mqtt_event_t type could
                         be    used to pass    an additional context data to the
                         handler.
                         */
} esp_mqtt_event_id_t;

typedef struct esp_mqtt_event_t
{
    esp_mqtt_event_id_t event_id;
    esp_mqtt_client_handle_t client;
    char *data;
    int data_len;
    int total_data_len;
    int current_data_offset;
    char *topic;
    int topic_len;
    int msg_id;
    int session_present;
    esp_mqtt_error_codes_t *error_handle;
    bool retain;
    int qos;
    bool dup;
    esp_mqtt_protocol_ver_t protocol_ver;

} esp_mqtt_event_t;

typedef esp_mqtt_event_t *esp_mqtt_event_handle_t;

esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client,
                                         esp_mqtt_event_id_t event_id,
                                         esp_event_handler_t event_handler,
                                         void *event_handler_arg);
esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client);
esp_mqtt_client_handle_t esp_mqtt_client_init(const void *config);
esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client);
esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client);
int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client,
                              const char *topic, int qos);
esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client);
int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic,
                            const char *data, int len, int qos, int retain);

#endif
