cmake_minimum_required(VERSION 3.16)
project(smart_pot)

set(CMAKE_CXX_STANDARD 17)

add_executable(smart_pot
        src/main.cpp
        src/include/app_config.h
        src/AppHttpHandler.cpp src/include/AppHttpHandler.h
        src/AppHardwareHandler.cpp src/include/AppHardwareHandler.h
        src/SmartPot.cpp src/include/SmartPot.h
        src/NotificationCenter.cpp src/include/NotificationCenter.h
        src/MqttClientHandler.cpp src/include/MqttClientHandler.h)

# Libraries must exists
find_package(Threads REQUIRED)

# version https://github.com/pistacheio/pistache/blob/master/version.txt
#find_package(Pistache 0.0.2 REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

# https://stackoverflow.com/questions/60406578/using-https-github-com-eclipse-paho-mqtt-cpp-with-a-cmake-build
find_package(PahoMqttCpp REQUIRED)

# Link libraries
TARGET_LINK_LIBRARIES(smart_pot pthread)

# Se instaleaza libraria Pistache si se link-eaza.
# https://stackoverflow.com/questions/52468551/include-pistache-in-c-project
# https://stackoverflow.com/questions/28536435/how-to-link-a-static-library-to-an-executable-using-cmake/28537032#28537032
# https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake/39600062#39600062
TARGET_LINK_LIBRARIES(smart_pot pistache)

# Am instalat libraria pe masina de Ubuntu cu comanda:  sudo apt-get install nlohmann-json3-dev
# Am link-at libraria
# https://github.com/nlohmann/json/issues/1703
TARGET_LINK_LIBRARIES(smart_pot nlohmann_json::nlohmann_json)

# Am instalat libraria paho.mqtt.cpp
# https://github.com/eclipse/paho.mqtt.cpp
# https://stackoverflow.com/questions/60406578/using-https-github-com-eclipse-paho-mqtt-cpp-with-a-cmake-build
TARGET_LINK_LIBRARIES(smart_pot paho-mqttpp3 paho-mqtt3as)