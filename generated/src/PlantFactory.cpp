#include <PlantFactory.h>

std::shared_ptr<Plant> PlantFactory::createPlant(const std::string& plantType) {
    if (plantType == "Lavender") return std::make_shared<Lavender>();
    if (plantType == "Orchid") return std::make_shared<Orchid>();
    if (plantType == "Hibiscus") return std::make_shared<Hibiscus>();
    if (plantType == "Lily") return std::make_shared<Lily>();
    if (plantType == "AloeVera") return std::make_shared<AloeVera>();
    if (plantType == "Cactus") return std::make_shared<Cactus>();
    if (plantType == "Flytrap") return std::make_shared<Flytrap>();
    if (plantType == "Bonsai") return std::make_shared<Bonsai>();
    std::cerr << "Invalid plant type." << "\n"; return nullptr;
}