#include "TyreSet.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

namespace f1 {

const CompoundInfo& TyreSet::info(TyreCompound compound) {
    static const CompoundInfo table[] = {
        {"Soft",         'S', 0.00, 3.8, 68.0},
        {"Medium",       'M', 0.55, 2.6, 74.0},
        {"Hard",         'H', 1.05, 1.9, 80.0},
        {"Intermediate", 'I', 0.80, 6.0, 70.0},  // wear shown for a dry track
        {"Wet",          'W', 2.00, 9.0, 65.0},  // wear shown for a dry track
    };
    return table[static_cast<int>(compound)];
}

void TyreSet::addLap(double wearPercent) {
    m_wear = std::min(100.0, m_wear + wearPercent);
    ++m_lapsUsed;
}

double TyreSet::performanceLossSeconds() const {
    const double smooth = 1.6 * (m_wear / 100.0) * (m_wear / 100.0);
    const double cliff = std::max(0.0, m_wear - info(m_compound).cliffWear) * 0.09;
    return smooth + cliff;
}

std::string TyreSet::describe() const {
    std::ostringstream os;
    os << info(m_compound).name << " (" << m_lapsUsed << " laps, wear " << std::fixed << std::setprecision(1) << m_wear
       << "%)";
    return os.str();
}

}  // namespace f1
