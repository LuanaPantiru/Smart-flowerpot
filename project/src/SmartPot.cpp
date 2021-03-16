#include "include/app_config.h"
#include "include/SmartPot.h"
#include "include/AppHardwareHandler.h"
#include "include/NotificationCenter.h"
#include <thread>
#include <iostream>
#include <fstream>

SmartPot *SmartPot::instance = nullptr;

SmartPot *SmartPot::getInstance() {
    if (!instance) {
        instance = new SmartPot();
    }
    return instance;
}

bool SmartPot::isGoodAirTemperature(float currentAirTemperature) const {
    //Daca nu e setat intervalul, nu monitorizam. Presupunem ca rezultatul este ok.
    if (!get<0>(airTemperature)) return true;
    return get<1>(airTemperature) <= currentAirTemperature && currentAirTemperature <= get<2>(airTemperature);
}

bool SmartPot::isGoodAirHumidity(float currentAirHumidity) const {
    //Daca nu e setat intervalul, nu monitorizam. Presupunem ca rezultatul este ok.
    if (!get<0>(airHumidity)) return true;
    return get<1>(airHumidity) <= currentAirHumidity && currentAirHumidity <= get<2>(airHumidity);
}

bool SmartPot::isGoodLightIntensity(float currentLightIntensity) const {
    if (!get<0>(lightIntensity)){
        return true;
    }
    return get<1>(lightIntensity) <= currentLightIntensity && currentLightIntensity <= get<2>(lightIntensity);
}

float SmartPot::calculateAverage(const vector<float>& sensorValues) {
    float averageValue = 0.0f;
    for(auto value : sensorValues){
        averageValue += value;
    }
    return averageValue / sensorValues.size();
}

bool SmartPot::isGoodSoilValue(int sensorCode, vector<float> &currentSensorValues) const {
    float averageValue = SmartPot::calculateAverage(currentSensorValues);
    switch (sensorCode){
        case SOIL_MOISTURE_SENSOR:
            if (!get<0>(soilMoisture)){
                return true;
            }
            return get<1>(soilMoisture) <= averageValue && averageValue <= get<2>(soilMoisture);
        case SOIL_PH_SENSOR:
            if (!get<0>(soilPh)){
                return true;
            }
            return get<1>(soilPh) <= averageValue && averageValue <= get<2>(soilPh);
        case SOIL_N_SENSOR:
            if (!get<0>(soilN)){
                return true;
            }
            return get<1>(soilN) <= averageValue && averageValue <= get<2>(soilN);
        case SOIL_K_SENSOR:
            if (!get<0>(soilK)){
                return true;
            }
            return get<1>(soilK) <= averageValue && averageValue <= get<2>(soilK);
        case SOIL_S_SENSOR:
            if (!get<0>(soilS)){
                return true;
            }
            return get<1>(soilS) <= averageValue && averageValue <= get<2>(soilS);
        case SOIL_Mg_SENSOR:
            if (!get<0>(soilMg)){
                return true;
            }
            return get<1>(soilMg) <= averageValue && averageValue <= get<2>(soilMg);
        case SOIL_Fe_SENSOR:
            if (!get<0>(soilFe)){
                return true;
            }
            return get<1>(soilFe) <= averageValue && averageValue <= get<2>(soilFe);
        default:
            return true;
    }
}


void SmartPot::checkGeneralHealth() const {

    //TODO: Must be implemented
    //      - Here must be checked the general flower health and after this check is made you must add
    //        ONE SINGLE notification using the GENERAL_HEALTH_NOTIFICATION tag.
    //      - Value from 'notification message' must be HAPPY, NEUTRAL or SAD
    //      - Will be created a vector for logs where will be logged everything which is not in parameters


    /*
        // Example:

        vector<Log> logs;

        // get current sensor value
        float currentAirHumidity = AppHardwareHandler::getInstance()->getAirTemperatureSensor();

        // make some calculations


        if(!isGoodAirHumidity(currentAirHumidity)) {
            // if something is wrong log that
            // log example
            string logMessage = "Value for airHumidity [" + to_string(currentAirHumidity) + "] is not in interval [" +
                    to_string(get<1>(airHumidity)) + " , " +
                    to_string(get<2>(airHumidity)) + "]";

            NotificationCenter::addLog(logs,logMessage);
            NotificationCenter::addLog(logs,logMessage);


             // make some calculations

        }

        // make some calculations


        // notification example
        NotificationCenter::getInstance()->addNotification(GENERAL_HEALTH_NOTIFICATION, HAPPY, logs);
    */

}

