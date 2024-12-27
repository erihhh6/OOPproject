#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include "vector"

class Subject {
public:
    void registerObserver(Observer* observer);
    void notifyObservers();

private:
    std::vector<Observer*> observers_;
};

#endif ///SUBJECT_H
