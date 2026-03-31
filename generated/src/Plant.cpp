/// Plant.cpp
#include <Plant.h>
#include <algorithm>
#include <cmath>

// ---------------------------------------------------------------------------
// Base Plant
// ---------------------------------------------------------------------------

Plant::Plant(std::string name, const int water, const int fertilizer, const int light)
    : name(std::move(name)), water_needed(water), fertilizer_needed(fertilizer),
      light_needed(light), current_water(water), current_fertilizer(fertilizer),
      current_light(light) {}

// --- Getters ---
const std::string& Plant::getName()             const { return name; }
int  Plant::getWaterNeeded()                    const { return water_needed; }
int  Plant::getFertilizerNeeded()               const { return fertilizer_needed; }
int  Plant::getLightNeeded()                    const { return light_needed; }
int  Plant::getCurrentWater()                   const { return current_water; }
int  Plant::getCurrentFertilizer()              const { return current_fertilizer; }
int  Plant::getCurrentLight()                   const { return current_light; }
GrowthStage Plant::getGrowthStage()             const { return stage; }
int  Plant::getConsecutiveHealthyDays()         const { return consecutiveHealthyDays; }
const std::vector<std::string>& Plant::getHistory() const { return history; }

// --- Protected ratio helpers ---
double Plant::calculateWaterRatio()      const { return static_cast<double>(current_water)      / water_needed; }
double Plant::calculateFertilizerRatio() const { return static_cast<double>(current_fertilizer) / fertilizer_needed; }
double Plant::calculateLightRatio()      const { return static_cast<double>(current_light)      / light_needed; }

// --- Default decay rates (overridden by each intermediate class) ---
DecayRates Plant::getDecayRates() const {
    return {DAILY_WATER_DECAY, DAILY_FERTILIZER_DECAY, DAILY_LIGHT_DECAY};
}

// --- State restoration (for save / load) ---
void Plant::restoreState(int water, int fertilizer, int light,
                         GrowthStage gs, int healthyDays) {
    current_water      = water;
    current_fertilizer = fertilizer;
    current_light      = light;
    stage              = gs;
    consecutiveHealthyDays = healthyDays;
}

void Plant::addHistory(const std::string& entry) {
    history.push_back(entry);
}

// --- Care (capped at 2× the plant's need to prevent infinite stacking) ---
void Plant::care(const int water, const int fertilizer, const int light) {
    current_water      = std::min(current_water      + water,      water_needed      * 2);
    current_fertilizer = std::min(current_fertilizer + fertilizer, fertilizer_needed * 2);
    current_light      = std::min(current_light      + light,      light_needed      * 2);
    std::cout << name << " has been cared for.\n";
}

// --- Growth stage advancement ---
static const char* growthStageName(GrowthStage s) {
    switch (s) {
        case GrowthStage::SEEDLING: return "Seedling";
        case GrowthStage::GROWING:  return "Growing";
        case GrowthStage::MATURE:   return "Mature";
        case GrowthStage::BLOOMING: return "Blooming";
    }
    return "Unknown";
}

void Plant::updateGrowthStage() {
    if (stage == GrowthStage::BLOOMING) return;

    if (calculateHealthIndex() >= GROWTH_HEALTH_THRESHOLD) {
        ++consecutiveHealthyDays;

        int threshold = 0;
        switch (stage) {
            case GrowthStage::SEEDLING: threshold = DAYS_TO_GROW_SEEDLING; break;
            case GrowthStage::GROWING:  threshold = DAYS_TO_GROW_GROWING;  break;
            case GrowthStage::MATURE:   threshold = DAYS_TO_GROW_MATURE;   break;
            default: return;
        }

        if (consecutiveHealthyDays >= threshold) {
            stage = static_cast<GrowthStage>(static_cast<int>(stage) + 1);
            consecutiveHealthyDays = 0;
            std::cout << name << " advanced to " << growthStageName(stage) << " stage!\n";
        }
    } else {
        consecutiveHealthyDays = 0;
    }
}

