/// Achievement.cpp
#include <Achievement.h>

// --- Static member definitions ---
int Achievement::totalPlantsAdded  = 0;
int Achievement::totalPlantsCared  = 0;
int Achievement::daysSurvived      = 0;
int Achievement::totalPlantsLost   = 0;

std::array<bool, static_cast<int>(AchievementType::COUNT)> Achievement::achievementUnlocked = {};

// --- Stat incrementors ---
void Achievement::incrementPlantsAdded()  { ++totalPlantsAdded; }
void Achievement::incrementPlantsCared()  { ++totalPlantsCared; }
void Achievement::incrementDaysSurvived() { ++daysSurvived; }
void Achievement::incrementPlantsLost()   { ++totalPlantsLost; }

// --- Achievement metadata ---
const char* Achievement::getAchievementName(AchievementType type) {
    switch (type) {
        case AchievementType::FIRST_PLANT:        return "Green Thumb";
        case AchievementType::DEDICATED_GARDENER: return "Dedicated Gardener";
        case AchievementType::GARDEN_MASTER:      return "Garden Master";
        case AchievementType::CARETAKER:          return "Caretaker";
        case AchievementType::NURTURING_HAND:     return "Nurturing Hand";
        case AchievementType::SEASONAL_SURVIVOR:  return "Seasonal Survivor";
        case AchievementType::DECADE_GARDENER:    return "Decade Gardener";
        case AchievementType::LOSS_ACCEPTED:      return "Loss Accepted";
        case AchievementType::RESILIENT:          return "Resilient";
        default:                                  return "Unknown";
    }
}

const char* Achievement::getAchievementDesc(AchievementType type) {
    switch (type) {
        case AchievementType::FIRST_PLANT:        return "Add your first plant";
        case AchievementType::DEDICATED_GARDENER: return "Add 5 plants in total";
        case AchievementType::GARDEN_MASTER:      return "Add 10 plants in total";
        case AchievementType::CARETAKER:          return "Care for plants 10 times";
        case AchievementType::NURTURING_HAND:     return "Care for plants 50 times";
        case AchievementType::SEASONAL_SURVIVOR:  return "Survive 10 days";
        case AchievementType::DECADE_GARDENER:    return "Survive 30 days";
        case AchievementType::LOSS_ACCEPTED:      return "Lose your first plant";
        case AchievementType::RESILIENT:          return "Lose 5 plants and keep gardening";
        default:                                  return "";
    }
}

void Achievement::checkAndUnlock(AchievementType type, bool condition) {
    const int idx = static_cast<int>(type);
    if (condition && !achievementUnlocked[idx]) {
        achievementUnlocked[idx] = true;
        std::cout << "*** Achievement Unlocked: "
                  << getAchievementName(type) << " — "
                  << getAchievementDesc(type) << " ***\n";
    }
}

// --- Observer update: route event → stat increment → check unlocks ---
void Achievement::update(GardenEvent event) {
    switch (event) {
        case GardenEvent::PLANT_ADDED: incrementPlantsAdded();  break;
        case GardenEvent::PLANT_CARED: incrementPlantsCared();  break;
        case GardenEvent::DAY_PASSED:  incrementDaysSurvived(); break;
        case GardenEvent::PLANT_DIED:  incrementPlantsLost();   break;
    }

    checkAndUnlock(AchievementType::FIRST_PLANT,        totalPlantsAdded  >= 1);
    checkAndUnlock(AchievementType::DEDICATED_GARDENER, totalPlantsAdded  >= 5);
    checkAndUnlock(AchievementType::GARDEN_MASTER,      totalPlantsAdded  >= 10);
    checkAndUnlock(AchievementType::CARETAKER,          totalPlantsCared  >= 10);
    checkAndUnlock(AchievementType::NURTURING_HAND,     totalPlantsCared  >= 50);
    checkAndUnlock(AchievementType::SEASONAL_SURVIVOR,  daysSurvived      >= 10);
    checkAndUnlock(AchievementType::DECADE_GARDENER,    daysSurvived      >= 30);
    checkAndUnlock(AchievementType::LOSS_ACCEPTED,      totalPlantsLost   >= 1);
    checkAndUnlock(AchievementType::RESILIENT,          totalPlantsLost   >= 5);
}

std::ostream& operator<<(std::ostream& os, const Achievement&) {
    os << "\n=== Achievements ===\n"
       << "  Plants Added:  " << Achievement::totalPlantsAdded  << "\n"
       << "  Plants Cared:  " << Achievement::totalPlantsCared  << "\n"
       << "  Days Survived: " << Achievement::daysSurvived      << "\n"
       << "  Plants Lost:   " << Achievement::totalPlantsLost   << "\n"
       << "\n  Progress:\n";

    for (int i = 0; i < static_cast<int>(AchievementType::COUNT); ++i) {
        const auto type = static_cast<AchievementType>(i);
        const char* status = Achievement::achievementUnlocked[i] ? "[X]" : "[ ]";
        os << "  " << status << " " << Achievement::getAchievementName(type)
           << " — " << Achievement::getAchievementDesc(type) << "\n";
    }
    return os;
}
