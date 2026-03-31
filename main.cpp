#include <iostream>
#include <memory>
#include <fstream>
#include <Garden.h>
#include <Achievement.h>
#include <functions.h>
#include <CustomExceptions.h>
#include <Timer.h>

int main() {
    std::ifstream inputFile("x.txt");
    std::istream& input = inputFile.is_open() ? inputFile : std::cin;

    Achievement achievements;
    Garden garden;
    garden.registerObserver(&achievements);

    Timer<std::chrono::milliseconds> timer_ms;
    Timer<std::chrono::seconds>      timer_s;

    printGardenMessage(std::string("Welcome to the Botanical Garden Simulator!\n"));

    int choice;
    do {
        std::cout << "\n--- Day " << garden.getCurrentDay()
                  << " | " << Garden::seasonName(garden.getCurrentSeason())
                  << " ---\n";
        std::cout << "Menu:\n"
                  << "  1.  See garden\n"
                  << "  2.  Add plant\n"
                  << "  3.  Care for plant\n"
                  << "  4.  Apply general care\n"
                  << "  5.  Let day pass\n"
                  << "  6.  Display achievements\n"
                  << "  7.  Calculate health index\n"
                  << "  8.  Display plant needs\n"
                  << "  9.  Save garden\n"
                  << " 10.  Load garden\n"
                  << " 11.  Exit\n"
                  << "Enter your choice: ";

        try {
            if (!getIntInput(input, choice)) throw InvalidInputException();

            switch (choice) {
                case 1:  std::cout << garden; break;

                case 2:  addPlant(garden, input);    break;  // PLANT_ADDED notified inside Garden

                case 3:  careForPlant(garden, input); break; // PLANT_CARED notified inside Garden

                case 4:  garden.applyGeneralCare();   break; // PLANT_CARED notified per slot

                case 5: {
                    const int died = garden.updatePlants(); // DAY_PASSED + PLANT_DIED notified inside
                    std::cout << "Plants lost today: " << died << "\n";
                    break;
                }

                case 6:  std::cout << achievements; break;

                case 7:  calculateHealthIndex(garden, input); break;

                case 8:  displaySelectedPlantNeeds(input); break;

                case 9: {
                    garden.saveToFile("garden-save.txt");
                    break;
                }

                case 10: {
                    // operator= preserves observers; loadFromFile returns a fresh Garden
                    garden = Garden::loadFromFile("garden-save.txt");
                    garden.registerObserver(&achievements);
                    break;
                }

                case 11: {
                    std::cout << "Exiting the game.\n";
                    printGardenMessage(timer_ms.elapsed_time().count());
                    std::cout << " ms | ";
                    printGardenMessage(timer_s.elapsed_time().count());
                    std::cout << " s elapsed\n";
                    break;
                }

                default: throw InvalidMenuOptionException();
            }
        } catch (const GameException& e) {
            std::cerr << e.what() << "\n";
        }
    } while (choice != 11);

    return 0;
}