// --- Daily update with season-adjusted decay ---
bool Plant::update(Season season, int day) {
    DecayRates rates = getDecayRates();

    double waterMult = 1.0, fertMult = 1.0, lightMult = 1.0;
    switch (season) {
        case Season::SUMMER: waterMult = 1.5; lightMult = 0.5; break;
        case Season::WINTER: waterMult = 0.5; lightMult = 2.0; break;
        case Season::SPRING:
        case Season::AUTUMN:
        default: break;
    }

    current_water      -= static_cast<int>(std::round(rates.water      * waterMult));
    current_fertilizer -= static_cast<int>(std::round(rates.fertilizer * fertMult));
    current_light      -= static_cast<int>(std::round(rates.light      * lightMult));

    current_water      = std::max(0, current_water);
    current_fertilizer = std::max(0, current_fertilizer);
    current_light      = std::max(0, current_light);

    const bool waterCritical      = current_water      < static_cast<int>(water_needed      * DEATH_RATIO);
    const bool fertilizerCritical = current_fertilizer < static_cast<int>(fertilizer_needed * DEATH_RATIO);
    const bool lightCritical      = current_light      < static_cast<int>(light_needed      * DEATH_RATIO);

    if (waterCritical || fertilizerCritical || lightCritical) {
        addHistory("Day " + std::to_string(day) + ": Died from lack of care.");
        std::cout << name << " has died due to lack of care.\n";
        return true;
    }

    updateGrowthStage();
    addHistory("Day " + std::to_string(day) + ": Day passed. Health: " +
               std::to_string(static_cast<int>(calculateHealthIndex())) + "%");
    return false;
}

std::ostream& operator<<(std::ostream& os, const Plant& plant) {
    os << "  Plant: " << plant.name
       << " [" << growthStageName(plant.stage) << "]\n"
       << "    Water:      " << plant.current_water      << "/" << plant.water_needed      << "\n"
       << "    Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
       << "    Light:      " << plant.current_light      << "/" << plant.light_needed      << "\n"
       << "    Health:     " << static_cast<int>(plant.calculateHealthIndex()) << "%\n";
    return os;
}

// ---------------------------------------------------------------------------
// Intermediate classes — constructors + category decay rates
// ---------------------------------------------------------------------------

Flowering::Flowering(const std::string& name, int water, int fertilizer, int light)
    : Plant(name, water, fertilizer, light) {}
DecayRates Flowering::getDecayRates() const { return {8, 3, 2}; }

Tropical::Tropical(const std::string& name, int water, int fertilizer, int light)
    : Plant(name, water, fertilizer, light) {}
DecayRates Tropical::getDecayRates() const { return {12, 5, 2}; }

Cacti::Cacti(const std::string& name, int water, int fertilizer, int light)
    : Plant(name, water, fertilizer, light) {}
DecayRates Cacti::getDecayRates() const { return {1, 1, 5}; }

Exotic::Exotic(const std::string& name, int water, int fertilizer, int light)
    : Plant(name, water, fertilizer, light) {}
DecayRates Exotic::getDecayRates() const { return {8, 10, 4}; }

