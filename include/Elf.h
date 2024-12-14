#ifndef ELF_H
#define ELF_H

#include "NPC.h"

class Elf : public NPC {
public:
    Elf(const std::string& name, double x, double y)
            : NPC(NPCType::Elf, name, x, y) {}
};

#endif // ELF_H
