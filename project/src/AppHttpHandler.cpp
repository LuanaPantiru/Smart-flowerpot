#include "include/AppHttpHandler.h"
#include "include/SmartPot.h"
#include "include/AppHardwareHandler.h"

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

    // first input buffer
    Routes::Post(router, "/api/setFlowerEnvironment",
                 Routes::bind(&AppHttpHandler::setFlowerEnvironment, this));

    // second input buffer
    // water flower feature
    Routes::Post(router, "/api/waterFlower",
                 Routes::bind(&AppHttpHandler::waterFlower, this));

    // music feature
    Routes::Get(router, "/api/songs",
                 Routes::bind(&AppHttpHandler::getSongs, this));
    Routes::Post(router, "/api/playSong/:songId",
                 Routes::bind(&AppHttpHandler::playMusic, this));
    Routes::Post(router, "/api/stopMusic",
                 Routes::bind(&AppHttpHandler::stopMusic, this));
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

void AppHttpHandler::getSongs(const Rest::Request &request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, to_string(AppHardwareHandler::getInstance()->exportSongsToJson()));
}

void AppHttpHandler::playMusic(const Rest::Request& request, Http::ResponseWriter response){
    auto songId = request.param(":songId").as<unsigned int>();
    SmartPot::getInstance()->playMusic(songId);
    response.send(Http::Code::Ok, "Song [" + to_string(songId) + "] started");
}

void AppHttpHandler::stopMusic(const Rest::Request &request, Http::ResponseWriter response) {
    SmartPot::getInstance()->stopMusicPlayFeature();
    response.send(Http::Code::Ok, "Music stopped");
}

void AppHttpHandler::waterFlower(const Rest::Request& request, Http::ResponseWriter response) {

    auto jsonReceived = nlohmann::json::parse(request.body());
    float waterQuantity = jsonReceived["quantity"];
    SmartPot::getInstance()->waterFlower(waterQuantity);

    response.send(Http::Code::Ok, "Flower was watered!");
}