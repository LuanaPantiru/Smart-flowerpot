#ifndef SMART_POD_APP_HTTP_HANDLER_H
#define SMART_POD_APP_HTTP_HANDLER_H

#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;

/** This is the main handler class for HTTP protocol.
 * Here all endpoints will be defined. */
class AppHttpHandler {
    private:
        std::shared_ptr<Http::Endpoint> httpServer;
        Rest::Router router;

    public:
        explicit AppHttpHandler(Address address);
        void init(size_t threadsNumber = 2);
        void start();
        void shutdown();

    private:
        /** Here all routes must be set up. */
        void setupRoutes();

        void setFlowerEnvironment(const Rest::Request& request, Http::ResponseWriter response);
        void getSongs(const Rest::Request& request, Http::ResponseWriter response);
        void playMusic(const Rest::Request& request, Http::ResponseWriter response);
        void stopMusic(const Rest::Request& request, Http::ResponseWriter response);

        /** Some general status about running features and mqtt clients */
        void SmartPotStatus(const Rest::Request& request, Http::ResponseWriter response);

        /** For a controlled app close */
        void closeSmartPot(const Rest::Request& request, Http::ResponseWriter response);
};


#endif //SMART_POD_APP_HTTP_HANDLER_H
