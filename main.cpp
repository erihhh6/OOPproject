#include <iostream>
#include <memory>
#include <fstream>
#include <Garden.h>
#include <Achievement.h>
#include <functions.h>

/// MAIN PROGRAM (THE GAME ITSELF)
int main() {
    std::ifstream inputFile("input.txt");
    std::istream& input = inputFile.is_open() ? inputFile : std::cin;

    Garden garden;
    Achievement achievements;

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. See garden\n";
        std::cout << "2. Add plant\n";
        std::cout << "3. Care for plant\n";
        std::cout << "4. Let day pass\n";
        std::cout << "5. Display achievements\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        if (!getIntInput(input, choice)) continue;

        switch (choice) {
            case 1: std::cout << garden; break;
            case 2: addPlant(garden,input); break;
            case 3: careForPlant(garden,input); achievements.incrementPlantsCared(); break;
            case 4: garden.updatePlants(); achievements.incrementDaysSurvived(); break;
            case 5: std::cout << achievements; break;
            case 6: std::cout << "Exiting the game.\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
