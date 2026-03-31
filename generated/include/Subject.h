/// Subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

#include <Observer.h>
#include <vector>

/// Base Subject class — manages a list of observers and notifies them of events
class Subject {
public:
    /// Virtual destructor so derived class destructors are called correctly
    virtual ~Subject() = default;

    /// Registers an observer to receive future notifications
    void registerObserver(Observer* observer);

    /// Notifies all registered observers with the given event
    void notifyObservers(GardenEvent event);

private:
    std::vector<Observer*> observers_;
};

#endif /// SUBJECT_H
