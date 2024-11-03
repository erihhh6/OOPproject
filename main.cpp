#include <iostream>
#include <cstring>
#include <memory>
#include <limits>
#include <fstream>

using namespace std;

class Plant {
private:
    char name[20]{};
    int water_needed;
    int fertilizer_needed;
    int light_needed;
    int current_water;
    int current_fertilizer;
    int current_light;

public:
    Plant(const char* name, const int water, const int fertilizer, const int light)
        : water_needed(water), fertilizer_needed(fertilizer), light_needed(light),
          current_water(water), current_fertilizer(fertilizer), current_light(light) {
        strcpy(this->name, name);
    }

    ~Plant() = default;

    const char* getName() const {
        return name;
    }

    void care(const int water, const int fertilizer, const int light) {
        current_water += water;
        current_fertilizer += fertilizer;
        current_light += light;
        cout << name << " has been cared for.\n";
    }

    bool update() {
        current_water -= 10;
        current_fertilizer -= 2;
        current_light -= 1;

        if (current_water < water_needed / 2 ||
            current_fertilizer < fertilizer_needed / 2 ||
            current_light < light_needed / 2) {
            cout << name << " has died due to lack of care.\n";
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const Plant& plant) {
        os << "Plant: " << plant.name << "\n"
           << "  Current Water: " << plant.current_water << "/" << plant.water_needed << "\n"
           << "  Current Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
           << "  Current Light: " << plant.current_light << "/" << plant.light_needed << "\n";
        return os;
    }
};

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

class Lavender final : public Flowering {
public:
    Lavender() : Flowering("Lavender", 30, 20, 70) {}
};

class Orchid final : public Flowering {
public:
    Orchid() : Flowering("Orchid", 80, 50, 50) {}
};

class Hibiscus final : public Tropical {
public:
    Hibiscus() : Tropical("Hibiscus", 70, 30, 80) {}
};

class Lily final : public Tropical {
public:
    Lily() : Tropical("Lily", 65, 40, 85) {}
};

class AloeVera final : public Cacti {
public:
    AloeVera() : Cacti("AloeVera", 20, 5, 80) {}
};

class Cactus final : public Cacti {
public:
    Cactus() : Cacti("Cactus", 10, 5, 90) {}
};

class Flytrap final : public Exotic {
public:
    Flytrap() : Exotic("Flytrap", 30, 30, 30) {}
};

class Bonsai final : public Exotic {
public:
    Bonsai() : Exotic("Bonsai", 30, 50, 30) {}
};

class Garden {
private:
    shared_ptr<Plant> slots[8];
    int capacity;

public:
    Garden() : capacity(8) {
        for (int i = 0; i < capacity; ++i) {
            slots[i] = nullptr;
        }
    }

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

    void careForPlant(const int slot, const int water, const int fertilizer, const int light) const {
        if (water < 0 || fertilizer < 0 || light < 0) {
            cout << "Error: You cannot add negative values for water, fertilizer, or light.\n";
            return;
        }

        if (slot >= 0 && slot < capacity && slots[slot] != nullptr) {
            slots[slot]->care(water, fertilizer, light);
        } else {
            cout << "There is no plant in this slot!\n";
        }
    }

    void updatePlants() {
        for (int i = 0; i < capacity; ++i) {
            if (slots[i]) {
                if (slots[i]->update()) {
                    slots[i] = nullptr;
                    cout << "Plant in slot " << i << " has been removed.\n";
                }
            }
        }
    }

    bool isSlotEmpty(const int slot) const {
        if (slot < 0 || slot >= capacity) {
            return false;
        }
        return slots[slot] == nullptr;
    }


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


shared_ptr<Plant> selectPlant(istream& input) {
    int option;
    while (true) {
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
                    cout << "Invalid option! Please select a number between 1 and 8.\n";
                break;
            }
        }
    }
}

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
            case 1:
                cout << garden;
                break;
            case 2: {
                int slot;
                while (true) {
                    cout << "Choose a slot (0-7): ";
                    if (getIntInput(input, slot)) {
                        if (slot >= 0 && slot < 8 && garden.isSlotEmpty(slot)) {
                            auto plant = selectPlant(input);
                            if (plant) {
                                garden.addPlant(plant, slot);
                            }
                            break;
                        }
                        cout << "Slot is already occupied or invalid.\n";
                    } else {
                        continue;
                    }
                }
                break;
            }
            case 3: {
                int slot;
                cout << "Choose a slot to care for the plant (0-7): ";
                if (getIntInput(input, slot) && !garden.isSlotEmpty(slot)) {
                    int water, fertilizer, light;

                    while (true) {
                        cout << "Enter the amount of water to add: ";
                        if (getIntInput(input, water)) break;
                    }

                    while (true) {
                        cout << "Enter the amount of fertilizer to add: ";
                        if (getIntInput(input, fertilizer)) break;
                    }

                    while (true) {
                        cout << "Enter the amount of light to add: ";
                        if (getIntInput(input, light)) break;
                    }

                    garden.careForPlant(slot, water, fertilizer, light);
                } else {
                    cout << "There is no plant in this slot or slot is invalid!\n";
                }
                break;
            }
            case 4:
                garden.updatePlants();
                cout << "A day has passed.\n";
                break;
            case 5:
                cout << "Exiting the game.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
