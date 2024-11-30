/// functions.cpp
#include "functions.h"
#include <limits>

bool getIntInput(std::istream& input, int& value) {
    input >> value;
    if (input.fail()) {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
        return false;
    }
    return true;
}

std::shared_ptr<Plant> selectPlant(std::istream& input) {
    int option;
    std::cout << "Choose the type of plant you want to add:\n";
    std::cout << "1. Lavender (Flowering)\n";
    std::cout << "2. Orchid (Flowering)\n";
    std::cout << "3. Hibiscus (Tropical)\n";
    std::cout << "4. Lily (Tropical)\n";
    std::cout << "5. AloeVera (Cacti)\n";
    std::cout << "6. Cactus (Cacti)\n";
    std::cout << "7. Flytrap (Exotic)\n";
    std::cout << "8. Bonsai (Exotic)\n";
    std::cout << "Enter your option: ";

    while (true) {
        if (getIntInput(input, option)) {
            switch (option) {
                case 1: return std::make_shared<Lavender>();
                case 2: return std::make_shared<Orchid>();
                case 3: return std::make_shared<Hibiscus>();
                case 4: return std::make_shared<Lily>();
                case 5: return std::make_shared<AloeVera>();
                case 6: return std::make_shared<Cactus>();
                case 7: return std::make_shared<Flytrap>();
                case 8: return std::make_shared<Bonsai>();
                default:
                    std::cout << "Invalid option! Please select a number between 1 and 8.\n";
                    break;
            }
        }
    }
}

void careForPlant(const Garden& garden, std::istream& input) {
    int slot;

    while (true) {
        std::cout << "Choose a slot to care for the plant (0-7): ";
        if (!getIntInput(input, slot)) continue;

        if (slot >= 0 && slot < 8) {
            if (!garden.isSlotEmpty(slot)) break;
            std::cout << "There is no plant in this slot. Returning to menu.\n";
            return;
        }
        std::cout << "Slot is invalid. Please choose a slot between 0 and 7.\n";
    }

    int water, fertilizer, light;

    while (true) {
        std::cout << "Enter the amount of water to add : ";
        if (getIntInput(input, water) && water >= 0) break;
        if(water < 0)
            std::cout << "Invalid input. Water must be a non-negative number.\n";
    }

    while (true) {
        std::cout << "Enter the amount of fertilizer to add : ";
        if (getIntInput(input, fertilizer) && fertilizer >= 0) break;
        if(fertilizer < 0)
            std::cout << "Invalid input. Fertilizer must be a non-negative number.\n";
    }

    while (true) {
        std::cout << "Enter the amount of light to add : ";
        if (getIntInput(input, light) && light >= 0) break;
        if(light < 0)
            std::cout << "Invalid input. Light must be a non-negative number.\n";
    }

    garden.careForPlant(slot, water, fertilizer, light);
}

void addPlant(Garden& garden, std::istream& input) {
    int slot;

    while (true) {
        std::cout << "Choose a slot (0-7): ";

        if (getIntInput(input, slot)) {
            if (slot >= 0 && slot < 8 && garden.isSlotEmpty(slot)) {
                if (auto plant = selectPlant(input)) {
                    garden.addPlant(plant, slot);
                }
                break;
            }
            std::cout << "Slot is already occupied or invalid.\n";
        } else {
            continue;
        }
    }
}

void calculateHealthIndex(const Garden& garden, std::istream& input) {
    int slot;
    while (true) {
        std::cout << "Choose a slot of a plant you want to check (0-7): ";
        if (!getIntInput(input, slot)) continue;

        if (slot >= 0 && slot < 8) {
            if (!garden.isSlotEmpty(slot)) break;
            std::cout << "There is no plant in this slot. Returning to menu.\n";
            return;
        }
        std::cout << "Slot is invalid. Please choose a slot between 0 and 7.\n";
    }
    double healthIndex = garden.calculateHealthIndex(slot);
    std::cout << "Health Index of Plant in Slot " << slot << ": " << healthIndex << "%\n";
}

void displaySelectedPlantNeeds(std::istream& input) {
    int option;
    std::cout << "Choose the type of plant you want to see details for:\n";
    std::cout << "1. Lavender\n";
    std::cout << "2. Orchid\n";
    std::cout << "3. Hibiscus\n";
    std::cout << "4. Lily\n";
    std::cout << "5. AloeVera\n";
    std::cout << "6. Cactus\n";
    std::cout << "7. Flytrap\n";
    std::cout << "8. Bonsai\n";
    std::cout << "Enter option: ";
    while (true) {
        if (getIntInput(input, option)) {
            switch (option) {
                case 1: {
                    Lavender lavender;
                    return lavender.display();
                }
                case 2: {
                    Orchid orchid;
                    return orchid.display();
                }
                case 3: {
                    Hibiscus hibiscus;
                    return hibiscus.display();
                }
                case 4: {
                    Lily lily;
                    return lily.display();
                }
                case 5: {
                    AloeVera aloeVera;
                    return aloeVera.display();
                }
                case 6: {
                    Cactus cactus;
                    return cactus.display();
                }
                case 7: {
                    Flytrap flytrap;
                    return flytrap.display();
                }
                case 8: {
                    Bonsai bonsai;
                    return bonsai.display();
                }
                default:
                    std::cout << "Invalid option! Please select a number between 1 and 8.\n";
                break;
            }
        }
    }
}