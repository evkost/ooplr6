#include <gtest/gtest.h>
#include "NPCFactory.h"
#include "NPCLoader.h"
#include "NPCSaver.h"
#include "EventManager.h"
#include "LoggerObserver.h"
#include "ScreenObserver.h"
#include "CombatVisitor.h"
#include "NPCType.h"
#include <string>
#include <vector>

TEST(NPCFactoryTest, CreateNPC) {
    auto squirrel = NPCFactory::createNPC(NPCType::Squirrel, "Chippy", 100, 200);
    EXPECT_EQ(squirrel->getType(), NPCType::Squirrel);
    EXPECT_EQ(squirrel->getName(), "Chippy");
    EXPECT_DOUBLE_EQ(squirrel->getX(), 100);
    EXPECT_DOUBLE_EQ(squirrel->getY(), 200);

    auto elf = NPCFactory::createNPC(NPCType::Elf, "Legolas", 150, 250);
    EXPECT_EQ(elf->getType(), NPCType::Elf);
    EXPECT_EQ(elf->getName(), "Legolas");
    EXPECT_DOUBLE_EQ(elf->getX(), 150);
    EXPECT_DOUBLE_EQ(elf->getY(), 250);

    auto bandit = NPCFactory::createNPC(NPCType::Bandit, "Robin", 200, 300);
    EXPECT_EQ(bandit->getType(), NPCType::Bandit);
    EXPECT_EQ(bandit->getName(), "Robin");
    EXPECT_DOUBLE_EQ(bandit->getX(), 200);
    EXPECT_DOUBLE_EQ(bandit->getY(), 300);
}

TEST(NPCLoaderSaverTest, SaveLoadNPCs) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Elf, "Legolas", 100, 200));
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Bandit, "Robin", 150, 250));
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Squirrel, "Chippy", 200, 300));

    std::string filename = "test_npcs.txt";
    NPCSaver::saveToFile(filename, npcs);

    auto loadedNPCs = NPCLoader::loadFromFile(filename);
    ASSERT_EQ(loadedNPCs.size(), 3);

    EXPECT_EQ(loadedNPCs[0]->getType(), NPCType::Elf);
    EXPECT_EQ(loadedNPCs[0]->getName(), "Legolas");
    EXPECT_DOUBLE_EQ(loadedNPCs[0]->getX(), 100);
    EXPECT_DOUBLE_EQ(loadedNPCs[0]->getY(), 200);

    EXPECT_EQ(loadedNPCs[1]->getType(), NPCType::Bandit);
    EXPECT_EQ(loadedNPCs[1]->getName(), "Robin");
    EXPECT_DOUBLE_EQ(loadedNPCs[1]->getX(), 150);
    EXPECT_DOUBLE_EQ(loadedNPCs[1]->getY(), 250);

    EXPECT_EQ(loadedNPCs[2]->getType(), NPCType::Squirrel);
    EXPECT_EQ(loadedNPCs[2]->getName(), "Chippy");
    EXPECT_DOUBLE_EQ(loadedNPCs[2]->getX(), 200);
    EXPECT_DOUBLE_EQ(loadedNPCs[2]->getY(), 300);
}

TEST(CombatVisitorTest, EngageCombat) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Elf, "Legolas", 100, 100));
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Bandit, "Robin", 110, 110)); // В пределах дистанции
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Squirrel, "Chippy", 200, 200)); // Вне дистанции

    EventManager eventManager;
    auto logger = std::make_shared<LoggerObserver>("test_log.txt");
    auto screenObserver = std::make_shared<ScreenObserver>();
    eventManager.subscribe(logger);
    eventManager.subscribe(screenObserver);

    double combatDistance = 30.0;
    CombatVisitor combatVisitor(eventManager, combatDistance);
    combatVisitor.engageCombat(npcs);

    ASSERT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getName(), "Legolas");
    EXPECT_EQ(npcs[1]->getName(), "Chippy");
}

TEST(NPCUniquenessTest, UniqueNames) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(NPCFactory::createNPC(NPCType::Elf, "Legolas", 100, 100));

    bool nameExists = false;
    std::string newName = "Legolas";
    for(const auto& npc : npcs) {
        if(npc->getName() == newName) {
            nameExists = true;
            break;
        }
    }
    EXPECT_TRUE(nameExists);
}
