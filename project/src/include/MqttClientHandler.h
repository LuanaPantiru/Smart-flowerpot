#ifndef SMART_POT_MQTT_CLIENT_HANDLER_H
#define SMART_POT_MQTT_CLIENT_HANDLER_H

/** Check starting code here:
 *          - https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/samples/async_subscribe.cpp
 *          - https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/samples/async_publish.cpp
 * */

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

// for logs
#define MQTT_SUBSCRIBER "[MQTT_SUBSCRIBER] "
#define MQTT_PUBLISHER "[MQTT_PUBLISHER] "

// general info`s about MQTT
#define MQTT_BROKER_SERVER_ADDRESS "tcp://localhost:1883"
#define MQTT_LWT_PAYLOAD "Last will and testament"
#define QOS 2
#define NR_RETRY_ATTEMPTS 5
#define PUBLISHING_TIMEOUT 10

// subscribers info`s
#define WATER_SUBSCRIBER 1
#define ADDITIONAL_INFO_SUBSCRIBER 2
#define CLIENT_ID_WATER_SUBSCRIBER "smart-pod-water-subscriber"
#define CLIENT_ID_ADDITIONAL_INFO_SUBSCRIBER "smart-pod-additional-info-subscriber"
#define WATER_SUBSCRIBER_TOPIC "smart_pod/water"
#define ADDITIONAL_INFO_SUBSCRIBER_TOPIC "smart_pod/info"

// publishers info`s
#define WATER_PUBLISHER 3
#define DISPLAY_PUBLISHER 4
#define CLIENT_ID_WATER_PUBLISHER "smart-pod-water-publisher"
#define CLIENT_ID_DISPLAY_PUBLISHER "smart-pod-display-publisher"
#define WATER_PUBLISHER_TOPIC "smart_pod/water"
#define DISPLAY_PUBLISHER_TOPIC "smart_pod/display"

class MqttClientHandler {
    public:
        static void startPublisher(int publisherId);
        static void stopPublisher(int publisherId);
        static void publishMessage(int publisherId, const std::string& message);
        static void startSubscriber(int subscriberId);
        static void stopSubscriber(int subscriberId);

        [[nodiscard]] static bool isPublisherRunning(int publisherId) ;
        [[nodiscard]] static bool isSubscriberRunning(int subscriberId) ;

    private:
        static std::atomic<bool> waterSubscriberIsRunning;
        static std::atomic<bool> additionalInfoSubscriberIsRunning;
        static std::atomic<bool> waterPublisherIsRunning;
        static std::atomic<bool> displayPublisherIsRunning;
        static mqtt::async_client* waterPublisherClient;
        static mqtt::async_client* displayPublisherClient;

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
                std::string subscribedTopic;
                std::string clientId;

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
                explicit MqttSubscriberCallback(mqtt::async_client& asyncClient, mqtt::connect_options& connOpts,
                                                std::string topic, std::string _clientId) : nrRetry(0),
                                                asyncClient(asyncClient), connOpts(connOpts),
                                                subscribedTopic(std::move(topic)), clientId(std::move(_clientId)) {};
            };


        /** Callback for publisher */
        class MqttPublisherCallback : public virtual mqtt::callback {
            private:
                std::string clientId;
            public:
                void connection_lost(const std::string& cause) override;
                void delivery_complete(mqtt::delivery_token_ptr tok) override;
                explicit MqttPublisherCallback(std::string _clientId) : clientId(std::move(_clientId)) {};
        };
};


#endif //SMART_POT_MQTT_CLIENT_HANDLER_H
