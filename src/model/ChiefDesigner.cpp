#include "ChiefDesigner.h"

#include <algorithm>
#include <cmath>

namespace f1 {

ChiefDesigner::ChiefDesigner(std::string name, std::string nationality, int age, Money salary, int contractYears,
                             Rating potential, Rating innovation, Rating efficiency, Rating reliabilityFocus)
    : Staff(std::move(name), std::move(nationality), age, salary, contractYears, potential),
      m_innovation(innovation),
      m_efficiency(efficiency),
      m_reliabilityFocus(reliabilityFocus) {}

Rating ChiefDesigner::overallRating() const {
    return Rating(static_cast<int>(std::lround(0.4 * m_innovation + 0.4 * m_efficiency + 0.2 * m_reliabilityFocus)));
}

Money ChiefDesigner::marketValue() const { return exponentialValue(0.30, 0.05); }

double ChiefDesigner::projectSuccessChance(int targetGain, int currentPartRating) const {
    const double p = 0.55 + 0.35 * static_cast<int>(m_innovation) / 100.0 - 0.05 * targetGain -
                     0.01 * std::max(0, currentPartRating - 80);
    return std::clamp(p, 0.15, 0.95);
}

int ChiefDesigner::projectDurationRaces(int targetGain) const {
    return static_cast<int>(std::ceil(targetGain * (1.3 - static_cast<int>(m_efficiency) / 100.0 * 0.6)));
}

}  // namespace f1
