#include <iostream>
#include <cstring>
#include <memory>
#include <limits>
#include <fstream>

using namespace std;
///clasa de baza PLANTA cu date private
class Plant {
private:
    char name[20]{};
    int water_needed;
    int fertilizer_needed;
    int light_needed;
    int current_water;
    int current_fertilizer;
    int current_light;

protected:
    ///constructor de initializare ce poate fi folosit doar de clase derivate
    Plant(const char* name, const int water, const int fertilizer, const int light)
        : water_needed(water), fertilizer_needed(fertilizer), light_needed(light),
          current_water(water), current_fertilizer(fertilizer), current_light(light) {
        strcpy(this->name, name);
    }

public:
    ///destructor virtual ce permite stergerea corecta a entitatilor din clase derivate
    virtual ~Plant() = default;

    ///getter pentru numele plantei
    const char* getName() const {
        return name;
    }

    ///functie pentru ingrijirea plantei
    void care(const int water, const int fertilizer, const int light) {
        current_water += water;
        current_fertilizer += fertilizer;
        current_light += light;
        cout << name << " has been cared for.\n";
    }

    ///functie pentru simularea trecerii unei zile
    bool update() {
        current_water -= 10;
        current_fertilizer -= 2;
        current_light -= 1;

        if (current_water < water_needed / 2 || current_fertilizer < fertilizer_needed / 2 || current_light < light_needed / 2) {
            cout << name << " has died due to lack of care.\n";
            return true;
        }
        return false;
    }

    ///operator supraincarcat pentru afisarea detalilor unei plante
    friend ostream& operator<<(ostream& os, const Plant& plant) {
        os << "Plant: " << plant.name << "\n"
           << "  Current Water: " << plant.current_water << "/" << plant.water_needed << "\n"
           << "  Current Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
           << "  Current Light: " << plant.current_light << "/" << plant.light_needed << "\n";
        return os;
    }
};

///clase derivate pentru diferite tipuri de plante

class Flowering : public Plant {
protected:
    Flowering(const char* name, const int water, const int fertilizer, const int light)
        : Plant(name, water, fertilizer, light) {}
};

class Tropical : public Plant {
protected:
    Tropical(const char* name, const int water, const int fertilizer, const int light)
        : Plant(name, water, fertilizer, light) {}
};

class Cacti : public Plant {
protected:
    Cacti(const char* name, const int water, const int fertilizer, const int light)
        : Plant(name, water, fertilizer, light) {}
};

class Exotic : public Plant {
protected:
    Exotic(const char* name, const int water, const int fertilizer, const int light)
        : Plant(name, water, fertilizer, light) {}
};

///clase derivate cu plante specifice din tipurile definite mai sus

class Lavender final : public Flowering { public:Lavender() : Flowering("Lavender", 30, 20, 70) {} };
class Orchid final : public Flowering { public: Orchid() : Flowering("Orchid", 80, 50, 50) {} };
class Hibiscus final : public Tropical { public: Hibiscus() : Tropical("Hibiscus", 70, 30, 80) {} };
class Lily final : public Tropical { public: Lily() : Tropical("Lily", 65, 40, 85) {} };
class AloeVera final : public Cacti { public: AloeVera() : Cacti("AloeVera", 20, 5, 80) {} };
class Cactus final : public Cacti { public: Cactus() : Cacti("Cactus", 10, 5, 90) {} };
class Flytrap final : public Exotic { public: Flytrap() : Exotic("Flytrap", 30, 30, 30) {} };
class Bonsai final : public Exotic { public: Bonsai() : Exotic("Bonsai", 30, 50, 30) {} };


///clasa de baza GRADINA cu date private si capacitate predefinita de mine de 8 sloturi
class Garden {
private:
    shared_ptr<Plant> slots[8];
    int capacity;

public:
    ///constructor ce initializeaza fiecare slot ca fiind gol
    Garden() : capacity(8) {
        for (int i = 0; i < capacity; ++i) {
            slots[i] = nullptr;
        }
    }

    ///functie pentru adaugarea unei plante intr-un slot specific
    void addPlant(const shared_ptr<Plant>& plant, const int slot) {
        if (slot >= 0 && slot < capacity) {
            if (slots[slot] == nullptr) {
                slots[slot] = plant;
                cout << "Plant " << plant->getName() << " has been added to slot " << slot << ".\n";
            } else {
                cout << "Slot " << slot << " is already occupied!\n";
            }
        } else {
            cout << "Slot " << slot << " is invalid!\n";
        }
    }

    ///functie pentru ingrijirea unei plante dintr-un slot specific
    void careForPlant(const int slot, const int water, const int fertilizer, const int light) const {
        if (slot >= 0 && slot < capacity && slots[slot] != nullptr) {
            slots[slot]->care(water, fertilizer, light);
        } else {
            cout << "There is no plant in this slot or the slot is invalid!\n";
        }
    }

