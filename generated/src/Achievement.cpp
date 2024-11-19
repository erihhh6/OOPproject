/// Achievement.cpp
#include "Achievement.h"

Achievement::Achievement() : totalPlantsCared(0), daysSurvived(0) {}

void Achievement::incrementPlantsCared() {
    totalPlantsCared++;
}

void Achievement::incrementDaysSurvived() {
    daysSurvived++;
}

std::ostream& operator<<(std::ostream& os, const Achievement& achievement) {
    os << "\nAchievements:\n";
    os << " Total Plants Cared For: " << achievement.totalPlantsCared << "\n";
    os << " Total Days Survived: " << achievement.daysSurvived << "\n";
    return os;
}