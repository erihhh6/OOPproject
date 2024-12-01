/// Garden.h
#ifndef GARDEN_H
#define GARDEN_H

#include <memory>
#include "Plant.h"
#include "Achievement.h"

class Garden {
private:
    std::shared_ptr<Plant> slots[8];
    static constexpr int capacity = 8;

public:
    /// Default constructor initializes all slots as empty
    Garden();

    /// Copy constructor
    Garden(const Garden& other);

    /// Assignment operator using copy-and-swap idiom
    Garden& operator=(Garden other);

    /// Swap function
    friend void swap(Garden& first, Garden& second) noexcept;

    /// Function to add a plant to a specific slot
    void addPlant(const std::shared_ptr<Plant>& plant,  int slot);

    /// Function to care for a specific plant in a slot
    void careForPlant(int slot,int water,int fertilizer,int light) const;

    /// Function to apply general care to all plants by specific conditions
    void applyGeneralCare(Achievement& achievements) const;

    /// Function to update all plants and remove dead ones.
    void updatePlants();

    /// Function to calculate health index for a plant in a given slot
    double calculateHealthIndex(int slot) const;

    /// Check if a specific slot is empty.
    [[nodiscard]] bool isSlotEmpty(int slot) const;

    /// Overloaded operator<< to display garden state.
    friend std::ostream& operator<<(std::ostream& os, const Garden& garden);
};

#endif /// GARDEN_H