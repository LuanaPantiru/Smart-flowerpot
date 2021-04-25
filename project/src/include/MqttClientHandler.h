#ifndef SMART_POT_MQTT_CLIENT_HANDLER_H
#define SMART_POT_MQTT_CLIENT_HANDLER_H

/** Check starting code here https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/samples/async_subscribe.cpp */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <utility>
#include <atomic>
#include "mqtt/async_client.h"

#define MQTT_SUBSCRIBER "[MQTT_SUBSCRIBER] "
#define MQTT_PUBLISHER "[MQTT_PUBLISHER] "
#define SERVER_ADDRESS "tcp://localhost:1883"
#define CLIENT_ID_SUBSCRIBER "smart-pod-subscriber"
#define CLIENT_ID_PUBLISHER "smart-pod-publisher"
#define SUBSCRIBING_TOPIC "test-topic"
#define PUBLISHING_TOPIC "test-topic-publishing"
#define PERSIST_DIR "./output/persist"
#define LWT_PAYLOAD "Last will and testament."

const int QOS = 2;
const int NR_RETRY_ATTEMPTS = 5;

class MqttClientHandler {
    public:
        static void startPublisher();
        static void stopPublisher();
        static void publishMessage(const std::string& message);

        static void startSubscriber();
        static void stopSubscriber();

    private:
        static std::atomic<bool> subscriberIsRunning;
        static std::atomic<bool> publisherIsRunning;
        static mqtt::async_client* publisherAsyncClient;

        /** Callbacks for the success or failures of requested actions, which can be used to initiate further action. */
        class MqttSubscriberActionListener : public virtual mqtt::iaction_listener {
            private:
                std::string listenerName;
                void on_failure(const mqtt::token& tok) override;
                void on_success(const mqtt::token& tok) override;

            public:
                explicit MqttSubscriberActionListener(std::string name) : listenerName(std::move(name)){};
        };

        /**
        * Local callback & listener class for use with the client connection.
        * This is primarily intended to receive messages, but it will also monitor
        * the connection to the broker. If the connection is lost, it will attempt
        * to restore the connection and re-subscribe to the topic.
        */
        class MqttSubscriberCallback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
            private:
                int nrRetry;                                        // Counter for the number of connection retries
                mqtt::async_client& asyncClient;                    // The MQTT client
                mqtt::connect_options& connOpts;                    // Options to use if we need to reconnect
                MqttSubscriberActionListener mqttActionListener;    // An action listener to display the result of actions.

                // This demonstrates manually reconnecting to the broker by calling
                // connect() again. This is a possibility for an application that keeps
                // a copy of it's original connect_options, or if the app wants to
                // reconnect with different options.
                // Another way this can be done manually, if using the same options, is
                // to just call the async_client::reconnect() method.
                void reconnect();

                // Re-connection failure
                void on_failure(const mqtt::token& tok) override;

                // (Re)connection success
                // Either this or connected() can be used for callbacks.
                void on_success(const mqtt::token& tok) override;

                // (Re)connection success
                void connected(const std::string& cause) override;

                // Callback for when the connection is lost.
                // This will initiate the attempt to manually reconnect.
                void connection_lost(const std::string& cause) override;

                // Callback for when a message arrives.
                void message_arrived(mqtt::const_message_ptr msg) override;

                void delivery_complete(mqtt::delivery_token_ptr token) override;

            public:
                explicit MqttSubscriberCallback(mqtt::async_client& asyncClient, mqtt::connect_options& connOpts)
                        : nrRetry(0), asyncClient(asyncClient), connOpts(connOpts), mqttActionListener("Subscription") {};
            };







        /** Callbacks for the success or failures of requested actions, which can be used to initiate further action. */
        class MqttPublisherActionListener : public virtual mqtt::iaction_listener {
            private:
                std::string listenerName;
                void on_failure(const mqtt::token& tok) override;
                void on_success(const mqtt::token& tok) override;

            public:
                explicit MqttPublisherActionListener(std::string name) : listenerName(std::move(name)){};
        };

        class MqttPublisherCallback : public virtual mqtt::callback {
            public:
                void connection_lost(const std::string& cause) override;
                void delivery_complete(mqtt::delivery_token_ptr tok) override;
        };
};


#endif //SMART_POT_MQTT_CLIENT_HANDLER_H