void SmartPot::checkSoilMoisture() const {
    //TODO: Must be implemented
    //      - Here must be checked the soil moisture and after this check is made you must add
    //        ONE SINGLE notification using the WATER_NOTIFICATION tag.
    //      - Value from 'notification message' must be a float value >= 0. This value will represent
    //        the water quantity which flower need at that time
    //      - Will be created a vector for logs where will be logged everything which is not in parameters


    /*
        // Example:
            vector<Log> logs;

            vector<float> allSoilMoistureSensorValues =
                    AppHardwareHandler::getInstance()->getSoilSpecificSensorValues(SOIL_MOISTURE_SENSOR);

            // make some calculations

            // if something is wrong log it
            // log example
            string logMessage = "here will be a log message";
            NotificationCenter::addLog(logs,logMessage);


            // make some calculations

            // notification example
            float water = 3.14; // this value will result from previous calculations
            NotificationCenter::getInstance()->addNotification(WATER_NOTIFICATION, std::to_string(water), logs);
    */


}

void SmartPot::checkSoilHealth() const {
    //TODO: Must be implemented
    //      - Here must be checked the soil general health and after this check is made you must add
    //        ONE SINGLE notification using the SOIL_HEALTH_NOTIFICATION tag.
    //      - Value from 'notification message' must be HAPPY, NEUTRAL or SAD
    //      - Will be created a vector for logs where will be logged everything which is not in parameters


    /*
        // Example:

        vector<Log> logs;

        // get current sensor value different soil sensors
        vector<float> allSoilMoistureSensorValues =
            AppHardwareHandler::getInstance()->getSoilSpecificSensorValues(SOIL_MOISTURE_SENSOR);

        // get other values

        // make some calculations


        // if something is wrong log that
        // log example
        string logMessage = "here will be a log message";

        NotificationCenter::addLog(logs,logMessage);

        // make some calculations


        // notification example
        NotificationCenter::getInstance()->addNotification(SOIL_HEALTH_NOTIFICATION, HAPPY, logs);
    */

}

void SmartPot::checkAirQuality() const {
    //TODO: Must be implemented
    //      - Here must be checked the air general quality and after this check is made you must add
    //        ONE SINGLE notification using the AIR_QUALITY_NOTIFICATION tag.
    //      - Value from 'notification message' must be HAPPY, NEUTRAL or SAD
    //      - Will be created a vector for logs where will be logged everything which is not in parameters


    /*
        // Example:

        vector<Log> logs;

        // get current sensor value
        float currentAirTemperature = AppHardwareHandler::getInstance()->getAirHumiditySensor();

        // get other values

        // make some calculations


        // if something is wrong log that
        // log example
        string logMessage = "here will be a log message";

        NotificationCenter::addLog(logs,logMessage);

        // make some calculations


        // notification example
        NotificationCenter::getInstance()->addNotification(SOIL_HEALTH_NOTIFICATION, HAPPY, logs);
    */

}

void SmartPot::waterFlower(float waterQuantity) {
    //TODO: Must be implemented
}

