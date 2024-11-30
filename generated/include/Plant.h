/// Plant.h
#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include <memory>
#include <string>

/// Base class Plant
class Plant {
private:
    std::string name;
    int water_needed;
    int fertilizer_needed;
    int light_needed;
    int current_water;
    int current_fertilizer;
    int current_light;

protected:
    /// Constructor for initializing plant properties, accessible only to derived classes
    Plant(std::string name, int water, int fertilizer, int light);

    /// Protected methods for calculating the ratios

    double calculateWaterRatio() const {
        return static_cast<double>(current_water) / water_needed;
    };

    double calculateFertilizerRatio() const {
        return static_cast<double>(current_fertilizer) / fertilizer_needed;
    };

    double calculateLightRatio() const {
        return static_cast<double>(current_light) / light_needed;
    };

public:
    /// Virtual destructor to allow proper cleanup of derived classes
    virtual ~Plant() = default;

    /// Getter for the name of the plant
    [[nodiscard]] const std::string& getName() const;

    /// Function to care for the plant
    void care(int water, int fertilizer, int light);

    /// Function to simulate the passage of a day
    bool update();

    /// Clone function (virtual constructor)
    virtual std::shared_ptr<Plant> clone() const = 0;

    /// Pure virtual function to calculate health index
    virtual double calculateHealthIndex() const = 0;

    /// Overloaded << operator to print plant details
    friend std::ostream& operator<<(std::ostream& os, const Plant& plant);
};

/// Derived classes for specific plant types
class Flowering : public Plant {
protected:
    Flowering(const std::string& name, int water, int fertilizer, int light);
};

class Tropical : public Plant {
protected:
    Tropical(const std::string& name, int water, int fertilizer, int light);
};

class Cacti : public Plant {
protected:
    Cacti(const std::string& name, int water, int fertilizer, int light);
};

class Exotic : public Plant {
protected:
    Exotic(const std::string& name, int water, int fertilizer, int light);
};

/// Specific plants with predefined needs
class Lavender final : public Flowering {
public:
    Lavender();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Orchid final : public Flowering {
public:
    Orchid();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Hibiscus final : public Tropical {
public:
    Hibiscus();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Lily final : public Tropical {
public:
    Lily();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class AloeVera final : public Cacti {
public:
    AloeVera();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Cactus final : public Cacti {
public:
    Cactus();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Flytrap final : public Exotic {
public:
    Flytrap();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

class Bonsai final : public Exotic {
public:
    Bonsai();
    std::shared_ptr<Plant> clone() const override;
    double calculateHealthIndex() const override;
};

#endif /// PLANT_H