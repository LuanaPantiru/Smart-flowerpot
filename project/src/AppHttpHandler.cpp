#include "include/AppHttpHandler.h"
#include "include/SmartPot.h"

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
    Routes::Post(router, "/api/waterFlower",
                 Routes::bind(&AppHttpHandler::waterFlower, this));
}

void AppHttpHandler::setFlowerEnvironment(const Rest::Request& request, Http::ResponseWriter response){

    using namespace nlohmann;

    //Evitam lansarea mai multor thread-uri de monitorizare
    if(SmartPot::getInstance()->isEnvironmentIsSet())
    {
        response.send(Http::Code::Ok, "Ghiveciul este deja configurat!");
        return;
    }

    auto jsonReceived = json::parse(request.body());

    //Citim inputul de configurare
    SmartPot::getInstance()->setFlowerEnvironment(jsonReceived);

    //Pornim monitorizarea plantei
    SmartPot::getInstance()->startMonitorLoop();

    //Intoarcem configuratia citita ca raspuns
    auto const json_response = SmartPot::getInstance()->exportConfigurationToJson();
    response.send(Http::Code::Ok, to_string(json_response));
}

void AppHttpHandler::addVoiceRecord(const Rest::Request& request, Http::ResponseWriter response){
    response.send(Http::Code::Ok, "Record was added.\n");
}

void AppHttpHandler::waterFlower(const Rest::Request& request, Http::ResponseWriter response) {

    auto jsonReceived = nlohmann::json::parse(request.body());
    float waterQuantity = jsonReceived["quantity"];
    SmartPot::getInstance()->waterFlower(waterQuantity);

    response.send(Http::Code::Ok, "Flower was watered!");
}
