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
    return temperature.first <= currentTemperature && currentTemperature <= temperature.second;
}

bool FlowerEnvironment::isGoodHumidity(float currentHumidity) const {
    return humidity.first <= currentHumidity && currentHumidity <= humidity.second;
}

void FlowerEnvironment::showEnvironment() {

}

void FlowerEnvironment::setName(const string &newName) {
    FlowerEnvironment::name = newName;
}

void FlowerEnvironment::setTemperature(const pair<float, float> &newTemperature) {
    FlowerEnvironment::temperature = newTemperature;
}

void FlowerEnvironment::setEnvironmentIsSet(bool isSet) {
    FlowerEnvironment::environmentIsSet = isSet;
}

const pair<float, float> &FlowerEnvironment::getHumidity() const {
    return humidity;
}

const string &FlowerEnvironment::getName() const {
    return name;
}

const pair<float, float> &FlowerEnvironment::getTemperature() const {
    return temperature;
}

nlohmann::json FlowerEnvironment::exportConfigurationToJson() const {
    nlohmann::json export_json;
    export_json["name"] = name;
    export_json["temperature"]["min"] = temperature.first;
    export_json["temperature"]["max"] = temperature.second;
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
    float currentHumidity = AppHardwareHandler::getInstance()->getTemperatureSensor();
    if(FlowerEnvironment::getInstance()->isGoodTemperature(currentHumidity)) {
        string message = "Value for humidity [" + to_string(currentHumidity) + "] in not in interval [" +
                         to_string(FlowerEnvironment::getInstance()->getHumidity().first) + " , " +
                         to_string(FlowerEnvironment::getInstance()->getHumidity().second) + "]";

        NotificationCenter::getInstance()->addHealthMonitorNotification(
                make_tuple("Not good humidity", message, NotificationCenter::getCurrentTime()));
    }
}





