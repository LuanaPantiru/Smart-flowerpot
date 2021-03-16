#include <iomanip>
#include <iostream>
#include "include/NotificationCenter.h"
#include "include/app_config.h"

NotificationCenter * NotificationCenter::instance = nullptr;

NotificationCenter *NotificationCenter::getInstance() {
    if (!instance) {
        instance = new NotificationCenter();
    }
    return instance;
}

void NotificationCenter::addNotification(const Notification& notification) {
    notifications.push_back(notification);
}

string NotificationCenter::getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();

    return str;
}

void NotificationCenter::sendAlerts() {
    //TODO: De gasit unde afisam? Eg: Display-ul ghiveciului

    for(auto notification: notifications)
    {
        string code = get<0>(notification);
        if(code == GENERAL_NOTIFICATION)
        {
            //TODO
            continue;
        }
        if(code == WATER_NOTIFICATION)
        {
            //TODO
            continue;
        }
        //TODO: ifs...
    }

    //Stergem bufferul de notificari
    notifications.clear();
}
