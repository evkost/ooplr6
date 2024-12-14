#include "ScreenObserver.h"

void ScreenObserver::onNPCKilled(const std::string& killer, const std::string& victim) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << killer << " killed " << victim << std::endl;
}
