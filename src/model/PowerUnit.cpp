#include "PowerUnit.h"

#include "../core/Exceptions.h"

namespace f1 {

PowerUnit::PowerUnit(std::unique_ptr<ICE> ice, std::unique_ptr<Turbo> turbo, std::unique_ptr<ERS> ers,
                     std::unique_ptr<ControlElectronics> electronics)
    : m_ice(std::move(ice)), m_turbo(std::move(turbo)), m_ers(std::move(ers)), m_electronics(std::move(electronics)) {
    if (!m_ice || !m_turbo || !m_ers || !m_electronics) throw InvalidStateException("PowerUnit needs all four parts");
}

double PowerUnit::powerScore() const {
    return 0.45 * m_ice->effectiveRating() + 0.20 * m_turbo->effectiveRating() + 0.25 * m_ers->effectiveRating() +
           0.10 * m_electronics->effectiveRating();
}

std::vector<CarPart*> PowerUnit::parts() { return {m_ice.get(), m_turbo.get(), m_ers.get(), m_electronics.get()}; }

std::vector<const CarPart*> PowerUnit::parts() const {
    return {m_ice.get(), m_turbo.get(), m_ers.get(), m_electronics.get()};
}

}  // namespace f1
