#include <csignal>
#include <iomanip>
#include "include/app_config.h"
#include "include/AppHttpHandler.h"
#include "include/MqttClientHandler.h"

#define TIMEOUT 2

void launchPistacheServer(){
    std::cout << "\n[PISTACHE-HTTP] Starting Pistache HTTP Server..." << std::endl;

    // prepare HTTP Server
    // set default values
    Port port(SERVER_PORT);
    int threadsNumber = 2;

    // launch HTTP httpServer
    Address address(Ipv4::any(), port);
    std::cout << "[PISTACHE-HTTP] HTTP Server started on address [" << address.host() << "] and port ["
              << address.port() << "]\n";
    AppHttpHandler appHttpHandler(address);
    appHttpHandler.init(threadsNumber);
    appHttpHandler.start();

}


void launchMQTTClient() {
    std::cout << "\n[MQTT] Starting MQTT clients ..." << std::endl;
    std::thread waterSubscriber(MqttClientHandler::startSubscriber, WATER_SUBSCRIBER);
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT));
    std::thread additionalInfoSubscriber(MqttClientHandler::startSubscriber, ADDITIONAL_INFO_SUBSCRIBER);
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT));
    std::thread waterPublisher(MqttClientHandler::startPublisher, WATER_PUBLISHER);
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT));
    std::thread displayPublisher(MqttClientHandler::startPublisher, DISPLAY_PUBLISHER);
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT));
    std::cout << "\n[MQTT] MQTT clients started" << std::endl;

    waterSubscriber.join();
    additionalInfoSubscriber.join();
    waterPublisher.join();
    displayPublisher.join();
}

int main(int argc, char *argv[]) {

    std::thread pistacheThread(launchPistacheServer);
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT)); // sleep thread in order to show logs in order on console
    std::thread mqttThread(launchMQTTClient);

    // set signals for a gracefully shutdown of the httpServer when no longer needed
    sigset_t signals;
    if (sigemptyset(&signals) != 0 || sigaddset(&signals, SIGTERM) != 0 || sigaddset(&signals, SIGINT) != 0 ||
        sigaddset(&signals, SIGHUP) != 0 || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0){
        perror("install signal handler failed");
        return 1;
    }

    pistacheThread.join();
    mqttThread.join();

    return 0;
}


