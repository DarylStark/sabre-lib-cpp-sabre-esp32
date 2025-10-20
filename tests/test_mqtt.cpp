#include <gtest/gtest.h>
#include <mockoc.hpp>
#include <sabre_esp32/clients/mqtt.hpp>

using namespace sabre::esp32;

TEST(MQTTClient, BasicCreation)
{
    MQTTClient client;
    ASSERT_FALSE(client.is_connected());
}

TEST(MQTTClient, AfterConnectEvent)
{
    MQTTClient client;
    client.handle_event("", MQTT_EVENT_CONNECTED, nullptr);
    ASSERT_TRUE(client.is_connected());
}

TEST(MQTTClient, AfterDisconnectEvent)
{
    MQTTClient client;
    client.handle_event("", MQTT_EVENT_DISCONNECTED, nullptr);
    ASSERT_FALSE(client.is_connected());
}

TEST(MQTTClient, ProcessReceivedCallsSubscription)
{
    MQTTClient client;
    bool called = false;

    client.subscribe("test/topic",
                     [&](const sabre::MQTTEvent &event)
                     {
                         called = true;
                         ASSERT_EQ(event.topic, "test/topic");
                         ASSERT_EQ(event.data, "Hello, MQTT!");
                     });

    sabre::MQTTEvent event{"test/topic", "Hello, MQTT!",
                           sabre::MQTTQoS::FIRE_AND_FORGET,
                           sabre::MQTTRetain::DONT_RETAIN};
    client.process_received(event);

    ASSERT_TRUE(called);
}

TEST(MQTTClient, ProcessReceivedOnEvent)
{
    MQTTClient client;
    bool called = false;

    client.subscribe("test/topic",
                     [&](const sabre::MQTTEvent &event)
                     {
                         called = true;
                         ASSERT_EQ(event.topic, "test/topic");
                         ASSERT_EQ(event.data, "Hello, MQTT!");
                     });

    esp_mqtt_event_t mock_event;
    mock_event.topic = const_cast<char *>("test/topic");
    mock_event.topic_len = strlen("test/topic");
    mock_event.data = const_cast<char *>("Hello, MQTT!");
    mock_event.data_len = strlen("Hello, MQTT!");

    client.handle_event("", MQTT_EVENT_DATA, &mock_event);

    ASSERT_TRUE(called);
}

TEST(MQTTClient, ProcessReceivedCallsDefaultHandler)
{
    MQTTClient client;
    bool called = false;

    client.set_default_handler(
        [&](const sabre::MQTTEvent &event)
        {
            called = true;
            ASSERT_EQ(event.topic, "unsubscribed/topic");
            ASSERT_EQ(event.data, "Default handler message");
        });

    sabre::MQTTEvent event{"unsubscribed/topic", "Default handler message",
                           sabre::MQTTQoS::FIRE_AND_FORGET,
                           sabre::MQTTRetain::DONT_RETAIN};
    client.process_received(event);

    ASSERT_TRUE(called);
}

TEST(MQTTClient, Connect)
{
    MQTTClient client;
    client.connect("broker.hivemq.com", "test_client", "user", "pass");
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_init"));
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_register_event"));
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_start"));
}

TEST(MQTTClient, Disconnect)
{
    MQTTClient client;
    client.connect("broker.hivemq.com", "test_client", "user", "pass");
    client.disconnect();
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_disconnect"));
}

TEST(MQTTClient, Publish)
{
    MQTTClient client;
    client.connect("broker.hivemq.com", "test_client", "user", "pass");
    client.publish("test/topic", "Hello, MQTT!", sabre::MQTTQoS::AT_LEAST_ONCE,
                   sabre::MQTTRetain::RETAIN);
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_publish"));
    ASSERT_EQ(mockoc.last_call_for_function("esp_mqtt_client_publish").args[1],
              "test/topic");
    ASSERT_EQ(mockoc.last_call_for_function("esp_mqtt_client_publish").args[2],
              "Hello, MQTT!");
    ASSERT_EQ(mockoc.last_call_for_function("esp_mqtt_client_publish").args[4],
              "1");
}

TEST(MQTTClient, PublishWithUndefinedQoSAndRetain)
{
    MQTTClient client;
    client.connect("broker.hivemq.com", "test_client", "user", "pass");
    client.publish("test/topic", "Hello, MQTT!", sabre::MQTTQoS::UNDEFINED,
                   sabre::MQTTRetain::UNDEFINED);
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_publish"));
    ASSERT_EQ(mockoc.last_call_for_function("esp_mqtt_client_publish").args[4],
              "0");
    ASSERT_EQ(mockoc.last_call_for_function("esp_mqtt_client_publish").args[5],
              "0");
}

TEST(MQTTClient, IsStoppedInDestructor)
{
    {
        MQTTClient client;
        client.connect("broker.hivemq.com", "test_client", "user", "pass");
    }
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_stop"));
    ASSERT_TRUE(mockoc.was_called("esp_mqtt_client_destroy"));
}