#include "include/FlowerEnvironment.h"
#include "include/AppHardwareHandler.h"
#include "include/NotificationCenter.h"
#include <unistd.h>
#include <thread>
#include <iostream>
#include <fstream>

FlowerEnvironment *FlowerEnvironment::instance = nullptr;

FlowerEnvironment *FlowerEnvironment::getInstance() {
    if (!instance) {
        instance = new FlowerEnvironment();
    }
    return instance;
}

bool FlowerEnvironment::isGoodTemperature(float currentTemperature) const {
    //Daca nu e setat intervalul, nu monitorizam. Presupunem ca rezultatul este ok.
    if (!get<0>(temperature)) return true;
    return get<1>(temperature) <= currentTemperature && currentTemperature <= get<2>(temperature);
}

bool FlowerEnvironment::isGoodHumidity(float currentHumidity) const {
    //Daca nu e setat intervalul, nu monitorizam. Presupunem ca rezultatul este ok.
    if (!get<0>(airHumidity)) return true;
    return get<1>(airHumidity) <= currentHumidity && currentHumidity <= get<2>(airHumidity);
}

nlohmann::json FlowerEnvironment::exportConfigurationToJson() const {
    nlohmann::json export_json;

    export_json["flower_info"]["name"] = name;
    export_json["flower_info"]["species"] = species;

    export_json["flower_health"]["air"]["temperature"]["isSet"] = get<0>(temperature);
    export_json["flower_health"]["air"]["temperature"]["min"] = get<1>(temperature);
    export_json["flower_health"]["air"]["temperature"]["max"] = get<2>(temperature);

    export_json["flower_health"]["air"]["humidity"]["isSet"] = get<0>(airHumidity);
    export_json["flower_health"]["air"]["humidity"]["min"] = get<1>(airHumidity);
    export_json["flower_health"]["air"]["humidity"]["max"] = get<2>(airHumidity);

    export_json["flower_health"]["air"]["light_intensity"]["isSet"] = get<0>(lightIntensity);
    export_json["flower_health"]["air"]["light_intensity"]["min"] = get<1>(lightIntensity);
    export_json["flower_health"]["air"]["light_intensity"]["max"] = get<2>(lightIntensity);

    export_json["flower_health"]["soil"]["moisture"]["isSet"] = get<0>(soilMoisture);
    export_json["flower_health"]["soil"]["moisture"]["min"] = get<1>(soilMoisture);
    export_json["flower_health"]["soil"]["moisture"]["max"] = get<2>(soilMoisture);

    export_json["flower_health"]["soil"]["ph"]["isSet"] = get<0>(soilPh);
    export_json["flower_health"]["soil"]["ph"]["min"] = get<1>(soilPh);
    export_json["flower_health"]["soil"]["ph"]["max"] = get<2>(soilPh);

    export_json["flower_health"]["soil"]["N"]["isSet"] = get<0>(soilN);
    export_json["flower_health"]["soil"]["N"]["min"] = get<1>(soilN);
    export_json["flower_health"]["soil"]["N"]["max"] = get<2>(soilN);

    export_json["flower_health"]["soil"]["K"]["isSet"] = get<0>(soilK);
    export_json["flower_health"]["soil"]["K"]["min"] = get<1>(soilK);
    export_json["flower_health"]["soil"]["K"]["max"] = get<2>(soilK);

    export_json["flower_health"]["soil"]["S"]["isSet"] = get<0>(soilS);
    export_json["flower_health"]["soil"]["S"]["min"] = get<1>(soilS);
    export_json["flower_health"]["soil"]["S"]["max"] = get<2>(soilS);

    export_json["flower_health"]["soil"]["Mg"]["isSet"] = get<0>(soilMg);
    export_json["flower_health"]["soil"]["Mg"]["min"] = get<1>(soilMg);
    export_json["flower_health"]["soil"]["Mg"]["max"] = get<2>(soilMg);

    export_json["flower_health"]["soil"]["Fe"]["isSet"] = get<0>(soilFe);
    export_json["flower_health"]["soil"]["Fe"]["min"] = get<1>(soilFe);
    export_json["flower_health"]["soil"]["Fe"]["max"] = get<2>(soilFe);

    export_json["environmentIsSet"] = environmentIsSet;
    return export_json;
}



