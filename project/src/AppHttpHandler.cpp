#include "include/AppHttpHandler.h"
#include "include/FlowerEnvironment.h"

AppHttpHandler::AppHttpHandler(Address address): httpEndpoint(std::make_shared<Http::Endpoint>(address)){}

void AppHttpHandler::init(size_t threadsNumber) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(threadsNumber));
    httpEndpoint->init(opts);
    setupRoutes();
}

void AppHttpHandler::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void AppHttpHandler::setupRoutes(){
    using namespace Pistache::Rest;
    Routes::Post(router, "/api/setFlowerEnvironment",
                 Routes::bind(&AppHttpHandler::setFlowerEnvironment, this));
    Routes::Post(router, "/api/addVoiceRecord",
                 Routes::bind(&AppHttpHandler::addVoiceRecord, this));
}

void AppHttpHandler::setFlowerEnvironment(const Rest::Request& request, Http::ResponseWriter response){

    /*
    const auto xx = request.body();
    if (request.hasParam(":name")) {
        FlowerEnvironment::getInstance()->setName(request.param(":name").as<std::string>());
    }

    if (request.hasParam("name")) {
        FlowerEnvironment::getInstance()->setName(request.param(":name").as<std::string>());
    }

    if (request.query().has("temperature")) {
        const auto x = request.query().get("temperature");
        int a = 2;
    }

    FlowerEnvironment::getInstance()->setEnvironmentIsSet(true);
    */

    response.send(Http::Code::Ok, "Flower environment was set.\n");
}

void AppHttpHandler::addVoiceRecord(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Record was added.\n");
}
