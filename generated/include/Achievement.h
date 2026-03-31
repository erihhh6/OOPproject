/// Achievement.h
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <iostream>
#include <array>
#include <string>
#include <Subject.h>

/// Identifiers for every achievement the player can unlock
enum class AchievementType {
    FIRST_PLANT,        ///< Added the first plant ever
    DEDICATED_GARDENER, ///< Added 5 plants in total
    GARDEN_MASTER,      ///< Added 10 plants in total
    CARETAKER,          ///< Cared for plants 10 times
    NURTURING_HAND,     ///< Cared for plants 50 times
    SEASONAL_SURVIVOR,  ///< Survived 10 days
    DECADE_GARDENER,    ///< Survived 30 days
    LOSS_ACCEPTED,      ///< Lost the first plant
    RESILIENT,          ///< Lost 5 plants and kept going
    COUNT               ///< Sentinel — do not use as an actual achievement
};

/// Tracks player statistics and unlocks achievements via the Observer pattern
class Achievement final : public Observer {
private:
    static int totalPlantsAdded;
    static int totalPlantsCared;
    static int daysSurvived;
    static int totalPlantsLost;

    static std::array<bool, static_cast<int>(AchievementType::COUNT)> achievementUnlocked;

    [[nodiscard]] static const char* getAchievementName(AchievementType type);
    [[nodiscard]] static const char* getAchievementDesc(AchievementType type);
    static void checkAndUnlock(AchievementType type, bool condition);

public:
    Achievement() = default;

    /// Direct stat incrementors (also called internally from update())
    static void incrementPlantsAdded();
    static void incrementPlantsCared();
    static void incrementDaysSurvived();
    static void incrementPlantsLost();

    /// Receives garden events, updates stats, and checks for new unlocks
    void update(GardenEvent event) override;

    friend std::ostream& operator<<(std::ostream& os, const Achievement& achievement);
};

#endif /// ACHIEVEMENT_H
