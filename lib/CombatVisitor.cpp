#include "CombatVisitor.h"

CombatVisitor::CombatVisitor(EventManager& eventManager, double combatDistance)
        : eventManager_(eventManager), combatDistance_(combatDistance) {}

double CombatVisitor::calculateDistance(const NPC* a, const NPC* b) const {
    double dx = a->getX() - b->getX();
    double dy = a->getY() - b->getY();
    return std::sqrt(dx * dx + dy * dy);
}

bool CombatVisitor::canKill(NPCType killerType, NPCType victimType) const {
    if(killerType == NPCType::Elf && victimType == NPCType::Bandit) return true;
    if(killerType == NPCType::Bandit && victimType == NPCType::Squirrel) return true;
    if(killerType == NPCType::Squirrel && victimType == NPCType::Elf) return true;
    return false;
}

void CombatVisitor::engageCombat(std::vector<std::unique_ptr<NPC>>& npcs) {
    std::unordered_set<size_t> toRemove;

    for(size_t i = 0; i < npcs.size(); ++i) {
        for(size_t j = i + 1; j < npcs.size(); ++j) {
            if(toRemove.find(i) != toRemove.end() || toRemove.find(j) != toRemove.end()) {
                continue;
            }

            NPC* npc1 = npcs[i].get();
            NPC* npc2 = npcs[j].get();

            double distance = calculateDistance(npc1, npc2);
            if(distance <= combatDistance_) {
                bool npc1KillsNpc2 = canKill(npc1->getType(), npc2->getType());
                bool npc2KillsNpc1 = canKill(npc2->getType(), npc1->getType());

                if(npc1KillsNpc2) {
                    eventManager_.notify(npc1->getName(), npc2->getName());
                    toRemove.insert(j);
                }

                if(npc2KillsNpc1) {
                    eventManager_.notify(npc2->getName(), npc1->getName());
                    toRemove.insert(i);
                }
            }
        }
    }

    if(!toRemove.empty()) {
        std::vector<size_t> sortedToRemove(toRemove.begin(), toRemove.end());
        std::sort(sortedToRemove.begin(), sortedToRemove.end(), std::greater<size_t>());
        for(auto idx : sortedToRemove) {
            if(idx < npcs.size()) {
                npcs.erase(npcs.begin() + idx);
            }
        }
    }
}
