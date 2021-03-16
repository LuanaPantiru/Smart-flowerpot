#include "include/AppHardwareHandler.h"
#include "include/app_config.h"

AppHardwareHandler *AppHardwareHandler::instance = nullptr;

AppHardwareHandler::AppHardwareHandler() {
    int matrixDimension = 5;

    // populate soil sensors matrix
    for(int i = 0; i < matrixDimension; i++){
        vector<SoilSensor> sensor(matrixDimension);
        soilSensorsMatrix.push_back(sensor);
    }

    // populate light matrix
    for(int i = 0; i < matrixDimension; i++){
        vector<Pixel> pixel(matrixDimension);
        lightMatrix.push_back(pixel);
    }
}

AppHardwareHandler *AppHardwareHandler::getInstance() {
    if (!instance) {
        instance = new AppHardwareHandler();
    }
    return instance;
}

void AppHardwareHandler::loadSensorInfo() {
    // TODO: must be implemented
}

void AppHardwareHandler::changeLightMatrix() {
    // TODO: must be implemented
}

float AppHardwareHandler::getAirTemperatureSensor() const {
    return airTemperatureSensor;
}

float AppHardwareHandler::getAirHumiditySensor() const {
    return airHumiditySensor;
}

float AppHardwareHandler::getLightSensor() const {
    return lightIntensitySensor;
}

vector<float> AppHardwareHandler::getSoilSpecificSensorValues(int sensorCode) const {
    vector<float> soilMoistureSensorsValues;
    for(const auto& sensors : soilSensorsMatrix){
        for(auto sensor : sensors){
            switch (sensorCode){
                case SOIL_MOISTURE_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilMoisture);
                    break;
                case SOIL_PH_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilPh);
                    break;
                case SOIL_N_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilN);
                    break;
                case SOIL_K_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilK);
                    break;
                case SOIL_S_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilS);
                    break;
                case SOIL_Mg_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilMg);
                    break;
                case SOIL_Fe_SENSOR:
                    soilMoistureSensorsValues.push_back(sensor.soilFe);
                    break;
                default:
                    return vector<float>();
            }
        }
    }
    return soilMoistureSensorsValues;
}








