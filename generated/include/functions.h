/// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <memory>
#include <Garden.h>
#include <Plant.h>
#include <constants.h>

/// Reads one integer from the stream; clears the stream on failure and returns false
bool getIntInput(std::istream& input, int& value);

/// Presents a plant-type menu and returns a freshly created plant via PlantFactory
std::shared_ptr<Plant> selectPlant(std::istream& input);

/// Prompts for slot + resources and delegates to Garden::careForPlant
void careForPlant(Garden& garden, std::istream& input);

/// Prompts for slot + plant type and delegates to Garden::addPlant
void addPlant(Garden& garden, std::istream& input);

/// Prompts for a slot and prints that plant's current health index
void calculateHealthIndex(Garden& garden, std::istream& input);

/// Prints the static needs (water/fertilizer/light) for a user-selected plant type
void displaySelectedPlantNeeds(std::istream& input);

/// Prints a generic garden message of any printable type (template utility)
template <typename T>
void printGardenMessage(const T& message) {
    std::cout << "Garden Message: " << message;
}

#endif /// FUNCTIONS_H
