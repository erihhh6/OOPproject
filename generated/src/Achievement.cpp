/// Achievement.cpp
#include "Achievement.h"

int Achievement::totalPlantsAdded = 0;
int Achievement::totalPlantsCared = 0;
int Achievement::daysSurvived = 0;

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
    os << " Total Plants Added: " << Achievement::totalPlantsAdded << "\n";
    os << " Total Plants Cared For: " << Achievement::totalPlantsCared << "\n";
    os << " Total Days Survived: " << Achievement::daysSurvived << "\n";
    return os;
}