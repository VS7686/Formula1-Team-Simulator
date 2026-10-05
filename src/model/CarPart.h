#pragma once

#include <iosfwd>
#include <string>

#include "../core/Enums.h"
#include "../core/Money.h"
#include "../core/Rating.h"

namespace f1 {

// Abstract base class for every car component.
class CarPart {
public:
    virtual ~CarPart() = default;

    PartType type() const { return m_type; }
    const std::string& name() const { return m_name; }
    Rating rating() const { return m_rating; }
    Rating reliability() const { return m_reliability; }
    double condition() const { return m_condition; }  // 0..100, 100 = brand new
    Money baseCost() const { return m_baseCost; }

    // Rating reduced by up to 15% when the part is worn out.
    double effectiveRating() const;

    // Probability of a failure on one lap. Worse reliability / condition => higher chance.
    // modeMultiplier: engine/driving mode stress; raceDistanceFactor: shorter races scale it up.
    virtual double failureProbabilityPerLap(double modeMultiplier = 1.0, double raceDistanceFactor = 1.0) const;

    // Lowers condition after some laps. loadFactor: 1 normal, >1 pushing; mechanicMult from Mechanic::partWearMultiplier().
    void wear(double laps, double loadFactor, double mechanicMult);
    Money repairCost(double mechanicRepairMult = 1.0) const;
    void repair() { m_condition = 100.0; }
    void upgrade(int ratingGain) { m_rating += ratingGain; }

    // One-line text for the UI describing the part's special attribute.
    virtual std::string secondaryDescription() const = 0;
    virtual void print(std::ostream& os) const;

protected:
    CarPart(PartType type, std::string name, Rating rating, Rating reliability, Money baseCost);

private:
    PartType m_type;
    std::string m_name;
    Rating m_rating;
    Rating m_reliability;
    double m_condition = 100.0;
    Money m_baseCost;
};

std::ostream& operator<<(std::ostream& os, const CarPart& p);

}  // namespace f1
