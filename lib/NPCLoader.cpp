#include "NPCLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<std::unique_ptr<NPC>> NPCLoader::loadFromFile(const std::string& filename) {
    std::vector<std::unique_ptr<NPC>> npcs;
    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(infile, line)) {
        if(line.empty()) continue;
        std::istringstream iss(line);
        std::string typeStr, name;
        double x, y;
        if (!(iss >> typeStr >> name >> x >> y)) {
            throw std::runtime_error("Invalid line format: " + line);
        }
        npcs.push_back(NPCFactory::createNPC(typeStr, name, x, y));
    }

    return npcs;
}
