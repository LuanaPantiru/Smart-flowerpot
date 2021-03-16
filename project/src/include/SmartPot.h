#ifndef SMART_POD_FLOWER_ENVIRONMENT_H
#define SMART_POD_FLOWER_ENVIRONMENT_H

#include <utility>
#include <string>
#include <nlohmann/json.hpp>
#include <thread>
#include <atomic>

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

        // threads
        std::atomic<bool> environmentIsSet = false;
        std::thread monitorThread;

        std::atomic<bool> musicPlay = false;
        std::thread musicThread;
        std::atomic<unsigned int> currentSong{};


        // simulating the DidYouKnowThat feature
        std::atomic<bool> runDidYouKnowThatThread = false;
        std::thread didYouKnowThatThread;


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

        static float calculateAverage(const vector<float>& sensorValues);

        /** This must be launched in a new thread and will monitor lifecycle of the flower. */
        void startMonitorThreadFunction() const;
        /** This must be launched in a new thread and will play the music. */
        void startMusicPlayFeature();
        /** This must be launched in a new thread and will simulate startDidYouKnowThat Feature. */
        void startDidYouKnowThatFeature();

    public:
        static SmartPot *getInstance();

        void setFlowerEnvironment(nlohmann::json input);
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

        /** This will launch startMusicPlayFeature() in a new thread. */
        void playMusic(unsigned int songId);
        void stopMusicPlayFeature();

        /** This will launch startMusicPlayFeature() in a new thread. */
        void startDidYouKnowThat();
        void stopDidYouKnowThat();


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

        // getters
        [[nodiscard]] bool isEnvironmentSet() const;

        // setter
        void setCurrentSong(unsigned int song);

};


#endif //SMART_POD_FLOWER_ENVIRONMENT_H
