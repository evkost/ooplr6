// src/NPCFactory.cpp
#include "NPCFactory.h"

std::unique_ptr<NPC> NPCFactory::createNPC(NPCType type, const std::string& name, double x, double y) {
    switch(type) {
        case NPCType::Squirrel:
            return std::make_unique<Squirrel>(name, x, y);
        case NPCType::Elf:
            return std::make_unique<Elf>(name, x, y);
        case NPCType::Bandit:
            return std::make_unique<Bandit>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type.");
    }
}

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& typeStr, const std::string& name, double x, double y) {
    NPCType type = StringToNPCType(typeStr);
    return createNPC(type, name, x, y);
}
