#include "AeroParts.h"

namespace f1 {

FrontWing::FrontWing(Rating rating, Rating reliability, Rating airflowControl)
    : CarPart(PartType::FRONT_WING, "Front Wing", rating, reliability, Money::fromMillions(1.2)),
      m_airflowControl(airflowControl) {}

double FrontWing::dirtyAirMultiplier() const { return 1.30 - static_cast<int>(m_airflowControl) / 100.0 * 0.60; }

std::string FrontWing::secondaryDescription() const {
    return "airflow control " + std::to_string(static_cast<int>(m_airflowControl));
}

RearWing::RearWing(Rating rating, Rating reliability, Rating dragEfficiency)
    : CarPart(PartType::REAR_WING, "Rear Wing", rating, reliability, Money::fromMillions(1.2)),
      m_dragEfficiency(dragEfficiency) {}

double RearWing::powerMultiplier() const { return 1.0 + 0.0006 * (static_cast<int>(m_dragEfficiency) - 50); }

std::string RearWing::secondaryDescription() const {
    return "drag efficiency " + std::to_string(static_cast<int>(m_dragEfficiency));
}

Floor::Floor(Rating rating, Rating reliability, Rating groundEffect)
    : CarPart(PartType::FLOOR, "Floor", rating, reliability, Money::fromMillions(2.0)),
      m_groundEffect(groundEffect) {}

double Floor::aeroBonusFraction() const { return 0.15 * (static_cast<int>(m_groundEffect) - 50) / 50.0; }

std::string Floor::secondaryDescription() const {
    return "ground effect " + std::to_string(static_cast<int>(m_groundEffect));
}

}  // namespace f1
