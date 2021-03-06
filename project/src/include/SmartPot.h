#ifndef SMART_POD_FLOWER_ENVIRONMENT_H
#define SMART_POD_FLOWER_ENVIRONMENT_H

#include <utility>
#include <string>
#include <nlohmann/json.hpp>
#include <thread>
#include <atomic>
#include "app_config.h"

using namespace std;

/**
 * This class will be singleton.
 *
 * Is the class for smart pot application.
 * */
class SmartPot {

    private:
        // specific for singleton class
        SmartPot() = default;
        static SmartPot *instance;

        // control monitor health thread
        std::thread monitorThread;
        std::atomic<bool> environmentIsSet = false;          // used to run health monitor loop
        std::atomic<bool> environmentIsResetting = false;    // used to block health monitor loop until env change is finished
        std::atomic<bool> environmentCanBeModified = false;  // used to block env change until calculations from
                                                             // health monitor loop are completed

        // control music feature thread
        std::thread musicThread;
        std::atomic<bool> musicPlay = false;
        std::atomic<unsigned int> currentSong{};

        // flower environments values
        // tuples are for [isSet,min,max] interval
        string flowerName;
        string flowerSpecies;
        tuple <bool,float,float> airTemperature;
        tuple <bool,float,float> airHumidity;
        tuple <bool,float,float> lightIntensity;
        tuple <bool,float,float> soilMoisture;
        tuple <bool,float,float> soilPh;
        tuple <bool,float,float> soilN;
        tuple <bool,float,float> soilK;
        tuple <bool,float,float> soilS;
        tuple <bool,float,float> soilMg;
        tuple <bool,float,float> soilFe;

        // display color. stateful functionality
        std::atomic<unsigned int> displayColorCode = DISPLAY_DEFAULT;

        static float calculateAverage(const vector<float>& sensorValues);

        /** This must be launched in a new thread and will monitor lifecycle of the flower. */
        void startMonitorThreadFunction();
        /** This must be launched in a new thread and will play the music. */
        void startMusicPlayFeature();

    public:
        static SmartPot *getInstance();

        void setFlowerEnvironment(nlohmann::json input, bool resetEnvironment);
        [[nodiscard]] nlohmann::json exportConfigurationToJson();

        [[nodiscard]] bool isGoodAirTemperature(float currentAirTemperature) const;
        [[nodiscard]] bool isGoodAirHumidity(float currentAirHumidity) const;
        [[nodiscard]] bool isGoodLightIntensity(float currentLightIntensity) const;

        /**
        * Use this in order to get check soil parameters for one specific parameter
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
        [[nodiscard]] bool isGoodSoilValue(int sensorCode, vector<float>& currentSensorValues) const;

        /** This will launch startMonitorThreadFunction() in a new thread. */
        void startMonitorLoop();
        void stopMonitorLoop();

        /** This will launch startMusicPlayFeature() in a new thread. */
        void playMusic(unsigned int songId);
        void stopMusicPlayFeature();

        /**
         * Este pentru feature-ul de monitorizare al sanatatii plantei.
         * Este ofilita/Nu este ofilita
         */
        void checkGeneralHealth() const;

        /**
         * Este pentru verificarea solului
         * Are/Nu are nevoie de apa
         */
        void checkSoilMoisture() const;

        /**
         * Este pentru verificarea starii stolului
         * Verifica daca solul are nevoie de nutrienti
         */
        void checkSoilHealth() const;

        /**
         * Este pentru verificarea starii calitatii aerului
         * Verifica daca caracteristicile aerului sunt bune
         */
        void checkAirQuality() const;

        /**
         * Folosita pentru a simula actiunea care se intampla dupa ce floarea este udata
         * Se ajusteaza parametrii: umiditatea solului etc..
         */
        void waterFlower(float waterQuantity);

        /** For DidYouKnowThat feature. **/
        static void sendDidYouKnowThat();

        // getters
        [[nodiscard]] bool isEnvironmentSet() const;
        [[nodiscard]] bool isMusicPlay() const;
        [[nodiscard]] string getDisplayColor() const;


        // setter
        void setCurrentSong(unsigned int song);
        void setDisplayColorCode(unsigned int colorCode);

};


#endif //SMART_POD_FLOWER_ENVIRONMENT_H
