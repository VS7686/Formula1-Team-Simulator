#include "PitCrew.h"

#include <cmath>

namespace f1 {

PitCrew::PitCrew(std::string name, std::string nationality, int age, Money salary, int contractYears,
                 Rating potential, Rating speed, Rating consistency, Rating safety)
    : Staff(std::move(name), std::move(nationality), age, salary, contractYears, potential),
      m_speed(speed),
      m_consistency(consistency),
      m_safety(safety) {}

Rating PitCrew::overallRating() const {
    return Rating(static_cast<int>(std::lround(0.45 * m_speed + 0.35 * m_consistency + 0.20 * m_safety)));
}

Money PitCrew::marketValue() const { return exponentialValue(0.40, 0.05); }

double PitCrew::expectedStationaryTime() const { return 2.3 + (100 - static_cast<int>(m_speed)) / 100.0 * 1.5; }

double PitCrew::slowStopChance() const { return (100 - static_cast<int>(m_consistency)) / 100.0 * 0.08; }

double PitCrew::unsafeReleaseChance() const { return 0.02 * (100 - static_cast<int>(m_safety)) / 100.0; }

}  // namespace f1
