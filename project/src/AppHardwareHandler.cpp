#include "include/AppHardwareHandler.h"

AppHardwareHandler *AppHardwareHandler::instance = nullptr;

AppHardwareHandler *AppHardwareHandler::getInstance() {
    if (!instance) {
        instance = new AppHardwareHandler();
    }
    return instance;
}

void AppHardwareHandler::loadSensorInfo() {

}

void AppHardwareHandler::changeLightMatrix() {

}




