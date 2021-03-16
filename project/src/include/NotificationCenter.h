#ifndef SMART_POD_NOTIFICATION_CENTER_H
#define SMART_POD_NOTIFICATION_CENTER_H

#include <vector>
#include <string>
#include <chrono>
#include <tuple>
#include <iomanip>

using namespace std;

// (notification type, notification message, time when the notification was sent)
typedef tuple<string,string,string> Notification;

/**
 * This class will be singleton.
 *
 * This is class used for showing notifications.
 * */
class NotificationCenter {
    private:
        // specific for singleton class
        NotificationCenter() = default;
        static NotificationCenter *instance;

        vector<Notification> notifications;

    public:
        static NotificationCenter *getInstance();
        static string getCurrentTime();

        void addNotification(const Notification& notification);
        void sendAlerts();

};


#endif //SMART_POD_NOTIFICATION_CENTER_H
