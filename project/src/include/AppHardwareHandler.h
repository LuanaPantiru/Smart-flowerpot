#ifndef SMART_POD_APP_HARDWARE_HANDLER_H
#define SMART_POD_APP_HARDWARE_HANDLER_H

#include <tuple>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <nlohmann/json.hpp>

using namespace std;

typedef tuple <unsigned short, unsigned short, unsigned short> Pixel;

// tuple(song name, song artist, song duration, song lyrics)
typedef tuple<string, string, float, string> SongInfo;

// (did you know name, what did you know? )
typedef pair<string,string> DidYouKnowThat;

/** how a sensor in one point look */
typedef struct {
    float soilMoisture;
    float soilPh;
    float soilN;
    float soilK;
    float soilS;
    float soilMg;
    float soilFe;
} SoilSensor;

/**
 * This class will be singleton.
 *
 * This class will represent hardware configuration.
 * We presume that every sensor will receive data from a hardware component.
 *
 * Sensors should not have setters.
 *
 * Matrix Light can have a a setter.
 * */
class AppHardwareHandler {

    private:
        // specific for singleton class
        AppHardwareHandler();
        static AppHardwareHandler *instance;

        // sensors
        float airTemperatureSensor{};
        float airHumiditySensor{};
        float lightIntensitySensor{};
        // presume that are some sensors around the pot which will check soil parameters in multiple points
        // will be a 5 x 5 matrix (populated in constructor)
        vector<vector<SoilSensor>> soilSensorsMatrix;

        // sd card (presume that music is on sd card)
        vector<SongInfo> sdCardMusic;

        // presume that DidYouKnowThat features are taken from some server on the internet
        queue<DidYouKnowThat> didYouKnowThatServerValues;

    public:
        static AppHardwareHandler *getInstance();

        /** Here values for sensors must be shuffled in order to simulate new values. */
        void loadSensorInfo();

        /** getters */
        [[nodiscard]] float getAirTemperatureSensor() const;
        [[nodiscard]] float getAirHumiditySensor() const;
        [[nodiscard]] float getLightSensor() const;

        /**
         * Use this in order to get all values for one specific soil sensor
         *
         * sensorCode must be one of this values:
         *          SOIL_MOISTURE_SENSOR
         *          SOIL_PH_SENSOR
         *          SOIL_N_SENSOR
         *          SOIL_K_SENSOR
         *          SOIL_S_SENSOR
         *          SOIL_Mg_SENSOR
         *          SOIL_Fe_SENSOR
         * */
        [[nodiscard]] vector<float> getSoilSpecificSensorValues(int sensorCode) const;

        [[nodiscard]] const vector<SongInfo> &getSdCardMusic() const;
        [[nodiscard]] nlohmann::json exportSongsToJson();

        [[nodiscard]] DidYouKnowThat getDidYouKnowThatServerValue();

};


#endif //SMART_POD_APP_HARDWARE_HANDLER_H
