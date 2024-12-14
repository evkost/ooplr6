#include <iostream>
#include <vector>
#include <memory>
#include "NPCFactory.h"
#include "NPCLoader.h"
#include "NPCSaver.h"
#include "EventManager.h"
#include "LoggerObserver.h"
#include "ScreenObserver.h"
#include "CombatVisitor.h"
#include "NPCType.h"

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;
    EventManager eventManager;

    auto logger = std::make_shared<LoggerObserver>("log.txt");
    auto screenObserver = std::make_shared<ScreenObserver>();
    eventManager.subscribe(logger);
    eventManager.subscribe(screenObserver);

    while(true) {
        std::cout << "\n--- Dungeon Editor ---\n";
        std::cout << "1. Add NPC\n";
        std::cout << "2. Save NPCs to File\n";
        std::cout << "3. Load NPCs from File\n";
        std::cout << "4. List NPCs\n";
        std::cout << "5. Start Combat Mode\n";
        std::cout << "6. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        if(choice == 1) {
            std::cout << "Select NPC type:\n";
            std::cout << "1. Squirrel\n";
            std::cout << "2. Elf\n";
            std::cout << "3. Bandit\n";
            std::cout << "Enter choice (1-3): ";
            int typeChoice;
            std::cin >> typeChoice;

            NPCType type;
            switch(typeChoice) {
                case 1:
                    type = NPCType::Squirrel;
                    break;
                case 2:
                    type = NPCType::Elf;
                    break;
                case 3:
                    type = NPCType::Bandit;
                    break;
                default:
                    std::cout << "Invalid NPC type selection.\n";
                    continue;
            }

            std::string name;
            double x, y;
            std::cout << "Enter NPC name: ";
            std::cin >> name;
            std::cout << "Enter X coordinate (0-500): ";
            std::cin >> x;
            std::cout << "Enter Y coordinate (0-500): ";
            std::cin >> y;

            if(x < 0 || x > 500 || y < 0 || y > 500) {
                std::cout << "Invalid coordinates. Must be between 0 and 500.\n";
                continue;
            }

            bool nameExists = false;
            for(const auto& npc : npcs) {
                if(npc->getName() == name) {
                    nameExists = true;
                    break;
                }
            }
            if(nameExists) {
                std::cout << "NPC with this name already exists. Please choose a different name.\n";
                continue;
            }

            try {
                auto npc = NPCFactory::createNPC(type, name, x, y);
                npcs.emplace_back(std::move(npc));
                std::cout << "NPC added successfully.\n";
            } catch(const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        else if(choice == 2) {
            std::string filename;
            std::cout << "Enter filename to save NPCs: ";
            std::cin >> filename;
            try {
                NPCSaver::saveToFile(filename, npcs);
                std::cout << "NPCs saved successfully to " << filename << "\n";
            } catch(const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        else if(choice == 3) {
            std::string filename;
            std::cout << "Enter filename to load NPCs: ";
            std::cin >> filename;
            try {
                npcs = NPCLoader::loadFromFile(filename);
                std::cout << "NPCs loaded successfully from " << filename << "\n";
            } catch(const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        else if(choice == 4) {
            if(npcs.empty()) {
                std::cout << "No NPCs to display.\n";
            } else {
                std::cout << "\nList of NPCs:\n";
                for(const auto& npc : npcs) {
                    std::cout << "Type: " << NPCTypeToString(npc->getType())
                              << ", Name: " << npc->getName()
                              << ", X: " << npc->getX()
                              << ", Y: " << npc->getY() << "\n";
                }
            }
        }
        else if(choice == 5) {
            double distance;
            std::cout << "Enter combat distance: ";
            std::cin >> distance;
            if(distance <=0 ) {
                std::cout << "Invalid combat distance.\n";
                continue;
            }

            CombatVisitor combatVisitor(eventManager, distance);
            combatVisitor.engageCombat(npcs);
            std::cout << "Combat mode ended.\n";
        }
        else if(choice == 6) {
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
