#pragma once

#include "Staff.h"

namespace f1 {

// The race engineer is the player's source of information (tyre-wear estimates, rain forecast, advice).
class RaceEngineer : public Staff {
public:
    RaceEngineer(std::string name, std::string nationality, int age, Money salary, int contractYears,
                 Rating potential, Rating strategyIQ, Rating dataAnalysis, Rating communication);

    Rating overallRating() const override;
    std::string role() const override { return "Race Engineer"; }

    // 0 (perfect data) .. 1 (very noisy data). Scales the error on wear estimates and the rain forecast.
    double infoNoise() const;
    // Chance that a strategy suggestion is replaced by a worse one.
    double badAdviceChance() const;

    Rating strategyIQ() const { return m_strategyIQ; }
    Rating dataAnalysis() const { return m_dataAnalysis; }
    Rating communication() const { return m_communication; }

private:
    Rating m_strategyIQ;
    Rating m_dataAnalysis;
    Rating m_communication;
};

}  // namespace f1
