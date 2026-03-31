/// Subject.cpp
#include <Subject.h>

void Subject::registerObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::notifyObservers(GardenEvent event) {
    for (const auto& observer : observers_) {
        observer->update(event);
    }
}
