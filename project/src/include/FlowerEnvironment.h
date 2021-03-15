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

        // this will be used to show a different display if no env is set
        bool environmentIsSet = false;

        string name;
        string type;

        // pairs for [min,max] interval
        pair <float,float> temperature;
        pair <float,float> humidity;
        pair <float,float> light;

        //thread
        std::thread monitorThread;

    public:
        static FlowerEnvironment *getInstance();

        void showEnvironment();
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


        // setters
        void setEnvironmentIsSet(bool isSet);
        void setName(const string &newName);
        void setTemperature(const pair<float, float> &newTemperature);

        // getters
        [[nodiscard]] const pair<float, float> &getHumidity() const;
        [[nodiscard]] const string &getName() const;
        [[nodiscard]] const pair<float, float> &getTemperature() const;
};


#endif //SMART_POD_FLOWER_ENVIRONMENT_H
