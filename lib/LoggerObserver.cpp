#include "LoggerObserver.h"
#include <stdexcept>

LoggerObserver::LoggerObserver(const std::string& filename) : logfile_(filename, std::ios::app) {
    if (!logfile_) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

LoggerObserver::~LoggerObserver() {
    if(logfile_.is_open()) {
        logfile_.close();
    }
}

void LoggerObserver::onNPCKilled(const std::string& killer, const std::string& victim) {
    std::lock_guard<std::mutex> lock(mutex_);
    logfile_ << killer << " killed " << victim << "\n";
}
