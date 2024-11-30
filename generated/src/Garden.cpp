/// Garden.cpp
#include "Garden.h"

Garden::Garden() {
    for (int i = 0; i < capacity; ++i) {
        slots[i] = nullptr;
    }
}

void Garden::addPlant(const std::shared_ptr<Plant>& plant,const int slot) {
        slots[slot] = plant->clone();
        std::cout << "Plant " << plant->getName() << " has been added to slot " << slot << ".\n";
}

void Garden::careForPlant(const int slot,const int water,const int fertilizer,const int light) const {
        slots[slot]->care(water,fertilizer ,light);
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