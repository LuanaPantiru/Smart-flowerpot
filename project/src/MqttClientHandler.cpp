#include "include/MqttClientHandler.h"


/** =================================================================================================================
 *                                              MQTT HANDLER
 * =================================================================================================================*/
std::atomic<bool> MqttClientHandler::waterSubscriberIsRunning = false;
std::atomic<bool> MqttClientHandler::additionalInfoSubscriberIsRunning = false;
std::atomic<bool> MqttClientHandler::waterPublisherIsRunning = false;
std::atomic<bool> MqttClientHandler::displayPublisherIsRunning = false;
mqtt::async_client* MqttClientHandler::waterPublisherClient = nullptr;
mqtt::async_client* MqttClientHandler::displayPublisherClient = nullptr;


/** =================================================================================================================
 *                                                SUBSCRIBER
 * =================================================================================================================*/

/* ------------------------------------------------ CALLBACK ------------------------------------------------------- */

void MqttClientHandler::MqttSubscriberCallback::reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        std::cout << MQTT_SUBSCRIBER << "ClientId [" << clientId << "] try to reconnect at topic ["
                  << subscribedTopic << "]" << std::endl;
        asyncClient.connect(connOpts, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << "ClientId [" << clientId << "] Error: " << exc.what() << std::endl;
        exit(1);
    }
}

void MqttClientHandler::MqttSubscriberCallback::on_failure(const mqtt::token &tok) {
    std::cout << MQTT_SUBSCRIBER << "ClientId [" << clientId << "] connection attempt failed at topic ["
              << subscribedTopic << "]";
    if (tok.get_message_id() != 0) {
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
    if (++nrRetry > NR_RETRY_ATTEMPTS) {
        exit(1);
    }
    reconnect();
}

void MqttClientHandler::MqttSubscriberCallback::on_success(const mqtt::token &tok) {
    auto top = tok.get_topics();
    if (top && !top->empty()) {
        std::cout << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId << "] subscribed successfully"
                  << " for token topic: [" << (*top)[0] << "]" << std::endl;
    }
}

void MqttClientHandler::MqttSubscriberCallback::connected(const std::string &cause) {
    std::cout << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId << "] connected successfully" << std::endl;;
    std::cout << MQTT_SUBSCRIBER << "Subscribing to topic [" << subscribedTopic << "] for clientId ["
              << clientId << "] using QoS [" << QOS << "]" << std::endl;

    asyncClient.subscribe(subscribedTopic, QOS, nullptr, *this);
}

void MqttClientHandler::MqttSubscriberCallback::connection_lost(const std::string &cause) {
    std::cout << MQTT_SUBSCRIBER << "Connection lost for subscriber with clientId [" << clientId << "]" << std::endl;
    if (!cause.empty()) {
        std::cout << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId << "] connection lost cause: " << cause << std::endl;
    }
    std::cout << MQTT_SUBSCRIBER << "Reconnecting subscriber with clientId [" << clientId << "] ..." << std::endl;
    nrRetry = 0;
    reconnect();
}

void MqttClientHandler::MqttSubscriberCallback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << std::endl;
    std::cout << MQTT_SUBSCRIBER << "Message arrived" << std::endl;
    std::cout << MQTT_SUBSCRIBER << "  --> topic: [" << msg->get_topic() << "]" << std::endl;
    std::cout << MQTT_SUBSCRIBER << "  --> payload: [" << msg->to_string() << "]" << std::endl;
    std::cout << std::endl;

    if(msg->to_string() == "quit-subscriber"){
        if(clientId == CLIENT_ID_WATER_SUBSCRIBER){
            MqttClientHandler::stopSubscriber(WATER_SUBSCRIBER);
            return;
        }
        if(clientId == CLIENT_ID_ADDITIONAL_INFO_SUBSCRIBER){
            MqttClientHandler::stopSubscriber(ADDITIONAL_INFO_SUBSCRIBER);
            return;
        }
        return;
    }

    if(msg->to_string() == "quit-publisher-1") {
        MqttClientHandler::stopPublisher(WATER_PUBLISHER);
        return;
    }

    if(msg->to_string() == "quit-publisher-2") {
        MqttClientHandler::stopPublisher(DISPLAY_PUBLISHER);
        return;
    }
}

void MqttClientHandler::MqttSubscriberCallback::delivery_complete(mqtt::delivery_token_ptr token) {
    std::cout << std::endl;
    std::cout << MQTT_SUBSCRIBER << "Delivery complete for [" << token->get_message() << "]" << std::endl;
    std::cout << std::endl;
}


/* --------------------------------------- HANDLER FOR SUBSCRIBER ----------------------------------------------- */

