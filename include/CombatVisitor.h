#ifndef COMBATVISITOR_H
#define COMBATVISITOR_H

#include "NPC.h"
#include "EventManager.h"
#include "NPCType.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>

class CombatVisitor {
public:
    CombatVisitor(EventManager& eventManager, double combatDistance);
    void engageCombat(std::vector<std::unique_ptr<NPC>>& npcs);

private:
    EventManager& eventManager_;
    double combatDistance_;

    double calculateDistance(const NPC* a, const NPC* b) const;
    bool canKill(NPCType killerType, NPCType victimType) const;
};

#endif // COMBATVISITOR_H
