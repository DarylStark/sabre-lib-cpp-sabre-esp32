#ifndef MQTT_CLIENT_H_
#define MQTT_CLIENT_H_

#include "esp_event.h"
#include "esp_transport.h"
#include <stddef.h>

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

typedef enum esp_mqtt_transport_t
{
    MQTT_TRANSPORT_UNKNOWN = 0x0,
    MQTT_TRANSPORT_OVER_TCP, /*!< *MQTT* over TCP, using scheme: ``MQTT`` */
    MQTT_TRANSPORT_OVER_SSL, /*!< *MQTT* over SSL, using scheme: ``MQTTS`` */
    MQTT_TRANSPORT_OVER_WS, /*!< *MQTT* over Websocket, using scheme:: ``ws`` */
    MQTT_TRANSPORT_OVER_WSS /*!< *MQTT* over Websocket Secure, using scheme:
                             ``wss`` */
} esp_mqtt_transport_t;

typedef struct esp_mqtt_client_config_t
{
    /**
     *   Broker related configuration
     */
    struct broker_t
    {
        /**
         * Broker address
         *
         *  - uri have precedence over other fields
         *  - If uri isn't set at least hostname, transport and port should.
         */
        struct address_t
        {
            const char *uri; /*!< Complete *MQTT* broker URI */
            const char
                *hostname; /*!< Hostname, to set ipv4 pass it as string) */
            esp_mqtt_transport_t transport; /*!< Selects transport*/
            const char *path;               /*!< Path in the URI*/
            uint32_t port;                  /*!< *MQTT* server port */
        } address;                          /*!< Broker address configuration */
        /**
         * Broker identity verification
         *
         * If fields are not set broker's identity isn't verified. it's
         * recommended to set the options in this struct for security reasons.
         */
        struct verification_t
        {
            bool use_global_ca_store; /*!< Use a global ca_store, look esp-tls
                         documentation for details. */
            esp_err_t (*crt_bundle_attach)(
                void
                    *conf); /*!< Pointer to ESP x509 Certificate Bundle attach
                    function for the usage of certificate bundles. Client only
                    attach the bundle, the clean up must be done by the user. */
            const char *certificate; /*!< Certificate data, default is NULL.
                                        It's not copied nor freed by the client,
                                        user needs to clean up.*/
            size_t certificate_len;  /*!< Length of the buffer pointed to by
                                        certificate. */
            const struct psk_key_hint
                *psk_hint_key; /*!< Pointer to PSK struct defined in esp_tls.h
                       to enable PSK authentication (as alternative to
                       certificate verification). PSK is enabled only if there
                       are no other ways to verify broker. It's not copied nor
                       freed by the client, user needs to clean up.*/
            bool skip_cert_common_name_check; /*!< Skip any validation of server
                                      certificate CN field, this reduces the
                                      security of TLS and makes the *MQTT*
                                      client susceptible to MITM attacks  */
            const char *
                *alpn_protos; /*!< NULL-terminated list of supported application
                                 protocols to be used for ALPN.*/
            const char
                *common_name; /*!< Pointer to the string containing server
                                 certificate common name. If non-NULL, server
                                 certificate CN must match this name, If NULL,
                                 server certificate CN must match hostname. This
                                 is ignored if skip_cert_common_name_check=true.
                                   It's not copied nor freed by the client, user
                                 needs to clean up.*/
        } verification;       /*!< Security verification of the broker */
    } broker;                 /*!< Broker address and security verification */
    /**
     * Client related credentials for authentication.
     */
    struct credentials_t
    {
        const char *username; /*!< *MQTT* username */
        const char *
            client_id;           /*!< Set *MQTT* client identifier. Ignored if
                         set_null_client_id == true If NULL set          the default
                         client id.          Default client id is ``ESP32_%CHIPID%`` where
                         `%CHIPID%` are          last 3 bytes of MAC address in hex format
                       */
        bool set_null_client_id; /*!< Selects a NULL client id */
        /**
         * Client authentication
         *
         * Fields related to client authentication by broker
         *
         * For mutual authentication using TLS, user could select certificate
         * and key, secure element or digital signature peripheral if available.
         *
         */
        struct authentication_t
        {
            const char *password; /*!< *MQTT* password */
            const char
                *certificate; /*!< Certificate for ssl mutual authentication,
                      not required if mutual authentication is not needed. Must
                      be provided with `key`. It's not copied nor freed by the
                      client, user needs to clean up.*/
            size_t certificate_len; /*!< Length of the buffer pointed to by
                                       certificate.*/
            const char *key; /*!< Private key for SSL mutual authentication, not
                     required if mutual authentication is not needed. If it is
                     not NULL, also `certificate` has to be provided. It's not
                     copied nor freed by the client, user needs to clean up.*/
            size_t key_len;  /*!< Length of the buffer pointed to by key.*/
            const char *key_password; /*!< Client key decryption password, not
                               PEM nor DER, if provided `key_password_len` must
                               be correctly set.*/
            int key_password_len;     /*!< Length of the password pointed to by
                                         `key_password` */
            bool use_secure_element;  /*!< Enable secure element, available in
                                         ESP32-ROOM-32SE, for SSL connection */
            void *ds_data; /*!< Carrier of handle for digital signature
                   parameters, digital signature peripheral is available in some
                   Espressif devices.  It's not copied nor freed by the client,
                   user needs to clean up.*/
            bool use_ecdsa_peripheral; /*!< Enable ECDSA peripheral, available
                                          in some Espressif devices. */
            uint8_t
                ecdsa_key_efuse_blk; /*!< ECDSA key block number from efuse,
                                        available in some Espressif devices. */
        } authentication;            /*!< Client authentication */
    } credentials;                   /*!< User credentials for broker */
    /**
     * *MQTT* Session related configuration
     */
    struct session_t
    {
        /**
         * Last Will and Testament message configuration.
         */
        struct last_will_t
        {
            const char
                *topic;      /*!< LWT (Last Will and Testament) message topic */
            const char *msg; /*!< LWT message, may be NULL terminated*/
            int msg_len; /*!< LWT message length, if msg isn't NULL terminated
                            must have the correct length */
            int qos;     /*!< LWT message QoS */
            int retain;  /*!< LWT retained message flag */
        } last_will;     /*!< Last will configuration */
        bool disable_clean_session; /*!< *MQTT* clean session, default
                                       clean_session is true */
        int keepalive;          /*!< *MQTT* keepalive, default is 120 seconds
                                    When configuring this value, keep in mind that the
                                   client attempts          to communicate with the
                                   broker at half          the interval that is actually
                                   set.          This          conservative          approach
                                   allows for more attempts before          the broker's
                                   timeout          occurs */
        bool disable_keepalive; /*!< Set `disable_keepalive=true` to turn off
                        keep-alive mechanism, keepalive is active by default.
                        Note: setting the config value `keepalive` to `0`
                        doesn't disable keepalive feature, but uses a default
                        keepalive period */
        esp_mqtt_protocol_ver_t
            protocol_ver; /*!< *MQTT* protocol version used for connection.*/
        int message_retransmit_timeout; /*!< timeout for retransmitting of
                                           failed packet */
    } session;                          /*!< *MQTT* session configuration. */
    /**
     * Network related configuration
     */
    struct network_t
    {
        int reconnect_timeout_ms; /*!< Reconnect to the broker after this value
                          in miliseconds if auto reconnect is not disabled
                          (defaults to 10s) */
        int timeout_ms; /*!< Abort network operation if it is not completed
                after this value, in milliseconds (defaults to 10s). */
        int refresh_connection_after_ms; /*!< Refresh connection after this
                                            value (in milliseconds) */
        bool disable_auto_reconnect; /*!< Client will reconnect to server (when
                             errors/disconnect). Set
                             `disable_auto_reconnect=true` to disable */
        esp_transport_keep_alive_t
            tcp_keep_alive_cfg; /*!< Transport keep-alive config*/
        esp_transport_handle_t
            transport; /*!< Custom transport handle to use, leave it NULL to
                          allow MQTT client create or recreate its own. Warning:
                          The transport should be valid during the client
                          lifetime and is destroyed when esp_mqtt_client_destroy
                          is called. */
        struct ifreq
            *if_name; /*!< The name of interface for data to go through. Use the
                         default interface without setting */
    } network;        /*!< Network configuration */
    /**
     * Client task configuration
     */
    struct task_t
    {
        int priority;   /*!< *MQTT* task priority*/
        int stack_size; /*!< *MQTT* task stack size*/
    } task;             /*!< FreeRTOS task configuration.*/
    /**
     * Client buffer size configuration
     *
     * Client have two buffers for input and output respectivelly.
     */
    struct buffer_t
    {
        int size;     /*!< size of *MQTT* send/receive buffer*/
        int out_size; /*!< size of *MQTT* output buffer. If not defined,
              defaults to the size defined by
              ``buffer_size`` */
    } buffer;         /*!< Buffer size configuration.*/

    /**
     * Client outbox configuration options.
     */
    struct outbox_config_t
    {
        uint64_t limit; /*!< Size limit for the outbox in bytes.*/
    } outbox;           /*!< Outbox configuration. */
} esp_mqtt_client_config_t;

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
