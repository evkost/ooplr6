// src/NPCSaver.cpp
#include "NPCSaver.h"
#include "NPCType.h"
#include <fstream>
#include <stdexcept>

void NPCSaver::saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs) {
    std::ofstream outfile(filename);
    if (!outfile) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    for (const auto& npc : npcs) {
        outfile << NPCTypeToString(npc->getType()) << " "
                << npc->getName() << " "
                << npc->getX() << " "
                << npc->getY() << "\n";
    }
}
