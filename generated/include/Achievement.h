/// Achievement.h
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <iostream>

class Achievement {
private:
    int totalPlantsCared;
    int daysSurvived;

public:
    /// Constructor to initialize achievements
    Achievement();

    /// Increment the number of plants cared for
    void incrementPlantsCared();

    /// Increment the number of days survived
    void incrementDaysSurvived();

    /// Overloaded << operator to display achievements
    friend std::ostream& operator<<(std::ostream& os, const Achievement& achievement);
};

#endif // ACHIEVEMENT_H