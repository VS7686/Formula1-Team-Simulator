#pragma once

#include "CarPart.h"

namespace f1 {

class ICE : public CarPart {  // internal combustion engine
public:
    ICE(Rating rating, Rating reliability, Rating fuelEfficiency);
    // Multiplier on fuel burn per lap: 0.88 (efficient) .. 1.12 (thirsty).
    double fuelBurnMultiplier() const;
    std::string secondaryDescription() const override;

private:
    Rating m_fuelEfficiency;
};

class Turbo : public CarPart {
public:
    Turbo(Rating rating, Rating reliability, Rating response);
    // Corner-exit pace bonus in seconds (negative = faster).
    double paceDeltaSeconds() const;
    std::string secondaryDescription() const override;

private:
    Rating m_response;
};

class ERS : public CarPart {  // energy recovery system
public:
    ERS(Rating rating, Rating reliability, Rating deployment);
    // Scales how much lap time PUSH mode gains: 0.8 .. 1.2.
    double pushFactor() const;
    std::string secondaryDescription() const override;

private:
    Rating m_deployment;
};

class ControlElectronics : public CarPart {
public:
    ControlElectronics(Rating rating, Rating reliability, Rating mapping);
    // Scales how effective engine modes are: 0.8 .. 1.2.
    double engineModeFactor() const;
    std::string secondaryDescription() const override;

private:
    Rating m_mapping;
};

}  // namespace f1
