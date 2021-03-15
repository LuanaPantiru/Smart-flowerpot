#ifndef SMART_POD_NOTIFICATION_CENTER_H
#define SMART_POD_NOTIFICATION_CENTER_H

#include <vector>
#include <string>
#include <chrono>
#include <tuple>

using namespace std;

// (notification type, notification message, time when the notification was sent)
typedef tuple<string,string,time_t> Notification;

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

        vector<Notification> healthMonitorNotifications;

    public:
        static NotificationCenter *getInstance();
        static std::time_t getCurrentTime();

        void addHealthMonitorNotification(const Notification& notification);
};


#endif //SMART_POD_NOTIFICATION_CENTER_H