void SmartPot::startMonitorThreadFunction() const {
    ofstream file("output/monitor_logs.txt");
    if(!file.is_open()) return;
    file << "A inceput procesul de monitorizare!" << endl;

    while (environmentIsSet.load()){

        //Generare valori pentru senzori
        AppHardwareHandler::getInstance()->loadSensorInfo();

        // se verifica statusul curent
        checkGeneralHealth();
        checkAirQuality();
        checkSoilHealth();
        checkSoilMoisture();

        //Dupa toate verificarile anterioare unde s-a populat vectorul de notificari
        //Trimitem alertele
        NotificationCenter::getInstance()->sendAlerts();

        if(file.is_open()){
            file << "Am verificat starea la ora " << NotificationCenter::getCurrentTime() << endl;
        }

        // sleep for 5 sec
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void SmartPot::startMonitorLoop() {
    monitorThread = std::thread([]{SmartPot::getInstance()->startMonitorThreadFunction();});
}

nlohmann::json SmartPot::exportConfigurationToJson() {
    nlohmann::json export_json;

    export_json["flower_info"]["name"] = flowerName;
    export_json["flower_info"]["species"] = flowerSpecies;

    export_json["flower_health"]["air"]["temperature"]["isSet"] = get<0>(airTemperature);
    export_json["flower_health"]["air"]["temperature"]["min"] = get<1>(airTemperature);
    export_json["flower_health"]["air"]["temperature"]["max"] = get<2>(airTemperature);

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

    export_json["environmentIsSet"] = environmentIsSet.load();
    return export_json;
}

void SmartPot::setFlowerEnvironment(nlohmann::json input) {

    flowerName = input["flower_info"]["name"];
    flowerSpecies = input["flower_info"]["species"];

    get<0>(airTemperature) = input["flower_health"]["air"]["temperature"]["isSet"];
    get<1>(airTemperature) = input["flower_health"]["air"]["temperature"]["min"];
    get<2>(airTemperature) = input["flower_health"]["air"]["temperature"]["max"];

    get<0>(airHumidity) = input["flower_health"]["air"]["humidity"]["isSet"];
    get<1>(airHumidity) = input["flower_health"]["air"]["humidity"]["min"];
    get<2>(airHumidity) = input["flower_health"]["air"]["humidity"]["max"];

    get<0>(lightIntensity) = input["flower_health"]["air"]["light_intensity"]["isSet"];
    get<1>(lightIntensity) = input["flower_health"]["air"]["light_intensity"]["min"];
    get<2>(lightIntensity) = input["flower_health"]["air"]["light_intensity"]["max"];

    get<0>(soilMoisture) = input["flower_health"]["soil"]["moisture"]["isSet"];
    get<1>(soilMoisture) = input["flower_health"]["soil"]["moisture"]["min"];
    get<2>(soilMoisture) = input["flower_health"]["soil"]["moisture"]["max"];

    get<0>(soilPh) = input["flower_health"]["soil"]["ph"]["isSet"];
    get<1>(soilPh) = input["flower_health"]["soil"]["ph"]["min"];
    get<2>(soilPh) = input["flower_health"]["soil"]["ph"]["max"];

    get<0>(soilN) = input["flower_health"]["soil"]["N"]["isSet"];
    get<1>(soilN) = input["flower_health"]["soil"]["N"]["min"];
    get<2>(soilN) = input["flower_health"]["soil"]["N"]["max"];

    get<0>(soilK) = input["flower_health"]["soil"]["K"]["isSet"];
    get<1>(soilK) = input["flower_health"]["soil"]["K"]["min"];
    get<2>(soilK) = input["flower_health"]["soil"]["K"]["max"];

    get<0>(soilS) = input["flower_health"]["soil"]["S"]["isSet"];
    get<1>(soilS) = input["flower_health"]["soil"]["S"]["min"];
    get<2>(soilS) = input["flower_health"]["soil"]["S"]["max"];

    get<0>(soilMg) = input["flower_health"]["soil"]["Mg"]["isSet"];
    get<1>(soilMg) = input["flower_health"]["soil"]["Mg"]["min"];
    get<2>(soilMg) = input["flower_health"]["soil"]["Mg"]["max"];

    get<0>(soilFe) = input["flower_health"]["soil"]["Fe"]["isSet"];
    get<1>(soilFe) = input["flower_health"]["soil"]["Fe"]["min"];
    get<2>(soilFe) = input["flower_health"]["soil"]["Fe"]["max"];

    environmentIsSet.store(true);
}


void SmartPot::startMusicPlayFeature() {

    ofstream musicFile("output/music_play.txt");
    if(!musicFile.is_open()){
        // sd card problems
        return;
    }

    musicFile << "======================\n";
    musicFile << "Music feature started!\n";
    musicFile << "======================\n";

    unsigned int previousSong = -1;
    string song;
    string artist;
    int seconds;
    string lyrics;

    musicPlay.store(true);
    // simulate playing music by writing lyrics in a file at some time
    while(musicPlay.load()){

        // if a new song is played (previous song was not finished)
        if(currentSong.load() != previousSong){
            if (currentSong.load() < 0 || currentSong.load() >= AppHardwareHandler::getInstance()->getSdCardMusic().size()) {
                musicFile << "Song id [" << currentSong.load() << "] not found" << endl;
                musicPlay.store(false);
                break;
            }

            // get new current song info
            auto songInfo = AppHardwareHandler::getInstance()->getSdCardMusic()[currentSong.load()];
            previousSong = currentSong.load();
            song = get<0>(songInfo);
            artist = get<1>(songInfo);
            seconds = (int)get<2>(songInfo) * 60;
            lyrics = get<3>(songInfo);
        }

        musicFile << "=======================================" << endl;
        musicFile << "Song [" << song << "] by [" << artist << "] will play for [" << seconds << "] seconds!\n";
        musicFile << "---------------------------------------" << endl;
        musicFile << lyrics << endl;

        int threadSleepDuration = 5;
        seconds -= threadSleepDuration;

        // sleep for threadSleepDuration sec
        std::this_thread::sleep_for(std::chrono::seconds(threadSleepDuration));

        if(seconds <= 0){
            musicPlay.store(false);
            musicFile << "Song [" << song << "] finished!\n";
            musicFile << "-------------------------" << endl;
            break;
        }
    }

    musicFile << "======================\n";
    musicFile << "Music feature stopped!\n";
    musicFile << "======================\n";

    musicFile.close();
}

void SmartPot::setCurrentSong(unsigned int song) {
    currentSong.store(song);
}

void SmartPot::stopMusicPlayFeature() {
    musicPlay.store(false);
}

void SmartPot::playMusic(unsigned int songId) {
    SmartPot::getInstance()->setCurrentSong(songId);
    // if feature is already started return
    if(musicPlay.load()){
        return;
    }
    musicThread = std::thread([]{SmartPot::getInstance()->startMusicPlayFeature();});
}

bool SmartPot::isEnvironmentSet() const {
    return environmentIsSet.load();
}











