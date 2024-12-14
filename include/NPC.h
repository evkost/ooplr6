#ifndef NPC_H
#define NPC_H

#include <string>
#include "NPCType.h"

class NPC {
public:
    NPC(NPCType type, const std::string& name, double x, double y)
            : type_(type), name_(name), x_(x), y_(y) {}
    virtual ~NPC() = default;

    NPCType getType() const { return type_; }
    std::string getName() const { return name_; }
    double getX() const { return x_; }
    double getY() const { return y_; }

private:
    NPCType type_;
    std::string name_;
    double x_;
    double y_;
};

#endif // NPC_H
