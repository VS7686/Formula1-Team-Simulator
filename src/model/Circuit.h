#pragma once

#include <iosfwd>
#include <string>

#include "../core/LapTime.h"

namespace f1 {

// Plain description of a circuit (later this can be filled from a JSON file).
struct CircuitSpec {
    std::string id;
    std::string name;
    std::string country;
    double lapLengthKm = 5.0;
    int realLapCount = 50;
    double baseLapSeconds = 90.0;      // lap of a perfect car/driver on soft tyres, empty tank, dry
    double tyreSeverity = 1.0;         // multiplies tyre wear (0.7 gentle .. 1.3 harsh)
    double overtakingDifficulty = 0.5; // 0 easy .. 1 almost impossible (Monaco)
    double pitLaneLoss = 21.0;         // seconds lost by driving through the pit lane
    double wPower = 0.34;              // how much engine power matters here
    double wAero = 0.33;               // how much downforce matters here
    double wMech = 0.33;               // how much mechanical grip matters here
    int idealWing = 0;                 // best wing setting, -5 (low downforce) .. +5 (high downforce)
    double rainProbability = 0.1;      // chance of rain during the race
    double brakeSeverity = 0.5;
};

class Circuit {
public:
    explicit Circuit(const CircuitSpec& spec);

    const std::string& id() const { return m_spec.id; }
    const std::string& name() const { return m_spec.name; }
    const std::string& country() const { return m_spec.country; }
    double lapLengthKm() const { return m_spec.lapLengthKm; }
    int realLapCount() const { return m_spec.realLapCount; }
    LapTime baseLapTime() const { return LapTime::fromSeconds(m_spec.baseLapSeconds); }
    double tyreSeverity() const { return m_spec.tyreSeverity; }
    double overtakingDifficulty() const { return m_spec.overtakingDifficulty; }
    double pitLaneLoss() const { return m_spec.pitLaneLoss; }
    double wPower() const { return m_spec.wPower; }
    double wAero() const { return m_spec.wAero; }
    double wMech() const { return m_spec.wMech; }
    int idealWing() const { return m_spec.idealWing; }
    double rainProbability() const { return m_spec.rainProbability; }
    double brakeSeverity() const { return m_spec.brakeSeverity; }

    // Race length in laps: real lap count scaled by the distance factor (0.5 = half distance).
    int totalLaps(double raceDistanceFactor) const;

    static int count() { return s_count; }

private:
    CircuitSpec m_spec;
    static inline int s_count = 0;
};

std::ostream& operator<<(std::ostream& os, const Circuit& c);

}  // namespace f1
