#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNPCKilled(const std::string& killer, const std::string& victim) = 0;
};

#endif // OBSERVER_H
