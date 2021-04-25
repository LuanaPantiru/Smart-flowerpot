#include "include/MqttClientHandler.h"

// static values
std::atomic<bool> MqttClientHandler::subscriberIsRunning = false;
std::atomic<bool> MqttClientHandler::publisherIsRunning = false;
mqtt::async_client* MqttClientHandler::publisherAsyncClient = nullptr;

void MqttClientHandler::MqttSubscriberActionListener::on_failure(const mqtt::token &tok) {
    std::cout << MQTT_SUBSCRIBER << "Listener [" << listenerName << "] failure";
    if (tok.get_message_id() != 0) {
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
    std::cout << std::endl;
}

void MqttClientHandler::MqttSubscriberActionListener::on_success(const mqtt::token &tok) {
    std::cout << MQTT_SUBSCRIBER << "Listener [" << listenerName << "] success";
    if (tok.get_message_id() != 0) {
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
    auto top = tok.get_topics();
    if (top && !top->empty()) {
        std::cout << MQTT_SUBSCRIBER << "token topic: '" << (*top)[0] << std::endl;
    }
    std::cout << std::endl;
}

void MqttClientHandler::MqttSubscriberCallback::reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        asyncClient.connect(connOpts, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

void MqttClientHandler::MqttSubscriberCallback::on_failure(const mqtt::token &tok) {
    std::cout << MQTT_SUBSCRIBER << " Connection attempt failed" << std::endl;
    if (++nrRetry > NR_RETRY_ATTEMPTS) {
        exit(1);
    }
    reconnect();
}

void MqttClientHandler::MqttSubscriberCallback::on_success(const mqtt::token &tok) {

}

void MqttClientHandler::MqttSubscriberCallback::connected(const std::string &cause) {
    std::cout << MQTT_SUBSCRIBER << "Connection success" << std::endl;
    std::cout << MQTT_SUBSCRIBER << "Subscribing to topic [" << SUBSCRIBING_TOPIC << "] for client ["
              << CLIENT_ID_SUBSCRIBER << "] using QoS [" << QOS << "]" << std::endl;

    asyncClient.subscribe(SUBSCRIBING_TOPIC, QOS, nullptr, mqttActionListener);
}

void MqttClientHandler::MqttSubscriberCallback::connection_lost(const std::string &cause) {
    std::cout << MQTT_SUBSCRIBER << "Connection lost" << std::endl;
    if (!cause.empty()) {
        std::cout << "[SUBSCRIBER] connection lost cause: " << cause << std::endl;
    }
    std::cout << MQTT_SUBSCRIBER << " Reconnecting..." << std::endl;
    nrRetry = 0;
    reconnect();
}

void MqttClientHandler::MqttSubscriberCallback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << std::endl;
    std::cout << MQTT_SUBSCRIBER << "Message arrived" << std::endl;
    std::cout << MQTT_SUBSCRIBER << "  --> topic: [" << msg->get_topic() << "]" << std::endl;
    std::cout << MQTT_SUBSCRIBER << "  --> payload: [" << msg->to_string() << "]" << std::endl;
    std::cout << std::endl;

    if(msg->to_string() == "q"){
        subscriberIsRunning.store(false);
        return;
    }
}

void MqttClientHandler::MqttSubscriberCallback::delivery_complete(mqtt::delivery_token_ptr token) {

}


void MqttClientHandler::startSubscriber() {
    // A subscriber often wants the server to remember its messages when its
    // disconnected. In that case, it needs a unique ClientID and a
    // non-clean session.
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID_SUBSCRIBER);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(false);

    // Install the callback(s) before connecting.
    MqttSubscriberCallback mqttSubscriberCallback(client, connOpts);
    client.set_callback(mqttSubscriberCallback);

    // Start the connection.
    // When completed, the callback will subscribe to topic.
    try {
        std::cout << MQTT_SUBSCRIBER << "Starting subscriber..." << std::endl;
        client.connect(connOpts, nullptr, mqttSubscriberCallback);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << "ERROR: Unable to connect to MQTT server: '" << SERVER_ADDRESS << "'" << exc
                  << std::endl;
        return;
    }

    std::cout << MQTT_SUBSCRIBER << "Subscriber started" << std::endl;
    subscriberIsRunning.store(true);
    while (subscriberIsRunning.load());

    // Disconnect
    try {
        std::cout << MQTT_SUBSCRIBER << "Disconnecting subscriber..." << std::endl;
        client.disconnect()->wait();
        std::cout << MQTT_SUBSCRIBER << "Subscriber disconnected" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << exc << std::endl;
    }

}

void MqttClientHandler::stopSubscriber() {
    subscriberIsRunning.store(false);
}

void MqttClientHandler::MqttPublisherActionListener::on_failure(const mqtt::token &tok) {
    std::cout << MQTT_PUBLISHER << " Listener failure for token: " << tok.get_message_id() << std::endl;
}

void MqttClientHandler::MqttPublisherActionListener::on_success(const mqtt::token &tok) {
    std::cout << MQTT_PUBLISHER <<  "Listener success for token: " << tok.get_message_id() << std::endl;
}

void MqttClientHandler::MqttPublisherCallback::connection_lost(const std::string &cause) {
    std::cout << MQTT_PUBLISHER << " Connection lost" << std::endl;
    if (!cause.empty()) {
        std::cout << MQTT_PUBLISHER << " connection lost cause: " << cause << std::endl;
    }
}

void MqttClientHandler::MqttPublisherCallback::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::cout << MQTT_PUBLISHER << " Delivery complete for token: " << (tok ? tok->get_message_id() : -1) << std::endl;
}