void FlowerEnvironment::startMonitorLoop() {

    //TODO: Curata cod-ul

    auto f = []() {
        ofstream file("output/monitor_logs.txt");
        file<<"INCEPUT!";
        file.flush();

        while (FlowerEnvironment::getInstance()->environmentIsSet){

            if(file.is_open())
            {
                file<<"thread!\n";
                file.flush();
            }
//            FlowerEnvironment::getInstance()->checkHealth();
            // sleep for 5 sec
            std::this_thread::sleep_for (std::chrono::seconds(5));
        }
    };

    monitorThread = std::thread(f);
}

void FlowerEnvironment::checkHealth() const {
//    float currentHumidity = AppHardwareHandler::getInstance()->getTemperatureSensor();
//    if(FlowerEnvironment::getInstance()->isGoodTemperature(currentHumidity)) {
//        string message = "Value for airHumidity [" + to_string(currentHumidity) + "] in not in interval [" +
//                         to_string(FlowerEnvironment::getInstance()->getHumidity().first) + " , " +
//                         to_string(FlowerEnvironment::getInstance()->getHumidity().second) + "]";
//
//        NotificationCenter::getInstance()->addHealthMonitorNotification(
//                make_tuple("Not good airHumidity", message, NotificationCenter::getCurrentTime()));
//    }
}

void FlowerEnvironment::parseEnvironmentInputSet(nlohmann::json jsonReceived) {

    name = jsonReceived["flower_info"]["name"];
    species = jsonReceived["flower_info"]["species"];

    get<0>(temperature) = jsonReceived["flower_health"]["air"]["temperature"]["isSet"];
    get<1>(temperature) = jsonReceived["flower_health"]["air"]["temperature"]["min"];
    get<2>(temperature) = jsonReceived["flower_health"]["air"]["temperature"]["max"];

    get<0>(airHumidity) = jsonReceived["flower_health"]["air"]["humidity"]["isSet"];
    get<1>(airHumidity) = jsonReceived["flower_health"]["air"]["humidity"]["min"];
    get<2>(airHumidity) = jsonReceived["flower_health"]["air"]["humidity"]["max"];

    get<0>(lightIntensity) = jsonReceived["flower_health"]["air"]["light_intensity"]["isSet"];
    get<1>(lightIntensity) = jsonReceived["flower_health"]["air"]["light_intensity"]["min"];
    get<2>(lightIntensity) = jsonReceived["flower_health"]["air"]["light_intensity"]["max"];

    get<0>(soilMoisture) = jsonReceived["flower_health"]["soil"]["moisture"]["isSet"];
    get<1>(soilMoisture) = jsonReceived["flower_health"]["soil"]["moisture"]["min"];
    get<2>(soilMoisture) = jsonReceived["flower_health"]["soil"]["moisture"]["max"];

    get<0>(soilPh) = jsonReceived["flower_health"]["soil"]["ph"]["isSet"];
    get<1>(soilPh) = jsonReceived["flower_health"]["soil"]["ph"]["min"];
    get<2>(soilPh) = jsonReceived["flower_health"]["soil"]["ph"]["max"];

    get<0>(soilN) = jsonReceived["flower_health"]["soil"]["N"]["isSet"];
    get<1>(soilN) = jsonReceived["flower_health"]["soil"]["N"]["min"];
    get<2>(soilN) = jsonReceived["flower_health"]["soil"]["N"]["max"];

    get<0>(soilK) = jsonReceived["flower_health"]["soil"]["K"]["isSet"];
    get<1>(soilK) = jsonReceived["flower_health"]["soil"]["K"]["min"];
    get<2>(soilK) = jsonReceived["flower_health"]["soil"]["K"]["max"];

    get<0>(soilS) = jsonReceived["flower_health"]["soil"]["S"]["isSet"];
    get<1>(soilS) = jsonReceived["flower_health"]["soil"]["S"]["min"];
    get<2>(soilS) = jsonReceived["flower_health"]["soil"]["S"]["max"];

    get<0>(soilMg) = jsonReceived["flower_health"]["soil"]["Mg"]["isSet"];
    get<1>(soilMg) = jsonReceived["flower_health"]["soil"]["Mg"]["min"];
    get<2>(soilMg) = jsonReceived["flower_health"]["soil"]["Mg"]["max"];

    get<0>(soilFe) = jsonReceived["flower_health"]["soil"]["Fe"]["isSet"];
    get<1>(soilFe) = jsonReceived["flower_health"]["soil"]["Fe"]["min"];
    get<2>(soilFe) = jsonReceived["flower_health"]["soil"]["Fe"]["max"];

    environmentIsSet = true;
}

bool FlowerEnvironment::isEnvironmentIsSet() const {
    return environmentIsSet;
}





