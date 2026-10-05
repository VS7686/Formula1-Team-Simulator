#pragma once

#include "Staff.h"

namespace f1 {

// Mechanics keep the car in shape: skill = setup/repair quality, diligence = care for parts.
class Mechanic : public Staff {
public:
    Mechanic(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential,
             Rating skill, Rating diligence);

    Rating overallRating() const override;
    std::string role() const override { return "Mechanic"; }
    Money marketValue() const override;

    // Multiplier on part wear: 0.8 (very careful) .. 1.2 (careless).
    double partWearMultiplier() const;

    Rating skill() const { return m_skill; }
    Rating diligence() const { return m_diligence; }

private:
    Rating m_skill;
    Rating m_diligence;
};

}  // namespace f1
