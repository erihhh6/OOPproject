/// Garden.cpp
#include "Garden.h"

Garden::Garden() {
    for (int i = 0; i < capacity; ++i) {
        slots[i] = nullptr;
    }
}

void Garden::addPlant(const std::shared_ptr<Plant>& plant,const int slot) {
    if (slot >= 0 && slot < capacity && !slots[slot]) {
        slots[slot] = plant;
        std::cout << "Plant " << plant->getName()
                  << " has been added to slot "
                  << slot << ".\n";
    } else if (slots[slot]) {
        std::cout << "Slot " << slot
                  << " is already occupied!\n";
    } else {
        std::cout << "Slot is invalid!\n";
    }
}

void Garden::careForPlant(const int slot,const int water,const int fertilizer,const int light) const {
    if (slot >= 0 && slot < capacity && slots[slot]) {
        slots[slot]->care(water,fertilizer ,light);
    } else {
        std::cout <<"Invalid or empty slot!\n";
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

bool Garden :: isSlotEmpty(const int slot )const { return slot>=0&&slot<capacity&&!slots[slot]; }

std::ostream& operator<<(std::ostream& os, const Garden& g) {
    for (int i = 0; i < g.capacity; ++i) {
        if (g.slots[i]) {  // Check if slot is not null
            os << "Slot " << i << ":\n" << *g.slots[i] << "\n";
        } else {
            os << "Slot " << i << ": empty\n";
        }
    }
    return os;
}