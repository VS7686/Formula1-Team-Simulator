#include "Mechanic.h"

#include <cmath>

namespace f1 {

Mechanic::Mechanic(std::string name, std::string nationality, int age, Money salary, int contractYears,
                   Rating potential, Rating skill, Rating diligence)
    : Staff(std::move(name), std::move(nationality), age, salary, contractYears, potential),
      m_skill(skill),
      m_diligence(diligence) {}

Rating Mechanic::overallRating() const {
    return Rating(static_cast<int>(std::lround(0.5 * m_skill + 0.5 * m_diligence)));
}

Money Mechanic::marketValue() const { return exponentialValue(0.15, 0.05); }

double Mechanic::partWearMultiplier() const { return 1.20 - static_cast<int>(m_diligence) / 100.0 * 0.40; }

}  // namespace f1
