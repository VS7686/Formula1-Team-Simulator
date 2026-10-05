#pragma once

#include "CarPart.h"

namespace f1 {

class Suspension : public CarPart {
public:
    Suspension(Rating rating, Rating reliability, Rating tyreFriendliness);
    // Multiplier on tyre wear: 0.85 (gentle) .. 1.15 (harsh).
    double tyreWearFactor() const;
    std::string secondaryDescription() const override;

private:
    Rating m_tyreFriendliness;
};

class Chassis : public CarPart {
public:
    Chassis(Rating rating, Rating reliability, Rating crashResistance);
    // Multiplier on crash damage: 0.7 (strong) .. 1.3 (fragile).
    double damageMultiplier() const;
    std::string secondaryDescription() const override;

private:
    Rating m_crashResistance;
};

class Brakes : public CarPart {
public:
    Brakes(Rating rating, Rating reliability, Rating fadeResistance);
    // Lap-time penalty (seconds) on circuits with heavy braking (brakeSeverity 0..1).
    double fadePenaltySeconds(double brakeSeverity) const;
    std::string secondaryDescription() const override;

private:
    Rating m_fadeResistance;
};

class Gearbox : public CarPart {
public:
    Gearbox(Rating rating, Rating reliability, Rating shiftSpeed);
    // Small lap-time bonus in seconds (negative = faster).
    double paceDeltaSeconds() const;
    std::string secondaryDescription() const override;

private:
    Rating m_shiftSpeed;
};

}  // namespace f1
