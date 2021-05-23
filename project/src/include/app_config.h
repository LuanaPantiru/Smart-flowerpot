#ifndef SMART_POD_APP_CONFIG_H
#define SMART_POD_APP_CONFIG_H

#pragma once

using namespace std;

// must be an integer value
#define SERVER_PORT 9080

// log labels
#define INFO_LABEL "[INFO] "
#define ERROR_LABEL "[ERROR] "

// notification types
#define GENERAL_HEALTH_NOTIFICATION "GENERAL_HEALTH_NOTIFICATION"
#define WATER_NOTIFICATION "WATER_NOTIFICATION"
#define SOIL_HEALTH_NOTIFICATION "SOIL_HEALTH_NOTIFICATION"
#define AIR_QUALITY_NOTIFICATION "AIR_QUALITY_NOTIFICATION"

// smiley codes
#define HAPPY "HAPPY"
#define NEUTRAL "NEUTRAL"
#define SAD "SAD"

// soil sensor codes
#define SOIL_MOISTURE_SENSOR 1
#define SOIL_PH_SENSOR 2
#define SOIL_N_SENSOR 3
#define SOIL_K_SENSOR 4
#define SOIL_S_SENSOR 5
#define SOIL_Mg_SENSOR 6
#define SOIL_Fe_SENSOR 7

// display background color codes
#define DISPLAY_DEFAULT 122
#define DISPLAY_RED 123
#define DISPLAY_WHITE 124
#define DISPLAY_BLACK 125

// file paths
#define FILE_PATH_FOR_NOTIFICATION_CENTER_LOGS "output/notification_center_logs.txt"
#define FILE_PATH_FOR_MONITOR_LOGS "output/monitor_logs.txt"
#define FILE_PATH_FOR_MUSIC_PLAY "output/music_play.txt"
#define FILE_PATH_FOR_DID_YOU_KNOW_THAT "output/did_you_know_that.txt"
#define FILE_PATH_FOR_SD_CARD "input/sd_card.txt"

#endif //SMART_POD_APP_CONFIG_H
