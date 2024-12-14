#ifndef SCREENOBSERVER_H
#define SCREENOBSERVER_H

#include "Observer.h"
#include <iostream>
#include <mutex>
#include <string>

class ScreenObserver : public Observer {
public:
    void onNPCKilled(const std::string& killer, const std::string& victim) override;

private:
    std::mutex mutex_;
};

#endif // SCREENOBSERVER_H
