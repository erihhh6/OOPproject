/// Achievement.h
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <iostream>
#include <Subject.h>

class Achievement final : public Observer{
private:
    /// Static member for cumulative tracking
    static int totalPlantsAdded;
    static int totalPlantsCared;
    static int daysSurvived;

public:
    /// Constructor to initialize achievements
    Achievement() = default;

    /// Increment the number of plants added
    static void incrementPlantsAdded();

    /// Increment the number of plants cared for
    static void incrementPlantsCared();

    /// Increment the number of days survived
    static void incrementDaysSurvived();

    /// Overridden update function from the observer class
    void update() override;

    /// Overloaded << operator to display achievements
    friend std::ostream& operator<<(std::ostream& os, const Achievement& achievement);
};

#endif /// ACHIEVEMENT_H