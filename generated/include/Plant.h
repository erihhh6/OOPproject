/// Plant.h
#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <constants.h>

// ---------------------------------------------------------------------------
// Supporting enums and structs
// ---------------------------------------------------------------------------

/// The four life-cycle stages a plant can progress through
enum class GrowthStage { SEEDLING, GROWING, MATURE, BLOOMING };

/// The four seasons that rotate every DAYS_PER_SEASON days
enum class Season { SPRING, SUMMER, AUTUMN, WINTER };

/// Per-day resource loss rates specific to each plant type
struct DecayRates {
    int water;       ///< Units of water lost per day (before season multiplier)
    int fertilizer;  ///< Units of fertilizer lost per day
    int light;       ///< Units of light lost per day
};

// ---------------------------------------------------------------------------
// Base class
// ---------------------------------------------------------------------------

/// Abstract base class representing any plant in the garden (NVI pattern)
class Plant {
private:
    std::string name;
    int water_needed;
    int fertilizer_needed;
    int light_needed;
    int current_water;
    int current_fertilizer;
    int current_light;
    GrowthStage stage{GrowthStage::SEEDLING};
    int consecutiveHealthyDays{0};

protected:
    /// Event log for this plant slot (accessible to derived classes for custom entries)
    std::vector<std::string> history;

    /// Constructor — only callable by derived classes
    Plant(std::string name, int water, int fertilizer, int light);

    /// Ratio helpers used by calculateHealthIndex() overrides
    [[nodiscard]] double calculateWaterRatio()      const;
    [[nodiscard]] double calculateFertilizerRatio() const;
    [[nodiscard]] double calculateLightRatio()      const;

    /// NVI display hook — must print this plant's static needs (water/fertilizer/light)
    virtual void doDisplay() const = 0;

    /// Advances GrowthStage when enough consecutive healthy days have passed
    void updateGrowthStage();

public:
    virtual ~Plant() = default;

    // --- Getters ---
    [[nodiscard]] const std::string& getName()             const;
    [[nodiscard]] int  getWaterNeeded()                    const;
    [[nodiscard]] int  getFertilizerNeeded()               const;
    [[nodiscard]] int  getLightNeeded()                    const;
    [[nodiscard]] int  getCurrentWater()                   const;
    [[nodiscard]] int  getCurrentFertilizer()              const;
    [[nodiscard]] int  getCurrentLight()                   const;
    [[nodiscard]] GrowthStage getGrowthStage()             const;
    [[nodiscard]] int  getConsecutiveHealthyDays()         const;
    [[nodiscard]] const std::vector<std::string>& getHistory() const;

    /// Returns daily decay rates; override in derived types for differentiated decay
    [[nodiscard]] virtual DecayRates getDecayRates() const;

    /// Restores internal state after loading from a save file
    void restoreState(int water, int fertilizer, int light,
                      GrowthStage stage, int healthyDays);

    /// Appends a timestamped log entry to this plant's history
    void addHistory(const std::string& entry);

    /// Applies care; all values are capped at 2× the plant's need
    void care(int water, int fertilizer, int light);

    /// Simulates one day: applies season-adjusted decay, checks death, advances growth.
    /// @return true if the plant died (caller should remove it)
    [[nodiscard]] bool update(Season season, int day);

    /// Virtual constructor (clone pattern)
    [[nodiscard]] virtual std::shared_ptr<Plant> clone() const = 0;

    /// Weighted health index in [0, 100]; weights must sum to 1.0 in each override
    [[nodiscard]] virtual double calculateHealthIndex() const = 0;

    /// NVI public wrapper for doDisplay()
    void display() const { doDisplay(); }

    friend std::ostream& operator<<(std::ostream& os, const Plant& plant);
};

// ---------------------------------------------------------------------------
// Intermediate type classes — supply default DecayRates per category
// ---------------------------------------------------------------------------

class Flowering : public Plant {
protected:
    Flowering(const std::string& name, int water, int fertilizer, int light);
public:
    [[nodiscard]] DecayRates getDecayRates() const override;
};

class Tropical : public Plant {
protected:
    Tropical(const std::string& name, int water, int fertilizer, int light);
public:
    [[nodiscard]] DecayRates getDecayRates() const override;
};

class Cacti : public Plant {
protected:
    Cacti(const std::string& name, int water, int fertilizer, int light);
public:
    [[nodiscard]] DecayRates getDecayRates() const override;
};

class Exotic : public Plant {
protected:
    Exotic(const std::string& name, int water, int fertilizer, int light);
public:
    [[nodiscard]] DecayRates getDecayRates() const override;
};

// ---------------------------------------------------------------------------
// Concrete plant classes
// ---------------------------------------------------------------------------

class Lavender final : public Flowering {
public:
    Lavender();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class Orchid final : public Flowering {
public:
    Orchid();
    [[nodiscard]] std::shared_ptr<Plant> clone()          const override;
    [[nodiscard]] double calculateHealthIndex()            const override;
    [[nodiscard]] DecayRates getDecayRates()              const override; ///< Higher water/fertilizer loss
protected:
    void doDisplay() const override;
};

class Hibiscus final : public Tropical {
public:
    Hibiscus();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class Lily final : public Tropical {
public:
    Lily();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class AloeVera final : public Cacti {
public:
    AloeVera();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class Cactus final : public Cacti {
public:
    Cactus();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class Flytrap final : public Exotic {
public:
    Flytrap();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

class Bonsai final : public Exotic {
public:
    Bonsai();
    [[nodiscard]] std::shared_ptr<Plant> clone() const override;
    [[nodiscard]] double calculateHealthIndex() const override;
protected:
    void doDisplay() const override;
};

#endif /// PLANT_H
