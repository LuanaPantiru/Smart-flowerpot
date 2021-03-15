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

std::time_t NotificationCenter::getCurrentTime() {
    return std::chrono::system_clock::to_time_t(chrono::system_clock::now());
}
