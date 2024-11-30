/// Achievement.cpp
#include "Achievement.h"

Achievement::Achievement() : totalPlantsAdded(0), totalPlantsCared(0), daysSurvived(0) {}

void Achievement::incrementPlantsAdded() {
    totalPlantsAdded++;
}

void Achievement::incrementPlantsCared() {
    totalPlantsCared++;
}

void Achievement::incrementDaysSurvived() {
    daysSurvived++;
}

std::ostream& operator<<(std::ostream& os, const Achievement& achievement) {
    os << "\nAchievements:\n";
    os << " Total Plants Added: " << achievement.totalPlantsAdded << "\n";
    os << " Total Plants Cared For: " << achievement.totalPlantsCared << "\n";
    os << " Total Days Survived: " << achievement.daysSurvived << "\n";
    return os;
}