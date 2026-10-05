#include "Team.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <ostream>

#include "../core/Exceptions.h"

namespace f1 {

Team::Team(std::string name, std::string shortName, std::string colorHex, Money budget, std::unique_ptr<Car> car,
           int reputation)
    : m_name(std::move(name)),
      m_shortName(std::move(shortName)),
      m_colorHex(std::move(colorHex)),
      m_reputation(reputation),
      m_budget(budget),
      m_car(std::move(car)) {
    if (!m_car) throw InvalidStateException("A team needs a car");
}

void Team::hire(const std::shared_ptr<Staff>& staff) {
    if (!staff) throw ContractException("Cannot hire a null staff member");
    for (const auto& s : allStaff())
        if (s->id() == staff->id()) throw ContractException(staff->name() + " already works for this team");

    if (auto driver = std::dynamic_pointer_cast<Driver>(staff)) {
        if (m_drivers.size() >= kMaxDrivers) throw ContractException("Team already has two race drivers");
        m_drivers.push_back(driver);
    } else if (auto mechanic = std::dynamic_pointer_cast<Mechanic>(staff)) {
        if (m_mechanics.size() >= kMaxMechanics) throw ContractException("Team already has four mechanics");
        m_mechanics.push_back(mechanic);
    } else if (auto crew = std::dynamic_pointer_cast<PitCrew>(staff)) {
        if (m_pitCrew) throw ContractException("Team already has a pit crew - release it first");
        m_pitCrew = crew;
    } else if (auto engineer = std::dynamic_pointer_cast<RaceEngineer>(staff)) {
        if (m_raceEngineer) throw ContractException("Team already has a race engineer - release it first");
        m_raceEngineer = engineer;
    } else if (auto designer = std::dynamic_pointer_cast<ChiefDesigner>(staff)) {
        if (m_chiefDesigner) throw ContractException("Team already has a chief designer - release it first");
        m_chiefDesigner = designer;
    } else {
        throw ContractException("Unknown kind of staff");
    }
}

void Team::release(int staffId) {
    const auto staff = allStaff();
    const auto it = std::find_if(staff.begin(), staff.end(), [&](const auto& s) { return s->id() == staffId; });
    if (it == staff.end()) throw ContractException("No staff member with that id in this team");

    // Pay the release fee first: if the team cannot afford it, nothing changes.
    spend((*it)->salary() * ((*it)->contractYears() * 0.5));

    const auto sameId = [&](const auto& s) { return s->id() == staffId; };
    m_drivers.erase(std::remove_if(m_drivers.begin(), m_drivers.end(), sameId), m_drivers.end());
    m_mechanics.erase(std::remove_if(m_mechanics.begin(), m_mechanics.end(), sameId), m_mechanics.end());
    if (m_pitCrew && m_pitCrew->id() == staffId) m_pitCrew.reset();
    if (m_raceEngineer && m_raceEngineer->id() == staffId) m_raceEngineer.reset();
    if (m_chiefDesigner && m_chiefDesigner->id() == staffId) m_chiefDesigner.reset();
}

void Team::spend(const Money& amount) {
    if (amount > m_budget) throw InsufficientFundsException(amount, m_budget);
    m_budget -= amount;
}

Money Team::totalSalariesPerSeason() const {
    Money total;
    for (const auto& s : allStaff()) total += s->salary();
    return total;
}

Money Team::payRaceCosts(int racesInSeason) {
    if (racesInSeason <= 0) throw InvalidStateException("Season needs at least one race");
    const Money salaries = totalSalariesPerSeason() * (1.0 / racesInSeason);
    const Money operations = Money::fromMillions(1.2 + 0.05 * static_cast<double>(allStaff().size()));
    const Money total = salaries + operations;
    spend(total);
    return total;
}

double Team::mechanicSkill() const {
    double sum = 30.0 * static_cast<double>(kMaxMechanics - m_mechanics.size());
    for (const auto& m : m_mechanics) sum += static_cast<int>(m->skill());
    return sum / static_cast<double>(kMaxMechanics);
}

double Team::partWearMultiplier() const {
    // Empty mechanic slots behave like a careless mechanic (diligence 30 -> multiplier 1.08).
    double sum = 1.08 * static_cast<double>(kMaxMechanics - m_mechanics.size());
    for (const auto& m : m_mechanics) sum += m->partWearMultiplier();
    return sum / static_cast<double>(kMaxMechanics);
}

double Team::carDeltaSeconds(const Circuit& circuit) const { return m_car->carDeltaSeconds(circuit, mechanicSkill()); }

Rating Team::overallRating() const {
    double drivers = 30.0;
    if (!m_drivers.empty()) {
        drivers = std::accumulate(m_drivers.begin(), m_drivers.end(), 0.0,
                                  [](double acc, const auto& d) { return acc + static_cast<int>(d->overallRating()); }) /
                  static_cast<double>(m_drivers.size());
    }
    const double pit = m_pitCrew ? static_cast<int>(m_pitCrew->overallRating()) : 30.0;
    const double eng = m_raceEngineer ? static_cast<int>(m_raceEngineer->overallRating()) : 30.0;
    const double value = 0.45 * m_car->overallCarRating() + 0.30 * drivers + 0.10 * pit + 0.10 * eng +
                         0.05 * mechanicSkill();
    return Rating(static_cast<int>(std::lround(value)));
}

std::vector<std::shared_ptr<Staff>> Team::allStaff() const {
    std::vector<std::shared_ptr<Staff>> staff;
    staff.insert(staff.end(), m_drivers.begin(), m_drivers.end());
    staff.insert(staff.end(), m_mechanics.begin(), m_mechanics.end());
    if (m_pitCrew) staff.push_back(m_pitCrew);
    if (m_raceEngineer) staff.push_back(m_raceEngineer);
    if (m_chiefDesigner) staff.push_back(m_chiefDesigner);
    return staff;
}

void Team::printSummary(std::ostream& os) const {
    os << "=== " << m_name << " (" << m_shortName << ") ===  budget " << m_budget << ", reputation " << m_reputation
       << ", overall rating " << overallRating() << '\n';
    for (const auto& s : allStaff()) os << "  " << *s << '\n';
}

}  // namespace f1
