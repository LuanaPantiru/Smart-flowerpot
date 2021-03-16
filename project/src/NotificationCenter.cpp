#include <iomanip>
#include <iostream>
#include <fstream>
#include "include/NotificationCenter.h"
#include "include/app_config.h"

NotificationCenter * NotificationCenter::instance = nullptr;

NotificationCenter *NotificationCenter::getInstance() {
    if (!instance) {
        instance = new NotificationCenter();
    }
    return instance;
}

void NotificationCenter::addLog(vector<Log> &logs, const string& logMessage) {
    logs.emplace_back(make_pair(NotificationCenter::getCurrentTime(), logMessage));
}

void NotificationCenter::addNotification(const string &notificationType, const string &notificationMessage,
                                         const vector<Log> &notificationLogs) {
    notifications.emplace_back(make_tuple(NotificationCenter::getCurrentTime(), notificationType,
                                          notificationMessage, notificationLogs));
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

    // first print all notifications
    printNotifications();

    for(auto notification: notifications){

        string notificationTime = get<0>(notification);
        string notificationType = get<1>(notification);
        string notificationMessage = get<2>(notification);

        if(notificationType == GENERAL_HEALTH_NOTIFICATION){
            // TODO: here should show a a smiley face on display (happy, neutral or sad)
            //  notificationMessage will contain HAPPY, NEUTRAL or SAD
            continue;
        }
        if(notificationType == WATER_NOTIFICATION){
            // TODO: here should show a water icon on display
            continue;
        }
        if(notificationType == SOIL_HEALTH_NOTIFICATION){
            // TODO: here should show a a smiley face for soil on display (happy, neutral or sad)
            //  notificationMessage will contain HAPPY, NEUTRAL or SAD
            continue;
        }
        if(notificationType == AIR_QUALITY_NOTIFICATION){
            // TODO: here should show a a smiley face for air on display (happy, neutral or sad)
            //  notificationMessage will contain HAPPY, NEUTRAL or SAD
            continue;
        }

    }

    // after alerts are sent delete all because new alerts will be created if problems were not solved
    notifications.clear();
}

void NotificationCenter::printNotifications() {
    ofstream logFile("output/notification_center_logs.txt");
    if(!logFile.is_open()){
        return;
    }

    for(const auto& notification : notifications){
        logFile << "==================================================================\n";
        logFile << "[" << get<0>(notification) << "] [" << get<1>(notification) << "] ["
                << get<2>(notification) << "]\n" ;
        logFile << "------------------------------------------------------------------\n";
        for(const auto& log : get<3>(notification)){
            logFile << "[" << log.first << "] " << log.second << "\n";
        }
        logFile << "==================================================================\n";
    }

    logFile.close();
}










