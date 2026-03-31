/// Garden.cpp
#include <Garden.h>
#include <PlantFactory.h>
#include <CustomExceptions.h>
#include <fstream>
#include <sstream>
#include <algorithm>

// ---------------------------------------------------------------------------
// Constructors / assignment / swap
// ---------------------------------------------------------------------------

Garden::Garden() {
    for (auto& slot : slots) slot = nullptr;
}

Garden::Garden(const Garden& other) : Subject(other) {
    currentDay    = other.currentDay;
    currentSeason = other.currentSeason;
    for (int i = 0; i < capacity; ++i) {
        slots[i] = other.slots[i] ? other.slots[i]->clone() : nullptr;
    }
}

Garden& Garden::operator=(Garden other) {
    swap(*this, other);
    return *this;
}

void swap(Garden& first, Garden& second) noexcept {
    using std::swap;
    swap(first.currentDay,    second.currentDay);
    swap(first.currentSeason, second.currentSeason);
    for (int i = 0; i < Garden::capacity; ++i) {
        swap(first.slots[i], second.slots[i]);
    }
    // observers_ is intentionally NOT swapped: the logical garden keeps its listeners
}

// ---------------------------------------------------------------------------
// Season helpers
// ---------------------------------------------------------------------------

Season Garden::seasonFromDay(int day) const {
    return static_cast<Season>((day / DAYS_PER_SEASON) % 4);
}

const char* Garden::seasonName(Season season) {
    switch (season) {
        case Season::SPRING: return "Spring";
        case Season::SUMMER: return "Summer";
        case Season::AUTUMN: return "Autumn";
        case Season::WINTER: return "Winter";
    }
    return "Unknown";
}

int    Garden::getCurrentDay()    const { return currentDay; }
Season Garden::getCurrentSeason() const { return currentSeason; }

// ---------------------------------------------------------------------------
// Game actions
// ---------------------------------------------------------------------------

void Garden::addPlant(const std::string& plantType, int slot) {
    if (slot < 0 || slot >= capacity) throw InvalidSlotException();
    if (!isSlotEmpty(slot))           throw InvalidSlotException();

    auto plant  = PlantFactory::createPlant(plantType); // throws InvalidPlantTypeException on bad type
    slots[slot] = plant->clone();
    slots[slot]->addHistory("Day " + std::to_string(currentDay) +
                            ": Added to slot " + std::to_string(slot));
    std::cout << "Plant " << plant->getName()
              << " added to slot " << slot << ".\n";
    notifyObservers(GardenEvent::PLANT_ADDED);
}

void Garden::careForPlant(int slot, int water, int fertilizer, int light) {
    if (slot < 0 || slot >= capacity || isSlotEmpty(slot)) throw InvalidSlotException();

    slots[slot]->care(water, fertilizer, light);
    slots[slot]->addHistory("Day " + std::to_string(currentDay) +
                            ": Cared for (water +" + std::to_string(water) +
                            ", fertilizer +"       + std::to_string(fertilizer) +
                            ", light +"            + std::to_string(light) + ")");
    notifyObservers(GardenEvent::PLANT_CARED);
}

void Garden::applyGeneralCare() {
    for (int i = 0; i < capacity; ++i) {
        if (!slots[i]) continue;

        if (const auto fl = std::dynamic_pointer_cast<Flowering>(slots[i])) {
            std::cout << "Applying Flowering care to slot " << i << ".\n";
            fl->care(10, 5, 10);
        } else if (const auto tr = std::dynamic_pointer_cast<Tropical>(slots[i])) {
            std::cout << "Applying Tropical care to slot " << i << ".\n";
            tr->care(15, 10, 5);
        } else if (const auto ca = std::dynamic_pointer_cast<Cacti>(slots[i])) {
            std::cout << "Applying Cacti care to slot " << i << ".\n";
            ca->care(5, 2, 20);
        } else if (const auto ex = std::dynamic_pointer_cast<Exotic>(slots[i])) {
            std::cout << "Applying Exotic care to slot " << i << ".\n";
            ex->care(8, 4, 12);
        }
        slots[i]->addHistory("Day " + std::to_string(currentDay) + ": General care applied");
        notifyObservers(GardenEvent::PLANT_CARED);
    }
}

