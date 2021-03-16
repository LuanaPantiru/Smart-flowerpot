#ifndef SMART_POD_NOTIFICATION_CENTER_H
#define SMART_POD_NOTIFICATION_CENTER_H

#include <vector>
#include <string>
#include <chrono>
#include <tuple>
#include <utility>
#include <iomanip>

using namespace std;

// (time of log, log message)
typedef pair<string,string> Log;

// (time when the notification was sent, notification type, notification message, logs for this notification)
typedef tuple<string,string,string, vector<Log>> Notification;


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

        void printNotifications();

    public:
        static NotificationCenter *getInstance();
        static string getCurrentTime();
        static void addLog(vector<Log>& logs, const string& logMessage);

        void addNotification(const string& notificationType, const string& notificationMessage,
                             const vector<Log>& notificationLogs);
        void sendAlerts();
};


#endif //SMART_POD_NOTIFICATION_CENTER_H
