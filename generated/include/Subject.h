#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>

/// Base Subject class that manages a list of observers and notifies them of changes
class Subject {
public:
    /// Registers an observer to receive notifications
    void registerObserver(Observer* observer);

    /// Notifies all registered observers of a change
    void notifyObservers();

private:
    /// List of registered observers
    std::vector<Observer*> observers_;
};

#endif ///SUBJECT_H
