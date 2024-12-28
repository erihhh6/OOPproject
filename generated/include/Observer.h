#ifndef OBSERVER_H
#define OBSERVER_H

/// Base class Observer that defines the interface for objects that want to be notified of changes
class Observer {
public:
    /// Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Observer() = default;

    /// Pure virtual function to be implemented by derived classes to handle updates
    virtual void update() = 0;
};

#endif ///OBSERVER_H
