///functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <memory>
#include "Garden.h"
#include "Plant.h"

/// Function to validate integer input from a stream
bool getIntInput(std::istream& input, int& value);

/// Function to select a plant based on user input
std::shared_ptr<Plant> selectPlant(std::istream& input);

/// Function to care for a plant based on user input
void careForPlant(const Garden& garden, std::istream& input);

/// Function to add a plant based on user input
void addPlant(Garden& garden, std::istream& input);

/// Function to calculate and display the health index of a plant
void calculateHealthIndex(const Garden& garden, std::istream& input);

/// Function to display the plant needs of a selected plant
void displaySelectedPlantNeeds(std::istream& input);

#endif ///FUNCTIONS_H