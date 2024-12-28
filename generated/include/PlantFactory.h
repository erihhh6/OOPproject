#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include <Plant.h>

/// Base PlantFactory class that creates plants based on the provided plant type
class PlantFactory {
public:
    /// Static method to create a plant based on the provided plant type and returns a shared pointer to the created plant
    static std::shared_ptr<Plant> createPlant(const std::string& plantType);
};

#endif ///PLANTFACTORY_H
