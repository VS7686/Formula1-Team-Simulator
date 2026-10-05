#pragma once

#include "Staff.h"

namespace f1 {

// Head of the R&D department: decides how well and how fast car upgrades are developed.
class ChiefDesigner : public Staff {
public:
    ChiefDesigner(std::string name, std::string nationality, int age, Money salary, int contractYears,
                  Rating potential, Rating innovation, Rating efficiency, Rating reliabilityFocus);

    Rating overallRating() const override;
    std::string role() const override { return "Chief Designer"; }
    Money marketValue() const override;

    // Probability that an R&D project (gain 1..5 rating points on a part of the given rating) succeeds.
    double projectSuccessChance(int targetGain, int currentPartRating) const;
    // Number of races an R&D project takes.
    int projectDurationRaces(int targetGain) const;

    Rating innovation() const { return m_innovation; }
    Rating efficiency() const { return m_efficiency; }
    Rating reliabilityFocus() const { return m_reliabilityFocus; }

private:
    Rating m_innovation;
    Rating m_efficiency;
    Rating m_reliabilityFocus;
};

}  // namespace f1
