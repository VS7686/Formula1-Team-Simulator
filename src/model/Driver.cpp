#include "Driver.h"

#include <cmath>
#include <ostream>

#include "../core/Exceptions.h"

namespace f1 {

Driver::Driver(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential,
               DriverStats stats, int number, std::string code, std::string helmetColor)
    : Staff(std::move(name), std::move(nationality), age, salary, contractYears, potential),
      m_stats(stats),
      m_number(number),
      m_code(std::move(code)),
      m_helmetColor(std::move(helmetColor)) {
    if (m_code.size() != 3) throw InvalidStateException("Driver code must be exactly 3 letters");
    if (m_number < 1 || m_number > 99) throw InvalidStateException("Driver number must be 1-99");
}

Rating Driver::overallRating() const {
    const double v = 0.40 * m_stats.pace + 0.15 * m_stats.consistency + 0.15 * m_stats.racecraft +
                     0.10 * m_stats.tyreManagement + 0.10 * m_stats.wetSkill + 0.05 * m_stats.experience +
                     0.05 * m_stats.startSkill;
    return Rating(static_cast<int>(std::lround(v)));
}

Money Driver::marketValue() const { return exponentialValue(0.5, 0.06); }

double Driver::effectivePace(bool wet) const {
    const double base = wet ? 0.6 * m_stats.pace + 0.4 * m_stats.wetSkill : static_cast<double>(m_stats.pace);
    return base * moraleFactor();
}

double Driver::lapNoiseSigma() const { return 0.08 + (100 - static_cast<int>(m_stats.consistency)) / 100.0 * 0.45; }

double Driver::wearFactor() const { return 1.20 - static_cast<int>(m_stats.tyreManagement) / 100.0 * 0.40; }

void Driver::print(std::ostream& os) const {
    Staff::print(os);
    os << "\n                 #" << m_number << " [" << m_code << "]  pace " << m_stats.pace << ", consistency "
       << m_stats.consistency << ", racecraft " << m_stats.racecraft << ", aggression " << m_stats.aggression
       << ", tyres " << m_stats.tyreManagement << ", wet " << m_stats.wetSkill;
}

}  // namespace f1