// ---------------------------------------------------------------------------
// Lavender  (Flowering | water=30, fertilizer=20, light=70)
// Health weights: 0.4 + 0.3 + 0.3 = 1.0
// ---------------------------------------------------------------------------
Lavender::Lavender() : Flowering("Lavender", 30, 20, 70) {}
std::shared_ptr<Plant> Lavender::clone() const { return std::make_shared<Lavender>(*this); }
double Lavender::calculateHealthIndex() const {
    return (0.4 * calculateWaterRatio() + 0.3 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void Lavender::doDisplay() const {
    std::cout << "Lavender:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Orchid  (Flowering | water=80, fertilizer=50, light=50)
// Health weights: 0.5 + 0.2 + 0.3 = 1.0
// Decay override: higher water & fertilizer loss than generic Flowering
// ---------------------------------------------------------------------------
Orchid::Orchid() : Flowering("Orchid", 80, 50, 50) {}
std::shared_ptr<Plant> Orchid::clone() const { return std::make_shared<Orchid>(*this); }
double Orchid::calculateHealthIndex() const {
    return (0.5 * calculateWaterRatio() + 0.2 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
DecayRates Orchid::getDecayRates() const { return {15, 8, 3}; }
void Orchid::doDisplay() const {
    std::cout << "Orchid:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Hibiscus  (Tropical | water=70, fertilizer=30, light=80)
// Health weights: 0.4 + 0.3 + 0.3 = 1.0
// ---------------------------------------------------------------------------
Hibiscus::Hibiscus() : Tropical("Hibiscus", 70, 30, 80) {}
std::shared_ptr<Plant> Hibiscus::clone() const { return std::make_shared<Hibiscus>(*this); }
double Hibiscus::calculateHealthIndex() const {
    return (0.4 * calculateWaterRatio() + 0.3 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void Hibiscus::doDisplay() const {
    std::cout << "Hibiscus:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Lily  (Tropical | water=65, fertilizer=40, light=85)
// Health weights: 0.4 + 0.3 + 0.3 = 1.0
// ---------------------------------------------------------------------------
Lily::Lily() : Tropical("Lily", 65, 40, 85) {}
std::shared_ptr<Plant> Lily::clone() const { return std::make_shared<Lily>(*this); }
double Lily::calculateHealthIndex() const {
    return (0.4 * calculateWaterRatio() + 0.3 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void Lily::doDisplay() const {
    std::cout << "Lily:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// AloeVera  (Cacti | water=20, fertilizer=5, light=80)
// Health weights: 0.5 + 0.2 + 0.3 = 1.0
// ---------------------------------------------------------------------------
AloeVera::AloeVera() : Cacti("AloeVera", 20, 5, 80) {}
std::shared_ptr<Plant> AloeVera::clone() const { return std::make_shared<AloeVera>(*this); }
double AloeVera::calculateHealthIndex() const {
    return (0.5 * calculateWaterRatio() + 0.2 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void AloeVera::doDisplay() const {
    std::cout << "AloeVera:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Cactus  (Cacti | water=10, fertilizer=5, light=90)
// Health weights: 0.2 + 0.3 + 0.5 = 1.0  (light is most critical)
// ---------------------------------------------------------------------------
Cactus::Cactus() : Cacti("Cactus", 10, 5, 90) {}
std::shared_ptr<Plant> Cactus::clone() const { return std::make_shared<Cactus>(*this); }
double Cactus::calculateHealthIndex() const {
    return (0.2 * calculateWaterRatio() + 0.3 * calculateFertilizerRatio() + 0.5 * calculateLightRatio()) * 100.0;
}
void Cactus::doDisplay() const {
    std::cout << "Cactus:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Flytrap  (Exotic | water=30, fertilizer=30, light=30)
// Health weights: 0.4 + 0.3 + 0.3 = 1.0
// ---------------------------------------------------------------------------
Flytrap::Flytrap() : Exotic("Flytrap", 30, 30, 30) {}
std::shared_ptr<Plant> Flytrap::clone() const { return std::make_shared<Flytrap>(*this); }
double Flytrap::calculateHealthIndex() const {
    return (0.4 * calculateWaterRatio() + 0.3 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void Flytrap::doDisplay() const {
    std::cout << "Flytrap:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}

// ---------------------------------------------------------------------------
// Bonsai  (Exotic | water=30, fertilizer=50, light=30)
// Health weights: 0.3 + 0.4 + 0.3 = 1.0  (fertilizer is most critical)
// ---------------------------------------------------------------------------
Bonsai::Bonsai() : Exotic("Bonsai", 30, 50, 30) {}
std::shared_ptr<Plant> Bonsai::clone() const { return std::make_shared<Bonsai>(*this); }
double Bonsai::calculateHealthIndex() const {
    return (0.3 * calculateWaterRatio() + 0.4 * calculateFertilizerRatio() + 0.3 * calculateLightRatio()) * 100.0;
}
void Bonsai::doDisplay() const {
    std::cout << "Bonsai:\n"
              << "  Water needed:      " << getWaterNeeded()      << "\n"
              << "  Fertilizer needed: " << getFertilizerNeeded() << "\n"
              << "  Light needed:      " << getLightNeeded()      << "\n";
}
