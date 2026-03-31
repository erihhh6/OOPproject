/// CustomExceptions.h
#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>

/// Base class for all custom game exceptions
class GameException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Game exception occurred";
    }
};

/// Thrown when the user picks an option outside the menu range
class InvalidMenuOptionException final : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Invalid menu option. Please choose a valid number.";
    }
};

/// Thrown when the user addresses a slot that is out-of-range or occupied
class InvalidSlotException final : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Invalid slot. Please choose a slot between 0 and 7.";
    }
};

/// Thrown when the user provides non-integer input where an integer is expected
class InvalidInputException final : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Invalid input. Please enter a valid number.";
    }
};

/// Thrown by PlantFactory when an unrecognised plant type string is requested
class InvalidPlantTypeException final : public GameException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Invalid plant type. Valid types: Lavender, Orchid, Hibiscus, Lily, "
               "AloeVera, Cactus, Flytrap, Bonsai.";
    }
};

#endif /// CUSTOMEXCEPTIONS_H
