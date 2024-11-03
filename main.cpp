#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

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

    // Copy constructor
    Plant(const Plant& other)
        : water_needed(other.water_needed), fertilizer_needed(other.fertilizer_needed),
          light_needed(other.light_needed), current_water(other.current_water),
          current_fertilizer(other.current_fertilizer), current_light(other.current_light) {
        strcpy(this->name, other.name);
    }

    // Assignment operator
    Plant& operator=(const Plant& other) {
        if (this != &other) {
            strcpy(name, other.name);
            water_needed = other.water_needed;
            fertilizer_needed = other.fertilizer_needed;
            light_needed = other.light_needed;
            current_water = other.current_water;
            current_fertilizer = other.current_fertilizer;
            current_light = other.current_light;
        }
        return *this;
    }

    // Destructor
    virtual ~Plant() = default;

    // Getter for name
    const char* getName() const {
        return name;
    }

    // Public interface for caring for the plant
    void care(const int water, const int fertilizer, const int light) {
        current_water += water;
        current_fertilizer += fertilizer;
        current_light += light;
        cout << name << " has been cared for.\n";
    }

    // Update function
    bool update() {
        // Decrease current values each day
        current_water -= 10;
        current_fertilizer -= 2;
        current_light -= 1;

        // Check if any current value is less than half of needed value
        if (current_water < water_needed / 2 ||
            current_fertilizer < fertilizer_needed / 2 ||
            current_light < light_needed / 2) {
            cout << name << " has died due to lack of care.\n";
            return true; // Plant has died
        }
        return false; // Plant is still alive
    }

    friend ostream& operator<<(ostream& os, const Plant& plant) {
        os << "Plant: " << plant.name << "\n"
           << "  Current Water: " << plant.current_water << "/" << plant.water_needed << "\n"
           << "  Current Fertilizer: " << plant.current_fertilizer << "/" << plant.fertilizer_needed << "\n"
           << "  Current Light: " << plant.current_light << "/" << plant.light_needed << "\n";
        return os;
    }
};

class Tulip final : public Plant {
public:
    Tulip() : Plant("Tulip", 50, 20, 60) {}
};

class Cactus final : public Plant {
public:
    Cactus() : Plant("Cactus", 30, 10, 80) {}
};

class Rose final : public Plant {
public:
    Rose() : Plant("Rose", 80, 40, 70) {}
};

class Magnolia final : public Plant {
public:
    Magnolia() : Plant("Magnolia", 100, 50, 90) {}
};

class Garden {
private:
    vector<shared_ptr<Plant>> slots;
    int capacity;

public:
    explicit Garden(const int capacity) : capacity(capacity) {
        slots.resize(capacity, nullptr);
    }

    void addPlant(const shared_ptr<Plant>& plant, const int slot) {
        if (slot < capacity && slot >= 0) {
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

    void careForPlant(const int slot, int water, int fertilizer, int light) const {
        // Check for non-negative inputs
        if (water < 0 || fertilizer < 0 || light < 0) {
            cout << "Error: You cannot add negative values for water, fertilizer, or light.\n";
            return; // Exit the function early without applying care
        }

        if (slot < capacity && slot >= 0 && slots[slot] != nullptr) {
            slots[slot]->care(water, fertilizer, light);
        } else {
            cout << "There is no plant in this slot!\n";
        }
    }


    void updatePlants() {
        for (int i = 0; i < capacity; ++i) {
            if (slots[i]) {
                const bool died = slots[i]->update();
                if (died) {
                    slots[i] = nullptr;
                    cout << "Plant in slot " << i << " has been removed.\n";
                }
            }
        }
    }

    bool isSlotEmpty(const int slot) const {
        if (slot < 0 || slot >= capacity) {
            return false; // Invalid slot
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

// Function to display plant menu
void displayPlantMenu() {
    cout << "Choose the type of plant you want to add:\n";
    cout << "1. Tulip\n";
    cout << "2. Cactus\n";
    cout << "3. Rose\n";
    cout << "4. Magnolia\n";
}

// Function to select and create a plant
shared_ptr<Plant> selectPlant() {
    int option;
    displayPlantMenu();
    cout << "Enter your option: ";
    cin >> option;

    switch (option) {
        case 1: return make_shared<Tulip>();
        case 2: return make_shared<Cactus>();
        case 3: return make_shared<Rose>();
        case 4: return make_shared<Magnolia>();
        default:
            cout << "Invalid option!\n";
            return nullptr;
    }
}

int main() {
    Garden garden(8); // Initialize a garden with 8 slots

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. See garden\n";
        cout << "2. Add plant\n";
        cout << "3. Care for plant\n";
        cout << "4. Let day pass\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << garden;
                break;
            case 2: {
                int slot;
                cout << "Choose a slot (0-7): ";
                cin >> slot;
                if (garden.isSlotEmpty(slot)) {
                    auto plant = selectPlant();
                    if (plant) {
                        garden.addPlant(plant, slot);
                    }
                } else {
                    cout << "Slot is already occupied or invalid.\n";
                }
                break;
            }
            case 3: {
                int slot;
                cout << "Choose a slot to care for the plant (0-7): ";
                cin >> slot;
                if (!garden.isSlotEmpty(slot)) {
                    int water, fertilizer, light;
                    cout << "Enter the amount of water to add: ";
                    cin >> water;
                    cout << "Enter the amount of fertilizer to add: ";
                    cin >> fertilizer;
                    cout << "Enter the amount of light to add: ";
                    cin >> light;
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