void MqttClientHandler::startPublisher() {

    // A client that just publishes normally doesn't need a persistent
    // session or Client ID unless it's using persistence, then the local
    // library requires an ID to identify the persistence files.
    std::cout << MQTT_PUBLISHER << "Starting publisher..." << std::endl;
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID_PUBLISHER, PERSIST_DIR);

    // FIXME: Address of local variable may escape the function
    publisherAsyncClient = &client;

    MqttPublisherCallback mqttPublisherCallback;
    client.set_callback(mqttPublisherCallback);

    auto connOpts = mqtt::connect_options_builder()
            .clean_session()
            .will(mqtt::message(PUBLISHING_TOPIC, LWT_PAYLOAD, strlen(LWT_PAYLOAD)))
            .finalize();

    std::cout << MQTT_PUBLISHER << "Publisher started" << std::endl;
    try {
        std::cout << MQTT_PUBLISHER << "Connecting to broker..." << std::endl;
        mqtt::token_ptr connToken = client.connect(connOpts);
        std::cout << MQTT_PUBLISHER << "Waiting for the connection..." << std::endl;
        connToken->wait();
        std::cout << MQTT_PUBLISHER << "Publisher connected to broker" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
    }

    publisherIsRunning.store(true);
    while (publisherIsRunning.load());

    try {
        // Disconnect
        std::cout << MQTT_PUBLISHER << "Disconnecting publisher from broker..." << std::endl;
        client.disconnect()->wait();
        std::cout << MQTT_PUBLISHER << "Publisher disconnected from broker" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
    }

}

void MqttClientHandler::stopPublisher() {
    publisherIsRunning.store(false);
}

void MqttClientHandler::publishMessage(const std::string& message) {

    try {
        if(publisherAsyncClient == nullptr){
            std::cerr << MQTT_PUBLISHER << "publisherAsyncClient is null on [publishMessage]" << std::endl;
            return;
        }

        std::cout << std::endl;
        std::cout << MQTT_PUBLISHER << "Sending message [" << message << "]" << std::endl;
        MqttPublisherActionListener listener("Publisher-listener");
        mqtt::message_ptr pubMessage = mqtt::make_message(PUBLISHING_TOPIC, message);
        mqtt::delivery_token_ptr deliveryToken = publisherAsyncClient->publish(pubMessage, nullptr, listener);
        deliveryToken->wait();
        std::cout << MQTT_PUBLISHER << "Message [" << message << "] sent" << std::endl;
        std::cout << std::endl;

        // Double check that there are no pending tokens
        auto tokens = publisherAsyncClient->get_pending_delivery_tokens();
        if (!tokens.empty()) {
            std::cout << MQTT_PUBLISHER << "Error: There are pending delivery tokens!" << std::endl;
        }

    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
    }
}




