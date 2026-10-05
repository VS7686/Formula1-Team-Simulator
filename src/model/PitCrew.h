#pragma once

#include "Staff.h"

namespace f1 {

// The pit crew is one unit per team. It decides how fast and how reliable pit stops are.
class PitCrew : public Staff {
public:
    PitCrew(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential,
            Rating speed, Rating consistency, Rating safety);

    Rating overallRating() const override;
    std::string role() const override { return "Pit Crew"; }
    Money marketValue() const override;

    // Expected stationary time in seconds (no randomness): 2.3 s (perfect) .. 3.8 s (terrible).
    double expectedStationaryTime() const;
    // Chance of a slow stop (stuck wheel nut) per pit stop.
    double slowStopChance() const;
    // Chance of an unsafe release (5 s penalty) per pit stop.
    double unsafeReleaseChance() const;

    Rating speed() const { return m_speed; }
    Rating consistency() const { return m_consistency; }
    Rating safety() const { return m_safety; }

private:
    Rating m_speed;
    Rating m_consistency;
    Rating m_safety;
};

}  // namespace f1
