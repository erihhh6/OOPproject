#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include "Plant.h"

class PlantFactory {
public:
    static std::shared_ptr<Plant> createPlant(const std::string& plantType);
};

#endif ///PLANTFACTORY_H
