#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, double x, double y)
            : NPC(NPCType::Squirrel, name, x, y) {}
};

#endif // SQUIRREL_H
