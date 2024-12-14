#ifndef BANDIT_H
#define BANDIT_H

#include "NPC.h"

class Bandit : public NPC {
public:
    Bandit(const std::string& name, double x, double y)
            : NPC(NPCType::Bandit, name, x, y) {}
};

#endif // BANDIT_H
