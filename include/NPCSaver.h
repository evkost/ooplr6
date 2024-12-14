#ifndef NPCSAVER_H
#define NPCSAVER_H

#include "NPC.h"
#include <vector>
#include <memory>
#include <string>

class NPCSaver {
public:
    static void saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs);
};

#endif // NPCSAVER_H
