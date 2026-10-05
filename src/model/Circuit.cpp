#include "Circuit.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ostream>

#include "../core/Exceptions.h"

namespace f1 {

Circuit::Circuit(const CircuitSpec& spec) : m_spec(spec) {
    if (m_spec.name.empty()) throw InvalidStateException("Circuit needs a name");
    if (std::fabs(m_spec.wPower + m_spec.wAero + m_spec.wMech - 1.0) > 0.01)
        throw InvalidStateException("Circuit weights (power/aero/mech) must sum to 1.0");
    if (m_spec.idealWing < -5 || m_spec.idealWing > 5) throw InvalidStateException("Ideal wing must be -5..+5");
    ++s_count;
}

int Circuit::totalLaps(double raceDistanceFactor) const {
    return std::max(5, static_cast<int>(std::lround(m_spec.realLapCount * raceDistanceFactor)));
}

std::ostream& operator<<(std::ostream& os, const Circuit& c) {
    os << c.name() << " (" << c.country() << "), " << std::fixed << std::setprecision(3) << c.lapLengthKm() << " km, "
       << c.realLapCount() << " laps, base lap " << c.baseLapTime() << ", tyre severity " << std::setprecision(2)
       << c.tyreSeverity() << ", overtaking difficulty " << c.overtakingDifficulty();
    return os;
}

}  // namespace f1
