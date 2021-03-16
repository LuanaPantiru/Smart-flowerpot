cmake_minimum_required(VERSION 3.16)
project(smart_pot)

set(CMAKE_CXX_STANDARD 17)

add_executable(smart_pot
        src/main.cpp
        src/include/app_config.h
        src/AppHttpHandler.cpp src/include/AppHttpHandler.h
        src/AppHardwareHandler.cpp src/include/AppHardwareHandler.h
        src/SmartPot.cpp src/include/SmartPot.h
        src/NotificationCenter.cpp src/include/NotificationCenter.h)

# Se instaleaza libraria Pistache si se link-eaza.
# https://stackoverflow.com/questions/52468551/include-pistache-in-c-project
# https://stackoverflow.com/questions/28536435/how-to-link-a-static-library-to-an-executable-using-cmake/28537032#28537032
# https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake/39600062#39600062
TARGET_LINK_LIBRARIES(smart_pot pistache)
TARGET_LINK_LIBRARIES(smart_pot pthread)

# Am instalat libraria pe masina de Ubuntu cu comanda:  sudo apt-get install nlohmann-json3-dev
# Am link-at libraria
# https://github.com/nlohmann/json/issues/1703
find_package(nlohmann_json 3.2.0 REQUIRED)
TARGET_LINK_LIBRARIES(smart_pot nlohmann_json::nlohmann_json)