#include <Subject.h>

void Subject::registerObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::notifyObservers() {
    for (const auto& observer : observers_) {
        observer->update();
    }
}
