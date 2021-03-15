#include "include/AppHttpHandler.h"
#include "include/FlowerEnvironment.h"
#include <nlohmann/json.hpp>

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

    using namespace nlohmann;

    auto jsonReceived = json::parse(request.body());
    FlowerEnvironment::getInstance()->setName(jsonReceived["name"]);
    FlowerEnvironment::getInstance()->setTemperature(make_pair(
            jsonReceived["temperature"]["min"], jsonReceived["temperature"]["max"]));
    FlowerEnvironment::getInstance()->setEnvironmentIsSet(true);

    //Pornim monitorizarea plantei
    FlowerEnvironment::getInstance()->startMonitorLoop();

    auto const json_response = FlowerEnvironment::getInstance()->exportConfigurationToJson();
    response.send(Http::Code::Ok, to_string(json_response));
}

void AppHttpHandler::addVoiceRecord(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Record was added.\n");
}
