/// Plant.cpp
#include "Plant.h"

Plant::Plant(std::string name, const int water, const int fertilizer, const int light)
        : name(std::move(name)), water_needed(water), fertilizer_needed(fertilizer),
          light_needed(light), current_water(water), current_fertilizer(fertilizer), current_light(light) {}

const std::string& Plant::getName() const {
    return name;
}

void Plant::care(const int water, const int fertilizer, const int light) {
    current_water += water;
    current_fertilizer += fertilizer;
    current_light += light;
    std::cout << name << " has been cared for.\n";
}

bool Plant::update() {
    current_water -= 10;
    current_fertilizer -= 2;
    current_light -= 1;

    if (current_water < water_needed / 2 || current_fertilizer < fertilizer_needed / 2 || current_light < light_needed / 2) {
        std::cout << name << " has died due to lack of care.\n";
        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const Plant& plant) {
    os << "Plant: " << plant.name << "\n"
       << " Current Water: " << plant.current_water << "/" << plant.water_needed << "\n"
       << " Current Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
       << " Current Light: " << plant.current_light << "/" << plant.light_needed << "\n";

    return os;
}

Flowering::Flowering(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Tropical::Tropical(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Cacti::Cacti(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Exotic::Exotic(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Lavender::Lavender() : Flowering("Lavender", 30, 20, 70) {}
Orchid::Orchid() : Flowering("Orchid", 80, 50, 50) {}
Hibiscus::Hibiscus() : Tropical("Hibiscus", 70, 30, 80) {}
Lily::Lily() : Tropical("Lily", 65, 40, 85) {}
AloeVera::AloeVera() : Cacti("AloeVera", 20, 5, 80) {}
Cactus::Cactus() : Cacti("Cactus", 10, 5, 90) {}
Flytrap::Flytrap() : Exotic("Flytrap", 30, 30, 30) {}
Bonsai::Bonsai() : Exotic("Bonsai", 30, 50, 30) {}