/// functions.cpp
#include <functions.h>
#include <limits>
#include <PlantFactory.h>
#include <CustomExceptions.h>

bool getIntInput(std::istream& input, int& value) {
    input >> value;
    if (input.fail()) {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

std::shared_ptr<Plant> selectPlant(std::istream& input) {
    static const char* names[] = {
        "Lavender", "Orchid", "Hibiscus", "Lily",
        "AloeVera", "Cactus", "Flytrap",  "Bonsai"
    };
    static const char* types[] = {
        "Flowering", "Flowering", "Tropical", "Tropical",
        "Cacti",     "Cacti",     "Exotic",   "Exotic"
    };

    std::cout << "Choose the type of plant to add:\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << "  " << (i + 1) << ". " << names[i]
                  << " (" << types[i] << ")\n";
    }
    std::cout << "Enter option: ";

    int option;
    while (true) {
        if (getIntInput(input, option) && option >= 1 && option <= 8) {
            return PlantFactory::createPlant(names[option - 1]);
        }
        std::cout << "Invalid option. Please select 1-8: ";
    }
}

void careForPlant(Garden& garden, std::istream& input) {
    int slot;
    while (true) {
        try {
            std::cout << "Choose a slot to care for (0-7): ";
            if (!getIntInput(input, slot)) throw InvalidInputException();
            if (slot >= 0 && slot < MAX_SLOTS && !garden.isSlotEmpty(slot)) break;
            throw InvalidSlotException();
        } catch (const GameException& e) {
            std::cerr << e.what() << "\n";
        }
    }

    int water = 0, fertilizer = 0, light = 0;

    while (true) {
        std::cout << "Water to add: ";
        if (getIntInput(input, water) && water >= 0) break;
        std::cout << "Water must be >= 0.\n";
    }
    while (true) {
        std::cout << "Fertilizer to add: ";
        if (getIntInput(input, fertilizer) && fertilizer >= 0) break;
        std::cout << "Fertilizer must be >= 0.\n";
    }
    while (true) {
        std::cout << "Light to add: ";
        if (getIntInput(input, light) && light >= 0) break;
        std::cout << "Light must be >= 0.\n";
    }

    garden.careForPlant(slot, water, fertilizer, light);
}

void addPlant(Garden& garden, std::istream& input) {
    int slot;
    while (true) {
        std::cout << "Choose an empty slot (0-7): ";
        if (getIntInput(input, slot)) {
            if (slot >= 0 && slot < MAX_SLOTS && garden.isSlotEmpty(slot)) {
                auto plant = selectPlant(input);
                garden.addPlant(plant->getName(), slot);
                return;
            }
            std::cout << "Slot is occupied or out of range.\n";
        }
    }
}

void calculateHealthIndex(Garden& garden, std::istream& input) {
    int slot;
    while (true) {
        std::cout << "Choose a slot (0-7): ";
        if (!getIntInput(input, slot)) continue;
        if (slot >= 0 && slot < MAX_SLOTS) {
            if (!garden.isSlotEmpty(slot)) break;
            std::cout << "No plant in that slot.\n";
            return;
        }
        std::cout << "Invalid slot. Choose 0-7.\n";
    }
    const double health = garden.calculateHealthIndex(slot);
    std::cout << "Health Index of slot " << slot << ": " << static_cast<int>(health) << "%\n";
}

/// Uses PlantFactory to get a temporary plant instance and prints its static needs.
/// This avoids duplicating hardcoded values outside of the plant constructors.
void displaySelectedPlantNeeds(std::istream& input) {
    static const char* names[] = {
        "Lavender", "Orchid", "Hibiscus", "Lily",
        "AloeVera", "Cactus", "Flytrap",  "Bonsai"
    };

    std::cout << "Choose a plant to see its needs:\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << "  " << (i + 1) << ". " << names[i] << "\n";
    }
    std::cout << "Enter option: ";

    int option;
    while (true) {
        if (getIntInput(input, option) && option >= 1 && option <= 8) {
            PlantFactory::createPlant(names[option - 1])->display();
            return;
        }
        std::cout << "Invalid option. Please select 1-8: ";
    }
}
