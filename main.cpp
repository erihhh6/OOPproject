#include <iostream>
#include <memory>
#include <fstream>
#include <Garden.h>
#include <Achievement.h>
#include <functions.h>
#include <CustomExceptions.h>
#include <Timer.h>


/// MAIN PROGRAM (THE GAME ITSELF)
int main() {
    std::ifstream inputFile("x.txt");
    std::istream& input = inputFile.is_open() ? inputFile : std::cin;

    Achievement achievements;
    Garden garden;
    garden.registerObserver(&achievements);

    Timer<std::chrono::milliseconds> timer_milliseconds;
    Timer<std::chrono::seconds> timer_seconds;

    const std::string message = "Welcome to the Garden!";
    printGardenMessage(message); std::cout << "\n";

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. See garden\n";
        std::cout << "2. Add plant\n";
        std::cout << "3. Care for plant\n";
        std::cout << "4. Apply general care\n";
        std::cout << "5. Let day pass\n";
        std::cout << "6. Display achievements\n";
        std::cout << "7. Calculate Health Index of a Plant\n";
        std::cout << "8. Display plants needs\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";

        try {
            if (!getIntInput(input, choice)) throw InvalidInputException();

            switch (choice) {
                case 1: std::cout << garden; break;
                case 2: addPlant(garden,input); Achievement::incrementPlantsAdded(); break;
                case 3: careForPlant(garden,input); Achievement::incrementPlantsCared(); break;
                case 4: garden.applyGeneralCare(); break;
                case 5: garden.updatePlants(); Achievement::incrementDaysSurvived(); break;
                case 6: std::cout << achievements; break;
                case 7: calculateHealthIndex(garden,input); break;
                case 8: displaySelectedPlantNeeds(input); break;
                case 9: {
                    std::cout << "Exiting the game.\n";
                     printGardenMessage(timer_milliseconds.elapsed_time().count()); std::cout << " milliseconds passed \n";
                     printGardenMessage(timer_seconds.elapsed_time().count()); std::cout << " seconds passed \n";
                    break;
                }
                default: throw InvalidMenuOptionException();
            }
        }catch (const GameException& e) {
            std::cerr << e.what() << '\n';
        }
    } while (choice != 9);

    return 0;
}