int Garden::updatePlants() {
    ++currentDay;
    currentSeason = seasonFromDay(currentDay);

    int plantsDied = 0;
    for (int i = 0; i < capacity; ++i) {
        if (!slots[i]) continue;

        if (slots[i]->update(currentSeason, currentDay)) {
            slots[i] = nullptr;
            std::cout << "  Slot " << i << " is now empty.\n";
            ++plantsDied;
            notifyObservers(GardenEvent::PLANT_DIED);
        }
    }

    notifyObservers(GardenEvent::DAY_PASSED);

    std::cout << "--- Day " << currentDay
              << " | Season: " << seasonName(currentSeason) << " ---\n";
    return plantsDied;
}

double Garden::calculateHealthIndex(int slot) const {
    if (slot < 0 || slot >= capacity || isSlotEmpty(slot)) return 0.0;
    return slots[slot]->calculateHealthIndex();
}

bool Garden::isSlotEmpty(int slot) const {
    return slot >= 0 && slot < capacity && !slots[slot];
}

// ---------------------------------------------------------------------------
// Save / Load
// ---------------------------------------------------------------------------

void Garden::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for saving: " << filename << "\n";
        return;
    }
    file << currentDay << "\n";
    for (int i = 0; i < capacity; ++i) {
        if (!slots[i]) continue;
        file << slots[i]->getName()               << "|"
             << i                                  << "|"
             << slots[i]->getCurrentWater()        << "|"
             << slots[i]->getCurrentFertilizer()   << "|"
             << slots[i]->getCurrentLight()        << "|"
             << static_cast<int>(slots[i]->getGrowthStage()) << "|"
             << slots[i]->getConsecutiveHealthyDays() << "\n";
    }
    std::cout << "Garden saved to \"" << filename << "\".\n";
}

Garden Garden::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for loading: " << filename << "\n";
        return Garden{};
    }

    Garden garden;
    std::string line;

    // First line: day counter
    if (std::getline(file, line)) {
        garden.currentDay    = std::stoi(line);
        garden.currentSeason = garden.seasonFromDay(garden.currentDay);
    }

    // Subsequent lines: one plant per line
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string nameStr, slotStr, wStr, fStr, lStr, gsStr, hdStr;

        if (!std::getline(ss, nameStr, '|')) continue;
        if (!std::getline(ss, slotStr, '|')) continue;
        if (!std::getline(ss, wStr,    '|')) continue;
        if (!std::getline(ss, fStr,    '|')) continue;
        if (!std::getline(ss, lStr,    '|')) continue;
        if (!std::getline(ss, gsStr,   '|')) continue;
        if (!std::getline(ss, hdStr,   '|')) continue;

        const int slot = std::stoi(slotStr);
        if (slot < 0 || slot >= MAX_SLOTS) continue;

        auto plant = PlantFactory::createPlant(nameStr);
        plant->restoreState(std::stoi(wStr), std::stoi(fStr), std::stoi(lStr),
                            static_cast<GrowthStage>(std::stoi(gsStr)),
                            std::stoi(hdStr));
        garden.slots[slot] = std::move(plant);
    }

    std::cout << "Garden loaded from \"" << filename << "\" (day " << garden.currentDay << ").\n";
    return garden;
}

// ---------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Garden& garden) {
    os << "=== Garden — Day " << garden.currentDay
       << " | " << Garden::seasonName(garden.currentSeason) << " ===\n";

    for (int i = 0; i < Garden::capacity; ++i) {
        os << "Slot " << i << ": ";
        if (!garden.slots[i]) {
            os << "empty\n";
            continue;
        }
        os << "\n" << *garden.slots[i];

        // Show the last 3 history entries
        const auto& hist = garden.slots[i]->getHistory();
        if (!hist.empty()) {
            const int start = std::max(0, static_cast<int>(hist.size()) - 3);
            os << "    Log:\n";
            for (int j = start; j < static_cast<int>(hist.size()); ++j) {
                os << "      " << hist[j] << "\n";
            }
        }
        os << "\n";
    }
    return os;
}
