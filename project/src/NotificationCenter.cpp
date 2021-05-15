#include <iomanip>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "include/NotificationCenter.h"
#include "include/app_config.h"
#include "include/SmartPot.h"
#include "include/MqttClientHandler.h"

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

    nlohmann::json displayInfo;

    // first print all notifications
    printNotifications();

    for(auto notification: notifications){

        string notificationTime = get<0>(notification);
        string notificationType = get<1>(notification);
        string notificationMessage = get<2>(notification);

        if(notificationType == GENERAL_HEALTH_NOTIFICATION){

            displayInfo["general_health"] = notificationMessage;
            continue;
        }
        if(notificationType == WATER_NOTIFICATION){

            // message should be a float value
            waterQuantityNotification = std::stof(notificationMessage);

            if(waterQuantityNotification > 0){
                nlohmann::json waterNeeded;
                waterNeeded["water_needed"] = waterQuantityNotification;

                displayInfo["need_water"] = true;
                displayInfo["water_quantity_needed"] = waterQuantityNotification;

                MqttClientHandler::publishMessage(WATER_PUBLISHER, to_string(waterNeeded));
            }
            continue;
        }
        if(notificationType == SOIL_HEALTH_NOTIFICATION){

            displayInfo["soil_health"] = notificationMessage;
            continue;
        }
        if(notificationType == AIR_QUALITY_NOTIFICATION){

            displayInfo["air_quality"] = notificationMessage;
            continue;
        }

    }
    // current time
    displayInfo["notification_time"] = NotificationCenter::getCurrentTime();

    // display color. Stateful functionality
    displayInfo["display_color"] = SmartPot::getInstance()->getDisplayColor();

    MqttClientHandler::publishMessage(DISPLAY_PUBLISHER, to_string(displayInfo));

    // after alerts are sent delete all because new alerts will be created if problems were not solved
    notifications.clear();
}

void NotificationCenter::printNotifications() {
    ofstream logFile(FILE_PATH_FOR_NOTIFICATION_CENTER_LOGS);
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










