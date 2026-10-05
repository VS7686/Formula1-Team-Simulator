#pragma once

#include <string>

#include "../core/Enums.h"

namespace f1 {

// Fixed properties of each compound (starting values; later loaded from a balance file).
struct CompoundInfo {
    const char* name;
    char letter;
    double paceOffsetSeconds;  // slower than soft by this much per lap
    double baseWearPerLap;     // wear % per lap on a full-length race
    double cliffWear;          // after this wear % lap times fall off a cliff
};

class TyreSet {
public:
    explicit TyreSet(TyreCompound compound) : m_compound(compound) {}

    static const CompoundInfo& info(TyreCompound compound);

    TyreCompound compound() const { return m_compound; }
    double wear() const { return m_wear; }  // 0..100 %
    int lapsUsed() const { return m_lapsUsed; }

    // Adds one lap of use with the given wear (percentage points).
    void addLap(double wearPercent);
    bool pastCliff() const { return m_wear > info(m_compound).cliffWear; }
    // Seconds per lap lost because of wear: smooth curve + steep penalty beyond the cliff.
    double performanceLossSeconds() const;

    std::string describe() const;

private:
    TyreCompound m_compound;
    double m_wear = 0.0;
    int m_lapsUsed = 0;
};

}  // namespace f1
