#include "CarPart.h"

#include <algorithm>
#include <iomanip>
#include <ostream>

#include "../core/Constants.h"

namespace f1 {

CarPart::CarPart(PartType type, std::string name, Rating rating, Rating reliability, Money baseCost)
    : m_type(type), m_name(std::move(name)), m_rating(rating), m_reliability(reliability), m_baseCost(baseCost) {}

double CarPart::effectiveRating() const {
    return static_cast<int>(m_rating) * (0.85 + 0.15 * m_condition / 100.0);
}

double CarPart::failureProbabilityPerLap(double modeMultiplier, double raceDistanceFactor) const {
    const double reliabilityTerm = 1.0 + (100 - static_cast<int>(m_reliability)) / 25.0;
    const double conditionTerm = 1.0 + std::max(0.0, 50.0 - m_condition) / 25.0;
    return constants::kBaseFailurePerLap * reliabilityTerm * conditionTerm * modeMultiplier / raceDistanceFactor;
}

void CarPart::wear(double laps, double loadFactor, double mechanicMult) {
    m_condition -= constants::kBasePartWearPerLap * laps * loadFactor * mechanicMult;
    m_condition = std::max(0.0, m_condition);
}

Money CarPart::repairCost(double mechanicRepairMult) const {
    return m_baseCost * ((100.0 - m_condition) / 100.0 * 0.25 * mechanicRepairMult);
}

void CarPart::print(std::ostream& os) const {
    os << std::left << std::setw(20) << m_name << " rating " << std::setw(3) << m_rating << " reliability "
       << std::setw(3) << m_reliability << " condition " << std::fixed << std::setprecision(0) << m_condition
       << "%  | " << secondaryDescription();
}

std::ostream& operator<<(std::ostream& os, const CarPart& p) {
    p.print(os);
    return os;
}

}  // namespace f1
