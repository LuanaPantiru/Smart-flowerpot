#ifndef SMART_POD_APP_HARDWARE_HANDLER_H
#define SMART_POD_APP_HARDWARE_HANDLER_H

#include <tuple>

using namespace std;

typedef tuple <unsigned short, unsigned short, unsigned short> Pixel;

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
    AppHardwareHandler() = default;
    static AppHardwareHandler *instance;

    float temperatureSensor{};
    float humiditySensor{};
    float lightSensor{};
    float dirtSensor{};
    Pixel lightMatrix[10][10];

public:
    static AppHardwareHandler *getInstance();

    /** Here values for sensors must be shuffled in order to simulate new values. */
    void loadSensorInfo();

    /** Simulate new colors for matrix light */
    void changeLightMatrix();

    /** getters */
    [[nodiscard]] float getTemperatureSensor() const {
        return temperatureSensor;
    }
    [[nodiscard]] float getHumiditySensor() const {
        return humiditySensor;
    }

};


#endif //SMART_POD_APP_HARDWARE_HANDLER_H
