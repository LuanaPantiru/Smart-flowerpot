#include <csignal>
#include <iomanip>
#include "include/app_config.h"
#include "include/AppHttpHandler.h"
#include "include/MqttClientHandler.h"


void launchPistacheServer(int argc, char *argv[]){
    std::cout << "\n[PISTACHE-HTTP] Starting Pistache HTTP Server..." << std::endl;

    // prepare HTTP Server
    // set default values
    Port port(SERVER_PORT);
    int threadsNumber = 2;
    if (argc >= 2) {
        port = static_cast<uint16_t>(std::stol(argv[1]));
        if (argc == 3) {
            threadsNumber = std::stoi(argv[2]);
        }
    }

    // launch HTTP server
    Address address(Ipv4::any(), port);
    std::cout << "[PISTACHE-HTTP] HTTP Server started on address [" << address.host() << "] and port ["
              << address.port() << "]\n";
    AppHttpHandler appHttpHandler(address);
    appHttpHandler.init(threadsNumber);
    appHttpHandler.start();

}


void launchMQTTClient() {
    std::cout << "\n[MQTT] Starting MQTT Clients..." << std::endl;

    std::thread subscriber(MqttClientHandler::startSubscriber);

    // sleep thread in order to show logs in order on console
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::thread publisher(MqttClientHandler::startPublisher);

    std::cout << "[MQTT] MQTT Clients started" << std::endl;

    subscriber.join();
    publisher.join();
}

// TODO: IMPORTANT .
//    At final, when binary will be released check if program will output infos correctly in the output files,
//     because in CLion a current directory must be set.


// TODO: check input arguments like server address, port or thread number
//  (first argument I think is always the program name)
int main(int argc, char *argv[]) {

    std::thread pistacheThread(launchPistacheServer,argc,argv);

    // sleep thread in order to show logs in order on console
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::thread mqttThread(launchMQTTClient);

    pistacheThread.join();
    mqttThread.join();

    // set signals for a gracefully shutdown of the server when no longer needed
    sigset_t signals;
    if (sigemptyset(&signals) != 0 || sigaddset(&signals, SIGTERM) != 0 || sigaddset(&signals, SIGINT) != 0 ||
        sigaddset(&signals, SIGHUP) != 0 || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0){
        perror("install signal handler failed");
        return 1;
    }

    return 0;
}