    ///functie pentru simularea trecerii unei zile pentru fiecare planta
    void updatePlants() {
        for (int i = 0; i < capacity; ++i) {
            if (slots[i]) {
                if (slots[i]->update()) {
                    slots[i] = nullptr;
                    cout << "Plant in slot " << i << " has been removed.\n";
                }
            }
        }
        cout << "A day has passed.\n";
    }

    ///functie pentru verificarea validitatii unui slot
    bool isSlotEmpty(const int slot) const {
        if (slot < 0 || slot >= capacity) {return false;}
        return slots[slot] == nullptr;
    }

    ///operator supraincarcat pentru afisarea detalilor gradinii
    friend ostream& operator<<(ostream& os, const Garden& garden) {
        for (int i = 0; i < garden.capacity; ++i) {
            if (garden.slots[i]) {
                os << "Slot " << i << ":\n" << *garden.slots[i] << "\n";
            } else {
                os << "Slot " << i << ": empty\n";
            }
        }
        return os;
    }
};

///functie pentru validarea inputului din stream (SA FIE NUMAR)
bool getIntInput(istream& input, int& value) {
    input >> value;
    if (input.fail()) {
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return false;
    }
    return true;
}

///toate functiile de mai jos au verificare pentru input valid

///functie pentru selectarea plantei bazata pe input
shared_ptr<Plant> selectPlant(istream& input) {
    int option;
        cout << "Choose the type of plant you want to add:\n";
        cout << "1. Lavender (Flowering)\n";
        cout << "2. Orchid (Flowering)\n";
        cout << "3. Hibiscus (Tropical)\n";
        cout << "4. Lily (Tropical)\n";
        cout << "5. AloeVera (Cacti)\n";
        cout << "6. Cactus (Cacti)\n";
        cout << "7. Flytrap (Exotic)\n";
        cout << "8. Bonsai (Exotic)\n";
        cout << "Enter your option: ";
    while (true) {
        if (getIntInput(input, option)) {
            switch (option) {
                case 1: return make_shared<Lavender>();
                case 2: return make_shared<Orchid>();
                case 3: return make_shared<Hibiscus>();
                case 4: return make_shared<Lily>();
                case 5: return make_shared<AloeVera>();
                case 6: return make_shared<Cactus>();
                case 7: return make_shared<Flytrap>();
                case 8: return make_shared<Bonsai>();
                default:
                    cout << "Invalid option! Please select a number between 1 and 8.\n"; break;
            }
        }
    }
}

///functie pentru ingrijirea unei plantei bazata pe input
void careForPlant(const Garden& garden, istream& input) {
    int slot;

     while (true) {
        cout << "Choose a slot to care for the plant (0-7): ";
        if (!getIntInput(input, slot)) continue;
        if (slot >= 0 && slot < 8) {
            if (!garden.isSlotEmpty(slot)) break;
            cout << "There is no plant in this slot. Returning to menu.\n";
            return;
        }
        cout << "Slot is invalid. Please choose a slot between 0 and 7.\n";
     }

    int water, fertilizer, light;

    while (true) {
        cout << "Enter the amount of water to add : ";
        if (getIntInput(input, water) && water >= 0) {break;}
        if(water < 0) cout << "Invalid input. Water must be a non-negative number.\n";
    }

    while (true) {
        cout << "Enter the amount of fertilizer to add : ";
        if (getIntInput(input, fertilizer) && fertilizer >= 0) {break;}
        if(fertilizer < 0) cout << "Invalid input. Fertilizer must be a non-negative number.\n";
    }

    while (true) {
        cout << "Enter the amount of light to add : ";
        if (getIntInput(input, light) && light >= 0) {break;}
        if(light < 0) cout << "Invalid input. Light must be a non-negative number.\n";
    }

    garden.careForPlant(slot, water, fertilizer, light);

}

///functie pentru adaugarea unei plante bazata pe input
void addPlant(Garden& garden, istream& input) {
    int slot;
    while (true) {
        cout << "Choose a slot (0-7): ";
        if (getIntInput(input, slot)) {
            if (slot >= 0 && slot < 8 && garden.isSlotEmpty(slot)) {
                if (auto plant = selectPlant(input)) {
                    garden.addPlant(plant, slot);
                }
                break;
            }
            cout << "Slot is already occupied or invalid.\n";
        } else {
            continue;
        }
    }
}

///MAIN (jocul in sine)
int main() {
    ifstream inputFile("tastatura.txt");
    istream& input = inputFile.is_open() ? inputFile : cin;

    Garden garden;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. See garden\n";
        cout << "2. Add plant\n";
        cout << "3. Care for plant\n";
        cout << "4. Let day pass\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!getIntInput(input, choice)) continue;

        switch (choice) {
            case 1: cout << garden; break;
            case 2: addPlant(garden,input); break;
            case 3: careForPlant(garden,input); break;
            case 4: garden.updatePlants(); break;
            case 5: cout << "Exiting the game.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
