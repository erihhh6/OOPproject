#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>

/// Base class for all custom exceptions
class GameException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Game exception occurred";
    }
};

/// Derived class for invalid menu option errors
class InvalidMenuOptionException final : public GameException {
public:
    const char* what() const noexcept override {
        return "Invalid menu option selected. Please choose a number between 1 and 9.";
    }
};

/// Derived class for invalid slot errors
class InvalidSlotException final : public GameException {
public:
    const char* what() const noexcept override {
        return "Invalid slot selected. Please choose a slot between 0 and 7.";
    }
};

/// Derived class for invalid input errors
class InvalidInputException final : public GameException {
public:
    const char* what() const noexcept override {
        return "Invalid input provided. Please enter a valid number.";
    }
};

#endif ///CUSTOMEXCEPTIONS_H
