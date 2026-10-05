#pragma once

#include <memory>
#include <vector>

#include "PowerUnitParts.h"

namespace f1 {

// Composite object: the power unit is made of four parts and combines them into one power score.
class PowerUnit {
public:
    PowerUnit(std::unique_ptr<ICE> ice, std::unique_ptr<Turbo> turbo, std::unique_ptr<ERS> ers,
              std::unique_ptr<ControlElectronics> electronics);

    // 0..100: 45% engine, 20% turbo, 25% ERS, 10% electronics (using each part's effective rating).
    double powerScore() const;
    double fuelBurnFactor() const { return m_ice->fuelBurnMultiplier(); }

    const ICE& ice() const { return *m_ice; }
    const Turbo& turbo() const { return *m_turbo; }
    const ERS& ers() const { return *m_ers; }
    const ControlElectronics& electronics() const { return *m_electronics; }

    std::vector<CarPart*> parts();
    std::vector<const CarPart*> parts() const;

private:
    std::unique_ptr<ICE> m_ice;
    std::unique_ptr<Turbo> m_turbo;
    std::unique_ptr<ERS> m_ers;
    std::unique_ptr<ControlElectronics> m_electronics;
};

}  // namespace f1
