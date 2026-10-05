#include "PowerUnitParts.h"

namespace f1 {

ICE::ICE(Rating rating, Rating reliability, Rating fuelEfficiency)
    : CarPart(PartType::ICE, "Engine (ICE)", rating, reliability, Money::fromMillions(6.0)),
      m_fuelEfficiency(fuelEfficiency) {}

double ICE::fuelBurnMultiplier() const { return 1.12 - static_cast<int>(m_fuelEfficiency) / 100.0 * 0.24; }

std::string ICE::secondaryDescription() const {
    return "fuel efficiency " + std::to_string(static_cast<int>(m_fuelEfficiency));
}

Turbo::Turbo(Rating rating, Rating reliability, Rating response)
    : CarPart(PartType::TURBO, "Turbo", rating, reliability, Money::fromMillions(3.0)), m_response(response) {}

double Turbo::paceDeltaSeconds() const { return -0.08 * (static_cast<int>(m_response) - 50) / 50.0; }

std::string Turbo::secondaryDescription() const { return "response " + std::to_string(static_cast<int>(m_response)); }

ERS::ERS(Rating rating, Rating reliability, Rating deployment)
    : CarPart(PartType::ERS, "ERS", rating, reliability, Money::fromMillions(4.0)), m_deployment(deployment) {}

double ERS::pushFactor() const { return 0.8 + static_cast<int>(m_deployment) / 250.0; }

std::string ERS::secondaryDescription() const {
    return "deployment " + std::to_string(static_cast<int>(m_deployment));
}

ControlElectronics::ControlElectronics(Rating rating, Rating reliability, Rating mapping)
    : CarPart(PartType::CONTROL_ELECTRONICS, "Control Electronics", rating, reliability, Money::fromMillions(2.0)),
      m_mapping(mapping) {}

double ControlElectronics::engineModeFactor() const { return 0.8 + static_cast<int>(m_mapping) / 250.0; }

std::string ControlElectronics::secondaryDescription() const {
    return "mapping " + std::to_string(static_cast<int>(m_mapping));
}

}  // namespace f1
