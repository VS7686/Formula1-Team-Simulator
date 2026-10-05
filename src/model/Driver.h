#pragma once

#include <string>

#include "Staff.h"

namespace f1 {

// All the driving skills (1..100 each).
struct DriverStats {
    Rating pace{50};            // raw speed
    Rating consistency{50};     // fewer mistakes, less lap-time noise
    Rating racecraft{50};       // overtaking and defending
    Rating aggression{50};      // helps overtaking but raises incident risk
    Rating tyreManagement{50};  // lower tyre wear
    Rating wetSkill{50};        // speed and safety in the rain
    Rating experience{50};
    Rating startSkill{50};      // standing-start launch
};

class Driver : public Staff {
public:
    Driver(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential,
           DriverStats stats, int number, std::string code, std::string helmetColor = "#ffffff");

    Rating overallRating() const override;
    std::string role() const override { return "Driver"; }
    Money marketValue() const override;
    void print(std::ostream& os) const override;

    // Pace used in the lap-time model (wet weather mixes in wet skill; morale scales the result).
    double effectivePace(bool wet) const;
    // Standard deviation (seconds) of random lap-to-lap variation.
    double lapNoiseSigma() const;
    // Multiplier on tyre wear: 0.8 (great) .. 1.2 (poor).
    double wearFactor() const;

    const DriverStats& stats() const { return m_stats; }
    int number() const { return m_number; }
    const std::string& code() const { return m_code; }
    const std::string& helmetColor() const { return m_helmetColor; }

private:
    DriverStats m_stats;
    int m_number;
    std::string m_code;  // 3-letter timing-screen code
    std::string m_helmetColor;
};

}  // namespace f1
