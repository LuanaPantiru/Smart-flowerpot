#include "include/AppHardwareHandler.h"
#include "include/app_config.h"
#include <random>
AppHardwareHandler *AppHardwareHandler::instance = nullptr;

AppHardwareHandler::AppHardwareHandler() {
    int matrixDimension = 5;

    // populate soil sensors matrix
    for (int i = 0; i < matrixDimension; i++) {
        vector<SoilSensor> sensor(matrixDimension);
        soilSensorsMatrix.push_back(sensor);
    }

    // populate music sd card
    sdCardMusic.emplace_back(make_tuple("Song A", "Artist song A", 3.14, "la la la la la la la"));
    sdCardMusic.emplace_back(make_tuple("Song B", "Artist song B", 2.20, "la li lu la li la la"));

    // populate DidYouKnowThat
    didYouKnowThatServerValues.push(make_pair("Interesant", "Stiati ca floarea are frunze?"));
    didYouKnowThatServerValues.push(make_pair("Si mai Interesant", "Stiati ca merele cresc in copaci?"));
}

AppHardwareHandler *AppHardwareHandler::getInstance() {
    if (!instance) {
        instance = new AppHardwareHandler();
    }
    return instance;
}

void AppHardwareHandler::loadSensorInfo() {

    // https://en.cppreference.com/w/cpp/numeric/random
    // https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library/19666713#19666713

    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_real_distribution<float> soilMoistureDistribution(30, 100); // between 30 and 100, optimal is between 60 and 80
    std::uniform_real_distribution<float> soilPhDistribution(4, 8);          // float between 4 and 8, optimal is between 5 and 6.5
    std::uniform_real_distribution<float> soilSDistribution(0, 1);           // float between 0 and 1, optimal is between 0.01 and 0.08
    std::uniform_real_distribution<float> soilKDistribution(1, 2);           // float between 1 and 2, optimal is 1.5
    std::uniform_real_distribution<float> soilMgDistribution(0, 1);          // float between 0 and 1, optimal is between 0.1 and 0.5
    std::uniform_real_distribution<float> soilFeDistribution(0, 1);          // float between 0 and 1, optimal is between 0.005 and 0.2
    std::uniform_real_distribution<float> soilNDistribution(1, 2);           // float between 1 and 2, optimal is 1.5

    // generate random values for soil nutrients
    for (int i = 0; i < soilSensorsMatrix.size(); i++) {
        for (int j = 0; j < soilSensorsMatrix[i].size(); j++) {
            soilSensorsMatrix[i][j].soilMoisture = soilMoistureDistribution(mt);
            soilSensorsMatrix[i][j].soilPh = soilPhDistribution(mt);
            soilSensorsMatrix[i][j].soilS = soilSDistribution(mt);
            soilSensorsMatrix[i][j].soilK = soilKDistribution(mt);
            soilSensorsMatrix[i][j].soilMg = soilMgDistribution(mt);
            soilSensorsMatrix[i][j].soilFe = soilFeDistribution(mt);
            soilSensorsMatrix[i][j].soilN = soilNDistribution(mt);
        }
    }

    //generate a random value for air temperature
    airTemperatureSensor = float( rand() ) / float( ( RAND_MAX / 15 ) );   //float between 0 and 15, optimal is between 5 and 12

    //generate a random value for air humidity
    airHumiditySensor = float( rand() ) / float( ( RAND_MAX / 40 ) ) + 30; //float between 30 and 70, optimal is between 40 and 60

    //generate a random value for light intensity
    lightIntensitySensor = rand() % 3000 + 1000;                           //between 1000 and 4000 (lux-SI unit of illuminance), optimal is between 1500 and 3000 lux

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
    for (const auto &sensors : soilSensorsMatrix) {
        for (auto sensor : sensors) {
            switch (sensorCode) {
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

const vector<SongInfo> &AppHardwareHandler::getSdCardMusic() const {
    return sdCardMusic;
}

nlohmann::json AppHardwareHandler::exportSongsToJson() {
    nlohmann::json exportJson;
    for (int i = 0; i < sdCardMusic.size(); i++) {
        exportJson[to_string(i)] = sdCardMusic[i];
    }
    return exportJson;
}

DidYouKnowThat AppHardwareHandler::getDidYouKnowThatServerValue() {
    DidYouKnowThat tmp = didYouKnowThatServerValues.front();
    didYouKnowThatServerValues.pop();
    didYouKnowThatServerValues.push(tmp);
    return tmp;
}









