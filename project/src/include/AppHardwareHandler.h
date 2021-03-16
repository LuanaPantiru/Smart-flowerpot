#ifndef SMART_POD_APP_HARDWARE_HANDLER_H
#define SMART_POD_APP_HARDWARE_HANDLER_H

#include <tuple>
#include <vector>

using namespace std;

typedef tuple <unsigned short, unsigned short, unsigned short> Pixel;

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

        // will be a 5 x 5 matrix (populated in constructor)
        vector<vector<Pixel>> lightMatrix;

    public:
        static AppHardwareHandler *getInstance();

        /** Here values for sensors must be shuffled in order to simulate new values. */
        void loadSensorInfo();

        /** Simulate new colors for matrix lightIntensity */
        void changeLightMatrix();

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

};


#endif //SMART_POD_APP_HARDWARE_HANDLER_H
