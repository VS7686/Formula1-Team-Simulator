#pragma once

#include "CarPart.h"

namespace f1 {

class FrontWing : public CarPart {
public:
    FrontWing(Rating rating, Rating reliability, Rating airflowControl);
    // Multiplier on the lap-time loss when following another car (0.7 .. 1.3).
    double dirtyAirMultiplier() const;
    std::string secondaryDescription() const override;

private:
    Rating m_airflowControl;
};

class RearWing : public CarPart {
public:
    RearWing(Rating rating, Rating reliability, Rating dragEfficiency);
    // Small top-speed bonus/penalty on the engine power score.
    double powerMultiplier() const;
    std::string secondaryDescription() const override;
    Rating dragEfficiency() const { return m_dragEfficiency; }

private:
    Rating m_dragEfficiency;
};

class Floor : public CarPart {
public:
    Floor(Rating rating, Rating reliability, Rating groundEffect);
    // Extra downforce from ground effect, as a fraction of the aero score (-0.15 .. +0.15).
    double aeroBonusFraction() const;
    std::string secondaryDescription() const override;

private:
    Rating m_groundEffect;
};

}  // namespace f1
