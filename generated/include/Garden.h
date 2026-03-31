/// Garden.h
#ifndef GARDEN_H
#define GARDEN_H

#include <memory>
#include <string>
#include <Plant.h>
#include <Subject.h>
#include <constants.h>

/// Manages up to MAX_SLOTS plant slots, tracks day/season, and emits Observer events
class Garden : public Subject {
private:
    std::shared_ptr<Plant> slots[MAX_SLOTS];
    static constexpr int capacity = MAX_SLOTS;

    int    currentDay{0};
    Season currentSeason{Season::SPRING};

    /// Maps a day number to the corresponding Season
    [[nodiscard]] Season seasonFromDay(int day) const;

public:
    Garden();
    Garden(const Garden& other);
    Garden& operator=(Garden other);
    friend void swap(Garden& first, Garden& second) noexcept;

    /// Places a new plant (by type name) into an empty slot
    void addPlant(const std::string& plantType, int slot);

    /// Applies specified resources to the plant in the given slot
    void careForPlant(int slot, int water, int fertilizer, int light);

    /// Applies type-differentiated care to every occupied slot
    void applyGeneralCare();

    /// Advances one day: applies decay, removes dead plants, updates season.
    /// @return number of plants that died this day
    [[nodiscard]] int updatePlants();

    /// Returns the health index of the plant in the given slot
    [[nodiscard]] double calculateHealthIndex(int slot) const;

    /// Returns true when slot is valid and unoccupied
    [[nodiscard]] bool isSlotEmpty(int slot) const;

    [[nodiscard]] int    getCurrentDay()    const;
    [[nodiscard]] Season getCurrentSeason() const;

    /// Returns a human-readable season name
    [[nodiscard]] static const char* seasonName(Season season);

    /// Serialises garden state to a simple pipe-delimited text file
    void saveToFile(const std::string& filename) const;

    /// Deserialises garden state from a previously saved file
    [[nodiscard]] static Garden loadFromFile(const std::string& filename);

    friend std::ostream& operator<<(std::ostream& os, const Garden& garden);
};

#endif /// GARDEN_H
