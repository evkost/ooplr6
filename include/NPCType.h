#ifndef NPCTYPE_H
#define NPCTYPE_H

#include <string>
#include <stdexcept>

enum class NPCType {
    Squirrel,
    Elf,
    Bandit
};

inline std::string NPCTypeToString(NPCType type) {
    switch(type) {
        case NPCType::Squirrel: return "Squirrel";
        case NPCType::Elf: return "Elf";
        case NPCType::Bandit: return "Bandit";
        default: return "Unknown";
    }
}

inline NPCType StringToNPCType(const std::string& typeStr) {
    if(typeStr == "Squirrel") return NPCType::Squirrel;
    if(typeStr == "Elf") return NPCType::Elf;
    if(typeStr == "Bandit") return NPCType::Bandit;
    throw std::invalid_argument("Unknown NPC type: " + typeStr);
}

#endif // NPCTYPE_H
