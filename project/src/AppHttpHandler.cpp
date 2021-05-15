#include "include/AppHttpHandler.h"
#include "include/SmartPot.h"
#include "include/AppHardwareHandler.h"
#include "include/MqttClientHandler.h"

AppHttpHandler::AppHttpHandler(Address address): httpServer(std::make_shared<Http::Endpoint>(address)){}

void AppHttpHandler::init(size_t threadsNumber) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(threadsNumber));
    httpServer->init(opts);
    setupRoutes();
}

void AppHttpHandler::start() {
    httpServer->setHandler(router.handler());
    httpServer->serve();
}

void AppHttpHandler::shutdown() {
    std::cout << std::endl;
    std::cout << "[PISTACHE-HTTP] Shutting down HTTP server" << std::endl;
    httpServer->shutdown();
    std::cout << "[PISTACHE-HTTP] HTTP server is stopped" << std::endl;
}

void AppHttpHandler::setupRoutes(){
    using namespace Pistache::Rest;

    // first input buffer
    Routes::Post(router, "/api/setFlowerEnvironment",
                 Routes::bind(&AppHttpHandler::setFlowerEnvironment, this));

    // this is a stateful functionality
    Routes::Post(router, "/api/resetFlowerEnvironment",
                 Routes::bind(&AppHttpHandler::resetFlowerEnvironment,this));

    // second input buffer
    // music feature
    Routes::Get(router, "/api/songs",
                 Routes::bind(&AppHttpHandler::getSongs, this));
    Routes::Post(router, "/api/playSong/:songId",
                 Routes::bind(&AppHttpHandler::playMusic, this));
    Routes::Post(router, "/api/stopMusic",
                 Routes::bind(&AppHttpHandler::stopMusic, this));

    //stateful functionality
    Routes::Post(router, "/api/setDisplayColor/:colorCode",
                 Routes::bind(&AppHttpHandler::setDisplayColor, this));

    // other routes
    Routes::Get(router, "/api/status",
                 Routes::bind(&AppHttpHandler::SmartPotStatus, this));
    Routes::Post(router, "/api/close",
                 Routes::bind(&AppHttpHandler::closeSmartPot, this));
}

void AppHttpHandler::setFlowerEnvironment(const Rest::Request& request, Http::ResponseWriter response){

    using namespace nlohmann;

    //Evitam lansarea mai multor thread-uri de monitorizare
    if(SmartPot::getInstance()->isEnvironmentSet()){
        response.send(Http::Code::Ok, "Ghiveciul este deja configurat!");
        return;
    }

    auto jsonReceived = json::parse(request.body());

    //Citim inputul de configurare
    SmartPot::getInstance()->setFlowerEnvironment(jsonReceived,false);

    //Pornim monitorizarea plantei
    SmartPot::getInstance()->startMonitorLoop();

    //Intoarcem configuratia citita ca raspuns
    auto const json_response = SmartPot::getInstance()->exportConfigurationToJson();
    response.send(Http::Code::Ok, to_string(json_response));
}

void AppHttpHandler::resetFlowerEnvironment(const Rest::Request &request, Http::ResponseWriter response) {
    if(!SmartPot::getInstance()->isEnvironmentSet()){
        response.send(Http::Code::Ok, "Smart-pot is not configured. Nothing to reset!!");
        return;
    }
    auto jsonReceived = nlohmann::json::parse(request.body());
    SmartPot::getInstance()->setFlowerEnvironment(jsonReceived,true);
    auto const json_response = SmartPot::getInstance()->exportConfigurationToJson();
    response.send(Http::Code::Ok, to_string(json_response));
}

void AppHttpHandler::getSongs(const Rest::Request &request, Http::ResponseWriter response) {
    // if environment is not set no feature will be available
    if(!SmartPot::getInstance()->isEnvironmentSet()){
        response.send(Http::Code::Ok, "Pot is not configured!");
        return;
    }

    response.send(Http::Code::Ok, to_string(AppHardwareHandler::getInstance()->exportSongsToJson()));
}

void AppHttpHandler::playMusic(const Rest::Request& request, Http::ResponseWriter response){
    // if environment is not set no feature will be available
    if(!SmartPot::getInstance()->isEnvironmentSet()){
        response.send(Http::Code::Ok, "Pot is not configured!");
        return;
    }

    auto songId = request.param(":songId").as<unsigned int>();
    SmartPot::getInstance()->playMusic(songId);
    response.send(Http::Code::Ok, "Song [" + to_string(songId) + "] started");
}

void AppHttpHandler::stopMusic(const Rest::Request &request, Http::ResponseWriter response) {
    // if environment is not set no feature will be available
    if (!SmartPot::getInstance()->isEnvironmentSet()) {
        response.send(Http::Code::Ok, "Pot is not configured!");
        return;
    }

    SmartPot::getInstance()->stopMusicPlayFeature();
    response.send(Http::Code::Ok, "Music stopped");
}

void AppHttpHandler::setDisplayColor(const Rest::Request& request, Http::ResponseWriter response){
    // if environment is not set no feature will be available
    if(!SmartPot::getInstance()->isEnvironmentSet()){
        response.send(Http::Code::Ok, "Pot is not configured!");
        return;
    }

    auto displayColorCode = request.param(":colorCode").as<int>();
    SmartPot::getInstance()->setDisplayColorCode(displayColorCode);
    response.send(Http::Code::Ok, "Display color is set to [" +
        SmartPot::getInstance()->getDisplayColor() + "] with code [" + to_string(displayColorCode) + "]");
}

void AppHttpHandler::SmartPotStatus(const Rest::Request &request, Http::ResponseWriter response) {
    nlohmann::json jsonResponse;
    jsonResponse["features"]["monitor_loop_is_running"] = SmartPot::getInstance()->isEnvironmentSet();
    jsonResponse["features"]["music_feature_is_running"] = SmartPot::getInstance()->isMusicPlay();
    jsonResponse["subscribers"]["water_subscriber_is_running"] = MqttClientHandler::isSubscriberRunning(WATER_SUBSCRIBER);
    jsonResponse["subscribers"]["additional_info_subscriber_is_running"] = MqttClientHandler::isSubscriberRunning(ADDITIONAL_INFO_SUBSCRIBER);
    jsonResponse["publishers"]["water_publisher_is_running"] = MqttClientHandler::isPublisherRunning(WATER_PUBLISHER);
    jsonResponse["publishers"]["display_publisher_is_running"] = MqttClientHandler::isPublisherRunning(DISPLAY_PUBLISHER);

    if(jsonResponse["features"]["monitor_loop_is_running"] == true){
        jsonResponse["features"]["flower_environment"] = SmartPot::getInstance()->exportConfigurationToJson();
    }

    response.send(Http::Code::Ok, to_string(jsonResponse));
}

void AppHttpHandler::closeSmartPot(const Rest::Request &request, Http::ResponseWriter response) {
    nlohmann::json jsonResponse;
    jsonResponse["_info"] = "SmartPot closed";

    // close all features
    SmartPot::getInstance()->stopMonitorLoop();
    SmartPot::getInstance()->stopMusicPlayFeature();

    // close MQTT clients
    unsigned int timeout = 2;
    MqttClientHandler::stopSubscriber(WATER_SUBSCRIBER);
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
    MqttClientHandler::stopSubscriber(ADDITIONAL_INFO_SUBSCRIBER);
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
    MqttClientHandler::stopPublisher(WATER_PUBLISHER);
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
    MqttClientHandler::stopPublisher(DISPLAY_PUBLISHER);

    // shut down HTTP httpServer also
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
    shutdown();
}


