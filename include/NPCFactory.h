#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include "NPC.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Bandit.h"
#include "NPCType.h"
#include <memory>
#include <string>
#include <stdexcept>

class NPCFactory {
public:
    // Создание NPC на основе NPCType
    static std::unique_ptr<NPC> createNPC(NPCType type, const std::string& name, double x, double y);

    // Создание NPC из строки типа
    static std::unique_ptr<NPC> createNPC(const std::string& typeStr, const std::string& name, double x, double y);
};

#endif // NPCFACTORY_H