void MqttClientHandler::startSubscriber(int subscriberId) {
    std::cout << std::endl;
    std::string topic;
    std::string clientId;
    switch (subscriberId) {
        case WATER_SUBSCRIBER:
            if(waterSubscriberIsRunning.load()){
                std::cerr << MQTT_SUBSCRIBER << " SubscriberId [" << subscriberId << "] already running" << std::endl;
                return;
            }
            topic = WATER_SUBSCRIBER_TOPIC;
            clientId = CLIENT_ID_WATER_SUBSCRIBER;
            break;
        case ADDITIONAL_INFO_SUBSCRIBER:
            if(additionalInfoSubscriberIsRunning.load()){
                std::cerr << MQTT_SUBSCRIBER << " SubscriberId [" << subscriberId << "] already running" << std::endl;
                return;
            }
            topic = ADDITIONAL_INFO_SUBSCRIBER_TOPIC;
            clientId = CLIENT_ID_ADDITIONAL_INFO_SUBSCRIBER;
            break;
        default:
            std::cerr << MQTT_SUBSCRIBER << " SubscriberId [" << subscriberId << "] is not correct" << std::endl;
            return;
    }

    // A subscriber often wants the server to remember its messages when its
    // disconnected. In that case, it needs a unique ClientID and a
    // non-clean session.
    mqtt::async_client client(MQTT_BROKER_SERVER_ADDRESS, clientId);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(false);

    // Install the callback(s) before connecting.
    MqttSubscriberCallback mqttSubscriberCallback(client, connOpts, topic, clientId);
    client.set_callback(mqttSubscriberCallback);

    // Start the connection.
    // When completed, the callback will subscribe to topic.
    try {
        std::cout << MQTT_SUBSCRIBER << "Starting subscriber with clientId [" << clientId << "] ..." << std::endl;
        client.connect(connOpts, nullptr, mqttSubscriberCallback);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId
                  << "] ERROR: Unable to connect to MQTT server: [" << MQTT_BROKER_SERVER_ADDRESS << "]" << exc << std::endl;
        return;
    }
    std::cout << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId << "] started" << std::endl;

    // set busy waiting
    if(subscriberId == WATER_SUBSCRIBER){
        waterSubscriberIsRunning.store(true);
        while (waterSubscriberIsRunning.load());
    }

    if(subscriberId == ADDITIONAL_INFO_SUBSCRIBER){
        additionalInfoSubscriberIsRunning.store(true);
        while (additionalInfoSubscriberIsRunning.load());
    }

    // Disconnect
    try {
        std::cout << MQTT_SUBSCRIBER << "Disconnecting subscriber with clientId [" << clientId << "] ..." << std::endl;
        client.disconnect()->wait();
        std::cout << MQTT_SUBSCRIBER << "Subscriber with clientId [" << clientId << "] disconnected" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_SUBSCRIBER << "Disconnecting error for subscriber with clientId [" << clientId << "]" << exc << std::endl;
    }

}

void MqttClientHandler::stopSubscriber(int subscriberId) {
    if(subscriberId == WATER_SUBSCRIBER){
        waterSubscriberIsRunning.store(false);
    }
    if(subscriberId == ADDITIONAL_INFO_SUBSCRIBER){
        additionalInfoSubscriberIsRunning.store(false);
    }
}




/** =================================================================================================================
 *                                                   PUBLISHER
 * =================================================================================================================*/

/* ------------------------------------------------ CALLBACK ------------------------------------------------------- */

void MqttClientHandler::MqttPublisherCallback::connection_lost(const std::string &cause) {
    std::cout << MQTT_PUBLISHER << "ClientId [" << clientId << "] Connection lost" << std::endl;
    if (!cause.empty()) {
        std::cout << MQTT_PUBLISHER << "ClientId [" << clientId << "] Connection lost cause: " << cause << std::endl;
    }
}

void MqttClientHandler::MqttPublisherCallback::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::cout << MQTT_PUBLISHER << "ClientId [" << clientId << "] Delivery complete for token: "
              << (tok ? tok->get_message_id() : -1) << std::endl;
}



/* ---------------------------------------- HANDLER FOR PUBLISHER ------------------------------------------------ */

