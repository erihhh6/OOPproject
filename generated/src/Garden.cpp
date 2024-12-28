/// Garden.cpp
#include <Garden.h>
#include <PlantFactory.h>
#include <Subject.h>

Garden::Garden() {
    for (auto & slot : slots) {
        slot = nullptr;
    }
}

Garden::Garden(const Garden& other)  : Subject(other) {
    for (int i = 0; i < capacity; ++i) {
        if (other.slots[i]) {
            slots[i] = other.slots[i]->clone();
        } else {
            slots[i] = nullptr;
        }
    }
}

Garden& Garden::operator=(Garden other) {
    swap(*this, other);
    return *this;
}

void swap(Garden& first, Garden& second) noexcept {
    using std::swap;
    for (int i = 0; i < Garden::capacity; ++i) {
        swap(first.slots[i], second.slots[i]);
    }
}

void Garden::addPlant(const std::string& plantType,const int slot) {
        const std::shared_ptr<Plant> plant = PlantFactory::createPlant(plantType);
        slots[slot] = plant->clone();
        std::cout << "Plant " << plant->getName() << " has been added to slot " << slot << ".\n";
        notifyObservers();
}

void Garden::careForPlant(int slot, int water, int fertilizer, int light) {
        slots[slot]->care(water,fertilizer ,light);
        notifyObservers();
}

void Garden::applyGeneralCare() {
    for (int i = 0; i < capacity; ++i) {
        if (slots[i]) {
            if (const auto flowering = std::dynamic_pointer_cast<Flowering>(slots[i])) {
                std::cout << "Applying flowering-specific care to plant in slot " << i << ".\n";
                flowering->care(10, 5, 10);
                Achievement::incrementPlantsCared();
                notifyObservers();
            } else if (const auto tropical = std::dynamic_pointer_cast<Tropical>(slots[i])) {
                std::cout << "Applying tropical-specific care to plant in slot " << i << ".\n";
                tropical->care(15, 10, 5);
                Achievement::incrementPlantsCared();
                notifyObservers();
            } else if (const auto cacti = std::dynamic_pointer_cast<Cacti>(slots[i])) {
                std::cout << "Applying cacti-specific care to plant in slot " << i << ".\n";
                cacti->care(5, 2, 20);
                Achievement::incrementPlantsCared();
                notifyObservers();
            } else if (const auto exotic = std::dynamic_pointer_cast<Exotic>(slots[i])) {
                std::cout << "Applying exotic-specific care to plant in slot " << i << ".\n";
                exotic->care(8, 4, 12);
                Achievement::incrementPlantsCared();
                notifyObservers();
            }
        }
    }
}

void Garden::updatePlants() {
    for (int i =0; i<capacity; ++i){
        if(slots[i] && slots[i]->update()){
            slots[i] = nullptr;
            std :: cout <<"Removed dead from "<<i<<"\n";
        }
    }
}

double Garden::calculateHealthIndex(int const slot) const {
        return slots[slot]->calculateHealthIndex();
}



bool Garden :: isSlotEmpty(const int slot )const { return slot>=0&&slot<capacity&&!slots[slot]; }

std::ostream& operator<<(std::ostream& os, const Garden& garden) {
    for (int i = 0; i < Garden::capacity; ++i) {
        if (garden.slots[i]) {
            os << "Slot " << i << ":\n" << *garden.slots[i] << "\n";
        } else {
            os << "Slot " << i << ": empty\n";
        }
    }
    return os;
}