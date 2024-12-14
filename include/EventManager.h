#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Observer.h"
#include <vector>
#include <memory>

class EventManager {
public:
    void subscribe(std::shared_ptr<Observer> observer);
    void notify(const std::string& killer, const std::string& victim);

private:
    std::vector<std::shared_ptr<Observer>> observers_;
};

#endif // EVENTMANAGER_H
