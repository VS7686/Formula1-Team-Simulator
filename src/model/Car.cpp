#include "Car.h"

#include <algorithm>
#include <cmath>
#include <ostream>

#include "../core/Constants.h"
#include "../core/Exceptions.h"

namespace f1 {

Car::Car(std::unique_ptr<FrontWing> frontWing, std::unique_ptr<RearWing> rearWing, std::unique_ptr<Floor> floor,
         std::unique_ptr<Suspension> suspension, std::unique_ptr<Chassis> chassis, std::unique_ptr<Brakes> brakes,
         std::unique_ptr<Gearbox> gearbox, std::unique_ptr<PowerUnit> powerUnit)
    : m_frontWing(std::move(frontWing)),
      m_rearWing(std::move(rearWing)),
      m_floor(std::move(floor)),
      m_suspension(std::move(suspension)),
      m_chassis(std::move(chassis)),
      m_brakes(std::move(brakes)),
      m_gearbox(std::move(gearbox)),
      m_powerUnit(std::move(powerUnit)) {
    if (!m_frontWing || !m_rearWing || !m_floor || !m_suspension || !m_chassis || !m_brakes || !m_gearbox ||
        !m_powerUnit)
        throw InvalidStateException("A car needs all of its parts");
}

std::unique_ptr<Car> Car::createUniform(int rating, int reliability) {
    auto unit = std::make_unique<PowerUnit>(
        std::make_unique<ICE>(rating, reliability, rating), std::make_unique<Turbo>(rating, reliability, rating),
        std::make_unique<ERS>(rating, reliability, rating),
        std::make_unique<ControlElectronics>(rating, reliability, rating));
    return std::make_unique<Car>(std::make_unique<FrontWing>(rating, reliability, rating),
                                 std::make_unique<RearWing>(rating, reliability, rating),
                                 std::make_unique<Floor>(rating, reliability, rating),
                                 std::make_unique<Suspension>(rating, reliability, rating),
                                 std::make_unique<Chassis>(rating, reliability, rating),
                                 std::make_unique<Brakes>(rating, reliability, rating),
                                 std::make_unique<Gearbox>(rating, reliability, rating), std::move(unit));
}

double Car::powerScore() const { return m_powerUnit->powerScore(); }

double Car::aeroScore() const {
    const double base = 0.32 * m_frontWing->effectiveRating() + 0.32 * m_rearWing->effectiveRating() +
                        0.36 * m_floor->effectiveRating();
    return base * (1.0 + m_floor->aeroBonusFraction());
}

double Car::mechScore() const {
    return 0.55 * m_suspension->effectiveRating() + 0.30 * m_chassis->effectiveRating() +
           0.15 * m_brakes->effectiveRating();
}

double Car::effectivePower() const {
    return powerScore() * (1.0 - 0.025 * m_setup.wingSetting) * m_rearWing->powerMultiplier();
}

double Car::effectiveAero() const { return aeroScore() * (1.0 + 0.040 * m_setup.wingSetting); }

double Car::carScore(const Circuit& circuit) const {
    const double score = circuit.wPower() * effectivePower() + circuit.wAero() * effectiveAero() +
                         circuit.wMech() * mechScore();
    return std::clamp(score, 1.0, 100.0);
}

double Car::overallCarRating() const { return (powerScore() + aeroScore() + mechScore()) / 3.0; }

double Car::averageReliability() const {
    const auto parts = allParts();
    double sum = 0.0;
    for (const CarPart* p : parts) sum += static_cast<int>(p->reliability());
    return sum / static_cast<double>(parts.size());
}

double Car::setupPenaltySeconds(const Circuit& circuit, double mechanicSkill) const {
    const int error = std::abs(m_setup.wingSetting - circuit.idealWing());
    return 0.08 * error * (1.0 - 0.5 * mechanicSkill / 100.0) * (1.0 - 0.7 * m_setup.setupKnowledge);
}

double Car::carDeltaSeconds(const Circuit& circuit, double mechanicSkill) const {
    return (100.0 - carScore(circuit)) / 100.0 * constants::kCarRange + setupPenaltySeconds(circuit, mechanicSkill);
}

void Car::setWingSetting(int wing) {
    if (wing < -5 || wing > 5) throw InvalidStateException("Wing setting must be between -5 and +5");
    m_setup.wingSetting = wing;
}

std::vector<const CarPart*> Car::allParts() const {
    std::vector<const CarPart*> parts{m_frontWing.get(), m_rearWing.get(), m_floor.get(), m_suspension.get(),
                                      m_chassis.get(),   m_brakes.get(),   m_gearbox.get()};
    for (const CarPart* p : static_cast<const PowerUnit&>(*m_powerUnit).parts()) parts.push_back(p);
    return parts;
}

std::vector<CarPart*> Car::allParts() {
    std::vector<CarPart*> parts{m_frontWing.get(), m_rearWing.get(), m_floor.get(), m_suspension.get(),
                                m_chassis.get(),   m_brakes.get(),   m_gearbox.get()};
    for (CarPart* p : m_powerUnit->parts()) parts.push_back(p);
    return parts;
}

CarPart* Car::findPart(PartType type) {
    for (CarPart* p : allParts())
        if (p->type() == type) return p;
    return nullptr;
}

void Car::wearAllParts(double laps, double loadFactor, double mechanicMult) {
    for (CarPart* p : allParts()) p->wear(laps, loadFactor, mechanicMult);
}

std::ostream& operator<<(std::ostream& os, const Car& car) {
    for (const CarPart* p : car.allParts()) os << "  " << *p << '\n';
    return os;
}

}  // namespace f1
