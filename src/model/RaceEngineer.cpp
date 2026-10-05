#include "RaceEngineer.h"

#include <cmath>

namespace f1 {

RaceEngineer::RaceEngineer(std::string name, std::string nationality, int age, Money salary, int contractYears,
                           Rating potential, Rating strategyIQ, Rating dataAnalysis, Rating communication)
    : Staff(std::move(name), std::move(nationality), age, salary, contractYears, potential),
      m_strategyIQ(strategyIQ),
      m_dataAnalysis(dataAnalysis),
      m_communication(communication) {}

Rating RaceEngineer::overallRating() const {
    return Rating(static_cast<int>(std::lround(0.4 * m_strategyIQ + 0.4 * m_dataAnalysis + 0.2 * m_communication)));
}

double RaceEngineer::infoNoise() const { return (100 - static_cast<int>(m_dataAnalysis)) / 100.0; }

double RaceEngineer::badAdviceChance() const { return (100 - static_cast<int>(m_strategyIQ)) / 100.0 * 0.5; }

}  // namespace f1