void MqttClientHandler::startPublisher(int publisherId) {
    std::string topic;
    std::string clientId;
    switch (publisherId) {
        case WATER_PUBLISHER:
            if(waterPublisherIsRunning.load()){
                std::cerr << MQTT_PUBLISHER << "Publisher with clientId [" << clientId << "] already running" << std::endl;
                return;
            }
            topic = WATER_PUBLISHER_TOPIC;
            clientId = CLIENT_ID_WATER_PUBLISHER;
            break;
        case DISPLAY_PUBLISHER:
            if(displayPublisherIsRunning.load()){
                std::cerr << MQTT_PUBLISHER << "Publisher with clientId [" << clientId << "] already running" << std::endl;
                return;
            }
            topic = DISPLAY_PUBLISHER_TOPIC;
            clientId = CLIENT_ID_DISPLAY_PUBLISHER;
            break;
        default:
            std::cerr << MQTT_PUBLISHER << "PublisherId [" << publisherId << "] is not correct" << std::endl;
            return;
    }

    std::cout << "\n" << MQTT_PUBLISHER << "Starting publisher with clientId [" << clientId << "] for topic ["
              << topic << "] ..." << std::endl;
    auto* client = new mqtt::async_client(MQTT_BROKER_SERVER_ADDRESS, clientId);

    MqttPublisherCallback mqttPublisherCallback(clientId);
    client->set_callback(mqttPublisherCallback);

    auto connOpts = mqtt::connect_options_builder()
            .clean_session()
            .will(mqtt::message(topic, MQTT_LWT_PAYLOAD, strlen(MQTT_LWT_PAYLOAD)))
            .finalize();

    std::cout << MQTT_PUBLISHER << "Publisher with clientId [" << clientId << "] started" << std::endl;
    try {
        std::cout << MQTT_PUBLISHER << "Connecting publisher with clientId [" << clientId << "] to broker..." << std::endl;
        mqtt::token_ptr connToken = client->connect(connOpts);
        std::cout << MQTT_PUBLISHER << "Publisher with clientId [" << clientId << "] is waiting for the connection..." << std::endl;
        connToken->wait();
        std::cout << MQTT_PUBLISHER << "Publisher with clientId [" << clientId << "] connected to broker" << std::endl;

        if(publisherId == WATER_PUBLISHER){
            waterPublisherClient = client;
        }
        if(publisherId == DISPLAY_PUBLISHER){
            displayPublisherClient = client;
        }
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
        delete client;
        return;
    }

    // set busy waiting
    if(publisherId == WATER_PUBLISHER){
        waterPublisherIsRunning.store(true);
        while (waterPublisherIsRunning.load());
    }
    if(publisherId == DISPLAY_PUBLISHER){
        displayPublisherIsRunning.store(true);
        while (displayPublisherIsRunning.load());
    }


    try {
        // Disconnect
        std::cout << MQTT_PUBLISHER << "Disconnecting publisher with clientId [" << clientId << "] from broker..." << std::endl;
        client->disconnect()->wait();
        std::cout << MQTT_PUBLISHER << "Publisher disconnected with clientId [" << clientId << "] from broker" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
    }

    delete client;
    if(publisherId == WATER_PUBLISHER){
        waterPublisherClient = nullptr;
    }

    if(publisherId == DISPLAY_PUBLISHER){
        displayPublisherClient = nullptr;
    }
}

void MqttClientHandler::stopPublisher(int publisherId) {
    if(publisherId == WATER_PUBLISHER){
        waterPublisherIsRunning.store(false);
    }

    if(publisherId == DISPLAY_PUBLISHER){
        displayPublisherIsRunning.store(false);
    }
}

void MqttClientHandler::publishMessage(int publisherId, const std::string& message) {

    try {
        std::string topic;
        mqtt::async_client* client = nullptr;
        switch (publisherId) {
            case WATER_PUBLISHER:
                if(!waterPublisherIsRunning.load()){
                    std::cerr << MQTT_PUBLISHER << "Publisher with clientId [" << CLIENT_ID_WATER_PUBLISHER
                              << "] not running" << std::endl;
                    return;
                }
                client = waterPublisherClient;
                topic = WATER_PUBLISHER_TOPIC;
                break;
            case DISPLAY_PUBLISHER:
                if(!displayPublisherIsRunning.load()){
                    std::cerr << MQTT_PUBLISHER << "Publisher with clientId  [" << CLIENT_ID_DISPLAY_PUBLISHER
                              << "] not running" << std::endl;
                    return;
                }
                client = displayPublisherClient;
                topic = DISPLAY_PUBLISHER_TOPIC;
                break;
            default:
                std::cerr << MQTT_PUBLISHER << "PublisherId [" << publisherId << "] is not correct" << std::endl;
                return;
        }

        if(client == nullptr){
            std::cerr << MQTT_PUBLISHER << "Client is null on [publishMessage]" << std::endl;
            return;
        }

        std::cout << std::endl;
        std::cout << MQTT_PUBLISHER << "Publishing message [" << message << "] on topic [" << topic << "]" << std::endl;
        mqtt::message_ptr pubMessage = mqtt::make_message(topic, message);
        pubMessage->set_qos(QOS);
        client->publish(pubMessage)->wait_for(std::chrono::seconds(PUBLISHING_TIMEOUT));
        std::cout << MQTT_PUBLISHER << "Message [" << message << "] sent" << std::endl;
        std::cout << std::endl;

        // Double check that there are no pending tokens
        auto tokens = client->get_pending_delivery_tokens();
        if (!tokens.empty()) {
            std::cout << MQTT_PUBLISHER << "Error: There are pending delivery tokens!" << std::endl;
        }

    }
    catch (const mqtt::exception& exc) {
        std::cerr << MQTT_PUBLISHER << exc.what() << std::endl;
    }
}




