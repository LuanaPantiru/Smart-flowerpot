#include "include/AppHardwareHandler.h"
#include "include/app_config.h"
#include <random>
#include <fstream>
#include <iostream>

// https://github.com/elnormous/HTTPRequest
#include "include/external/HTTPRequest.h"

AppHardwareHandler *AppHardwareHandler::instance = nullptr;

AppHardwareHandler::AppHardwareHandler() {
    int matrixDimension = 5;

    // populate soil sensors matrix
    for (int i = 0; i < matrixDimension; i++) {
        vector<SoilSensor> sensor(matrixDimension);
        soilSensorsMatrix.push_back(sensor);
    }

    // simulate sdCard insertion
    ifstream sdCard(FILE_PATH_FOR_SD_CARD);
    if(sdCard.is_open()){
        while(!sdCard.eof()) {
            string music;
            std::getline(sdCard, music);
            vector<string> values = split (music, ",");
            string songName = values[0];
            string songArtist = values[1];
            float songLength = stof(values[2]);
            string songLyrics = values[3];

            sdCardMusic.emplace_back(make_tuple(songName, songArtist, songLength, songLyrics));
        }

        sdCard.close();
    }
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
    std::uniform_real_distribution<float> airTemperatureDistribution(0, 15);        // float between 0 and 15, optimal is between 5 and 12
    airTemperatureSensor = airTemperatureDistribution(mt);

    //generate a random value for air humidity
    std::uniform_real_distribution<float> airHumidityDistribution(30, 70);          // float between 30 and 70, optimal is between 40 and 60
    airHumiditySensor = airHumidityDistribution(mt);

    //generate a random value for light intensity
    std::uniform_real_distribution<float> lightIntensityDistribution(1000, 4000);   // between 1000 and 4000 (lux-SI unit of illuminance),
                                                                                    // optimal is between 1500 and 3000 lux
    lightIntensitySensor = lightIntensityDistribution(mt);

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
    // presume that DidYouKnowThat features are taken from some httpServer on the internet

    // https://github.com/elnormous/HTTPRequest
    try{
        http::Request request{SERVER_ROUTE_DID_YOU_KNOW_THAT};

        // send a get request
        const auto response = request.send("GET");

        // extract the result
        string name;
        string value;
        string receivedInfo = std::string{response.body.begin(), response.body.end()};
        auto jsonReceived = nlohmann::json::parse(receivedInfo);
        if(jsonReceived.contains("tag") && jsonReceived.contains("value")){
            name = jsonReceived["tag"];
            value = jsonReceived["value"];
            std::cout << "[SUCCESS] received value for did you know that: " << jsonReceived << "\n";
            return make_pair(name, value);
        }
        std::cerr << "[ERROR] No value for Did you know that [" << jsonReceived << "]\n";
        return make_pair("ERROR", "No value for Did you know that");
    }
    catch (const std::exception& e){
        std::cerr << "Request failed, error: " << e.what() << '\n';
        return make_pair("ERROR", "No value for Did you know that");
    }
}

std::vector<std::string> AppHardwareHandler::split(const string &s, const string &delimiter) {
    size_t posStart = 0, posEnd, delimiterLen = delimiter.length();
    string token;
    vector<string> res;

    while ((posEnd = s.find (delimiter, posStart)) != string::npos) {
        token = s.substr (posStart, posEnd - posStart);
        posStart = posEnd + delimiterLen;
        res.push_back (token);
    }

    res.push_back (s.substr (posStart));
    return res;
}









