/// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

/// Events that a Subject (e.g. Garden) can emit to its observers
enum class GardenEvent {
    PLANT_ADDED,  ///< A new plant was placed in a slot
    PLANT_CARED,  ///< A plant received care (water / fertilizer / light)
    DAY_PASSED,   ///< A day elapsed (updatePlants was called)
    PLANT_DIED    ///< A plant died and was removed from its slot
};

/// Base Observer interface — implement update() to react to garden events
class Observer {
public:
    /// Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Observer() = default;

    /// Called by the Subject whenever a relevant event occurs
    virtual void update(GardenEvent event) = 0;
};

#endif /// OBSERVER_H
