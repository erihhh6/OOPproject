#include "PlantFactory.h"

std::shared_ptr<Plant> PlantFactory::createPlant(const std::string& plantType) {
    if (plantType == "Lavender") return std::make_shared<Lavender>();
    else if (plantType == "Orchid") return std::make_shared<Orchid>();
    else if (plantType == "Hibiscus") return std::make_shared<Hibiscus>();
    else if (plantType == "Lily") return std::make_shared<Lily>();
    else if (plantType == "AloeVera") return std::make_shared<AloeVera>();
    else if (plantType == "Cactus") return std::make_shared<Cactus>();
    else if (plantType == "Flytrap") return std::make_shared<Flytrap>();
    else if (plantType == "Bonsai") return std::make_shared<Bonsai>();
    else {
        std::cerr << "Invalid plant type." << "\n";
        return nullptr;
    }
}