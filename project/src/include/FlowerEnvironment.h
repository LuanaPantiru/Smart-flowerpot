#ifndef SMART_POD_FLOWER_ENVIRONMENT_H
#define SMART_POD_FLOWER_ENVIRONMENT_H

#include <utility>
#include <string>
#include <nlohmann/json.hpp>
#include <thread>

using namespace std;

/**
 * This class will be singleton.
 *
 * It will be initialized only once by the user and will contain information about the
 * environment in which the flower should be cared for.
 * */
class FlowerEnvironment {

    private:
        // specific for singleton class
        FlowerEnvironment() = default;
        static FlowerEnvironment *instance;

        //thread
        std::thread monitorThread;

        // this will be used to show a different display if no env is set
        bool environmentIsSet = false;

        // De aici in jos se pun valorile din json pt input
        string name;
        string species;

        // tuple for [isSet,min,max] interval
        tuple <bool,float,float> temperature;
        tuple <bool,float,float> airHumidity;
        tuple <bool,float,float> lightIntensity;
        tuple <bool,float,float> soilMoisture;
        tuple <bool,float,float> soilPh;
        tuple <bool,float,float> soilN;
        tuple <bool,float,float> soilK;
        tuple <bool,float,float> soilS;
        tuple <bool,float,float> soilMg;
        tuple <bool,float,float> soilFe;

        //
public:
        static FlowerEnvironment *getInstance();

        void parseEnvironmentInputSet(nlohmann::json input);
        [[nodiscard]] bool isGoodTemperature(float currentTemperature) const;
        [[nodiscard]] bool isGoodHumidity(float currentHumidity) const;

        /** This must be launched in a new thread
        *
        *  Here app will monitor flower health and is for the following feature:
        *     "Monitoring certain living conditions of the plant and draw a conclusion (is withered / not withered)"
        * */
        void startMonitorLoop();
        void checkHealth() const;
        [[nodiscard]] nlohmann::json exportConfigurationToJson() const;

        //getter
        [[nodiscard]] bool isEnvironmentIsSet() const;
};


#endif //SMART_POD_FLOWER_ENVIRONMENT_H
