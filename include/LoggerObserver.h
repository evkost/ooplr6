#ifndef LOGGEROBSERVER_H
#define LOGGEROBSERVER_H

#include "Observer.h"
#include <fstream>
#include <mutex>
#include <string>

class LoggerObserver : public Observer {
public:
    LoggerObserver(const std::string& filename);
    ~LoggerObserver();

    void onNPCKilled(const std::string& killer, const std::string& victim) override;

private:
    std::ofstream logfile_;
    std::mutex mutex_;
};

#endif // LOGGEROBSERVER_H
