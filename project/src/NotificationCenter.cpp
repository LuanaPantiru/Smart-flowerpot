#include <iomanip>
#include <iostream>
#include "include/NotificationCenter.h"

NotificationCenter *NotificationCenter::instance = nullptr;

NotificationCenter *NotificationCenter::getInstance() {
    if (!instance) {
        instance = new NotificationCenter();
    }
    return instance;
}

void NotificationCenter::addHealthMonitorNotification(const Notification& notification) {
    healthMonitorNotifications.push_back(notification);
}

string NotificationCenter::getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();

    return str;
}
