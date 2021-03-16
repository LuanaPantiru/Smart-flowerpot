#include <iomanip>
#include "include/app_config.h"
#include "include/AppHttpHandler.h"
#include "nlohmann/json.hpp"
#include "include/NotificationCenter.h"

// TODO: check input arguments like server address, port or thread number
//  (first argument I think is always the program name)
int main(int argc, char *argv[]) {

//     set default values
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
    std::cout << INFO_LABEL << "HTTP Server started on address [" << address.host() << "] and port ["
              << address.port() << "]\n";
    AppHttpHandler appHttpHandler(address);
    appHttpHandler.init(threadsNumber);
    appHttpHandler.start();

    return 0;
}


