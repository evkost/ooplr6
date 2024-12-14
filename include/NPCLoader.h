#ifndef NPCLOADER_H
#define NPCLOADER_H

#include "NPCFactory.h"
#include <vector>
#include <memory>
#include <string>

class NPCLoader {
public:
    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename);
};

#endif // NPCLOADER_H
