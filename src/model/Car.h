#pragma once

#include <iosfwd>
#include <memory>
#include <vector>

#include "AeroParts.h"
#include "ChassisParts.h"
#include "Circuit.h"
#include "PowerUnit.h"

namespace f1 {

// Setup chosen by the team for a weekend.
struct Setup {
    int wingSetting = 0;         // -5 (max speed) .. +5 (max downforce)
    double setupKnowledge = 0.0; // 0..1, learned in practice sessions
};

// A car owns all its parts and combines them into performance scores for a given circuit.
class Car {
public:
    Car(std::unique_ptr<FrontWing> frontWing, std::unique_ptr<RearWing> rearWing, std::unique_ptr<Floor> floor,
        std::unique_ptr<Suspension> suspension, std::unique_ptr<Chassis> chassis, std::unique_ptr<Brakes> brakes,
        std::unique_ptr<Gearbox> gearbox, std::unique_ptr<PowerUnit> powerUnit);

    // Convenience: a car where every part has the same rating (handy for tests and demos).
    static std::unique_ptr<Car> createUniform(int rating, int reliability = 70);

    // --- aggregate scores (0..100) ---
    double powerScore() const;       // engine side
    double aeroScore() const;        // downforce side
    double mechScore() const;        // mechanical grip side
    double effectivePower() const;   // power after the wing setting trade-off
    double effectiveAero() const;    // downforce after the wing setting trade-off
    // Overall car performance on one circuit, weighted by what that circuit rewards.
    double carScore(const Circuit& circuit) const;
    // Overall circuit-independent rating for the UI.
    double overallCarRating() const;
    double averageReliability() const;

    // --- lap-time effects (seconds per lap; lower is faster) ---
    double setupPenaltySeconds(const Circuit& circuit, double mechanicSkill) const;
    double carDeltaSeconds(const Circuit& circuit, double mechanicSkill) const;

    // --- setup ---
    void setWingSetting(int wing);
    const Setup& setup() const { return m_setup; }

    // --- parts ---
    std::vector<const CarPart*> allParts() const;
    std::vector<CarPart*> allParts();
    CarPart* findPart(PartType type);
    void wearAllParts(double laps, double loadFactor, double mechanicMult);

    const FrontWing& frontWing() const { return *m_frontWing; }
    const RearWing& rearWing() const { return *m_rearWing; }
    const Floor& floor() const { return *m_floor; }
    const Suspension& suspension() const { return *m_suspension; }
    const Chassis& chassis() const { return *m_chassis; }
    const Brakes& brakes() const { return *m_brakes; }
    const Gearbox& gearbox() const { return *m_gearbox; }
    const PowerUnit& powerUnit() const { return *m_powerUnit; }

private:
    std::unique_ptr<FrontWing> m_frontWing;
    std::unique_ptr<RearWing> m_rearWing;
    std::unique_ptr<Floor> m_floor;
    std::unique_ptr<Suspension> m_suspension;
    std::unique_ptr<Chassis> m_chassis;
    std::unique_ptr<Brakes> m_brakes;
    std::unique_ptr<Gearbox> m_gearbox;
    std::unique_ptr<PowerUnit> m_powerUnit;
    Setup m_setup;
};

std::ostream& operator<<(std::ostream& os, const Car& car);

}  // namespace f1
