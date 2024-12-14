#include "EventManager.h"

void EventManager::subscribe(std::shared_ptr<Observer> observer) {
    observers_.emplace_back(observer);
}

void EventManager::notify(const std::string& killer, const std::string& victim) {
    for (const auto& obs : observers_) {
        if(obs) {
            obs->onNPCKilled(killer, victim);
        }
    }
}
