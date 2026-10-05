#include "ChassisParts.h"

namespace f1 {

Suspension::Suspension(Rating rating, Rating reliability, Rating tyreFriendliness)
    : CarPart(PartType::SUSPENSION, "Suspension", rating, reliability, Money::fromMillions(2.5)),
      m_tyreFriendliness(tyreFriendliness) {}

double Suspension::tyreWearFactor() const { return 1.15 - static_cast<int>(m_tyreFriendliness) / 100.0 * 0.30; }

std::string Suspension::secondaryDescription() const {
    return "tyre friendliness " + std::to_string(static_cast<int>(m_tyreFriendliness));
}

Chassis::Chassis(Rating rating, Rating reliability, Rating crashResistance)
    : CarPart(PartType::CHASSIS, "Chassis", rating, reliability, Money::fromMillions(5.0)),
      m_crashResistance(crashResistance) {}

double Chassis::damageMultiplier() const { return 1.3 - static_cast<int>(m_crashResistance) / 100.0 * 0.6; }

std::string Chassis::secondaryDescription() const {
    return "crash resistance " + std::to_string(static_cast<int>(m_crashResistance));
}

Brakes::Brakes(Rating rating, Rating reliability, Rating fadeResistance)
    : CarPart(PartType::BRAKES, "Brakes", rating, reliability, Money::fromMillions(1.5)),
      m_fadeResistance(fadeResistance) {}

double Brakes::fadePenaltySeconds(double brakeSeverity) const {
    if (brakeSeverity <= 0.7) return 0.0;
    return 0.25 * (100 - static_cast<int>(m_fadeResistance)) / 100.0;
}

std::string Brakes::secondaryDescription() const {
    return "fade resistance " + std::to_string(static_cast<int>(m_fadeResistance));
}

Gearbox::Gearbox(Rating rating, Rating reliability, Rating shiftSpeed)
    : CarPart(PartType::GEARBOX, "Gearbox", rating, reliability, Money::fromMillions(2.5)),
      m_shiftSpeed(shiftSpeed) {}

double Gearbox::paceDeltaSeconds() const { return -0.10 * (static_cast<int>(m_shiftSpeed) - 50) / 50.0; }

std::string Gearbox::secondaryDescription() const {
    return "shift speed " + std::to_string(static_cast<int>(m_shiftSpeed));
}

}  // namespace f1
