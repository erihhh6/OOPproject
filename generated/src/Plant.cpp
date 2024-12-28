/// Plant.cpp
#include <Plant.h>

Plant::Plant(std::string name, const int water, const int fertilizer, const int light)
        : name(std::move(name)), water_needed(water), fertilizer_needed(fertilizer),
          light_needed(light), current_water(water), current_fertilizer(fertilizer), current_light(light) {}

const std::string& Plant::getName() const {
    return name;
}

void Plant::care(const int water, const int fertilizer, const int light) {
    current_water += water;
    current_fertilizer += fertilizer;
    current_light += light;
    std::cout << name << " has been cared for.\n";
}

bool Plant::update() {
    current_water -= 10;
    current_fertilizer -= 2;
    current_light -= 1;

    if (current_water < water_needed / 2 || current_fertilizer < fertilizer_needed / 2 || current_light < light_needed / 2) {
        std::cout << name << " has died due to lack of care.\n";
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Plant& plant) {
    os << "Plant: " << plant.name << "\n"
       << " Current Water: " << plant.current_water << "/" << plant.water_needed << "\n"
       << " Current Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
       << " Current Light: " << plant.current_light << "/" << plant.light_needed << "\n";

    return os;
}

Flowering::Flowering(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Tropical::Tropical(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Cacti::Cacti(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Exotic::Exotic(const std::string& name, int water, int fertilizer, int light)
        : Plant(name, water, fertilizer, light) {}

Lavender::Lavender() : Flowering("Lavender", 30, 20, 70) {}

std::shared_ptr<Plant> Lavender::clone() const {
    return std::make_shared<Lavender>(*this);
}

double Lavender::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return (0.4 * waterRatio + 0.3 * fertilizerRatio + 0.1 * lightRatio) * 100;
}

void Lavender::doDisplay() const {
    std::cout<<"Lavender:\n"<<"Water needed : 30\n"<<"Fertilizer needed : 20\n"<<"Light needed : 70\n";
}

Orchid::Orchid() : Flowering("Orchid", 80, 50, 50) {}

std::shared_ptr<Plant> Orchid::clone() const {
    return std::make_shared<Orchid>(*this);
}

double Orchid::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return (0.5 * waterRatio + 0.2 * fertilizerRatio + 0.3 * lightRatio) * 100;
}

void Orchid::doDisplay() const {
    std::cout<<"Orchid:\n"<<"Water needed : 80\n"<<"Fertilizer needed : 50\n"<<"Light needed : 50\n";
}

Hibiscus::Hibiscus() : Tropical("Hibiscus", 70, 30, 80) {}

std::shared_ptr<Plant> Hibiscus::clone() const {
    return std::make_shared<Hibiscus>(*this);
}

double Hibiscus::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return (0.4 * waterRatio + 0.3 * fertilizerRatio + 0.3 * lightRatio) * 100;
}

void Hibiscus::doDisplay() const {
    std::cout<<"Hibiscus:\n"<<"Water needed : 70\n"<<"Fertilizer needed : 30\n"<<"Light needed : 80\n";
}

Lily::Lily() : Tropical("Lily", 65, 40, 85) {}

std::shared_ptr<Plant> Lily::clone() const {
    return std::make_shared<Lily>(*this);
}

double Lily::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return (0.4 * waterRatio + 0.3 * fertilizerRatio + 0.2 * lightRatio) * 100;
}

void Lily::doDisplay() const {
    std::cout<<"Lily:\n"<<"Water needed : 65\n"<<"Fertilizer needed : 40\n"<<"Light needed : 85\n";
}

AloeVera::AloeVera() : Cacti("AloeVera", 20, 5, 80) {}

std::shared_ptr<Plant> AloeVera::clone() const {
    return std::make_shared<AloeVera>(*this);
}

double AloeVera::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return(0.5*waterRatio+0.2*fertilizerRatio+0.3*lightRatio)*100;
}

void AloeVera::doDisplay() const {
    std::cout<<"AloeVera:\n"<<"Water needed : 20\n"<<"Fertilizer needed : 5\n"<<"Light needed : 80\n";
}

Cactus::Cactus() : Cacti("Cactus", 10, 5, 90) {}

std::shared_ptr<Plant> Cactus::clone() const {
    return std::make_shared<Cactus>(*this);
}

double Cactus::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return(0.5*waterRatio+0.2*fertilizerRatio+0.1*lightRatio)*100;
}

void Cactus::doDisplay() const {
    std::cout<<"Cactus:\n"<<"Water needed : 10\n"<<"Fertilizer needed : 5\n"<<"Light needed : 90\n";
}

Flytrap::Flytrap() : Exotic("Flytrap", 30, 30, 30) {}

std::shared_ptr<Plant> Flytrap::clone() const {
    return std::make_shared<Flytrap>(*this);
}

double Flytrap::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return(0.4*waterRatio+0.4*fertilizerRatio+0.3*lightRatio)*100;
}

void Flytrap::doDisplay() const {
    std::cout<<"Flytrap:\n"<<"Water needed : 30\n"<<"Fertilizer needed : 30\n"<<"Light needed : 30\n";
}

Bonsai::Bonsai() : Exotic("Bonsai", 30, 50, 30) {}

std::shared_ptr<Plant> Bonsai::clone() const {
    return std::make_shared<Bonsai>(*this);
}

double Bonsai::calculateHealthIndex() const {

    double const waterRatio = calculateWaterRatio();
    double const fertilizerRatio = calculateFertilizerRatio();
    double const lightRatio = calculateLightRatio();

    return(0.4*waterRatio+0.2*fertilizerRatio+0.2*lightRatio)*100;
}

void Bonsai::doDisplay() const {
    std::cout<<"Bonsai:\n"<<"Water needed : 30\n"<<"Fertilizer needed : 50\n"<<"Light needed : 30\n";
}

