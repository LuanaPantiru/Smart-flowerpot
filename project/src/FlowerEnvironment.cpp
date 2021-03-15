#include "include/FlowerEnvironment.h"
#include "include/AppHardwareHandler.h"
#include "include/NotificationCenter.h"
#include <unistd.h>

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

void FlowerEnvironment::startHealthMonitor() const {
    while (environmentIsSet){

        float currentHumidity = AppHardwareHandler::getInstance()->getTemperatureSensor();
        if(FlowerEnvironment::getInstance()->isGoodTemperature(currentHumidity)){
            string message = "Value for humidity [" + to_string(currentHumidity) + "] in not in interval [" +
                             to_string(FlowerEnvironment::getInstance()->getHumidity().first) + " , " +
                             to_string(FlowerEnvironment::getInstance()->getHumidity().second) + "]";

            NotificationCenter::getInstance()->addHealthMonitorNotification(
                    make_tuple("Not good humidity", message, NotificationCenter::getCurrentTime()));
        }

        // sleep for 5 sec
        usleep(5000);
    }
}





