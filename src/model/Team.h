#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "../core/Money.h"
#include "../core/Rating.h"
#include "Car.h"
#include "ChiefDesigner.h"
#include "Driver.h"
#include "Mechanic.h"
#include "PitCrew.h"
#include "RaceEngineer.h"

namespace f1 {

// A team owns a car, two race drivers and its support staff, and has a budget.
class Team {
public:
    static constexpr std::size_t kMaxDrivers = 2;
    static constexpr std::size_t kMaxMechanics = 4;

    Team(std::string name, std::string shortName, std::string colorHex, Money budget, std::unique_ptr<Car> car,
         int reputation = 40);

    // Hires any kind of staff. The concrete type decides which slot is filled (dynamic_cast).
    // Throws ContractException when the slot is full or the person is already employed.
    void hire(const std::shared_ptr<Staff>& staff);
    // Releases a staff member; breaking a contract costs 50% of the remaining salary.
    void release(int staffId);

    // --- money ---
    bool canAfford(const Money& amount) const { return m_budget >= amount; }
    void spend(const Money& amount);  // throws InsufficientFundsException
    void earn(const Money& amount) { m_budget += amount; }
    Money totalSalariesPerSeason() const;
    // Pays one race's share of salaries plus operating costs; returns the amount paid.
    Money payRaceCosts(int racesInSeason);

    // --- ratings used by the simulation and the UI ---
    double mechanicSkill() const;        // average of 4 slots (an empty slot counts as 30)
    double partWearMultiplier() const;   // from mechanics' diligence
    double carDeltaSeconds(const Circuit& circuit) const;  // lap-time cost of this car on that circuit
    Rating overallRating() const;        // 45% car, 30% drivers, 10% pit crew, 10% engineer, 5% mechanics

    std::vector<std::shared_ptr<Staff>> allStaff() const;
    void printSummary(std::ostream& os) const;

    // --- getters ---
    const std::string& name() const { return m_name; }
    const std::string& shortName() const { return m_shortName; }
    const std::string& colorHex() const { return m_colorHex; }
    Rating reputation() const { return m_reputation; }
    Money budget() const { return m_budget; }
    Car& car() { return *m_car; }
    const Car& car() const { return *m_car; }
    const std::vector<std::shared_ptr<Driver>>& drivers() const { return m_drivers; }
    const std::vector<std::shared_ptr<Mechanic>>& mechanics() const { return m_mechanics; }
    const std::shared_ptr<PitCrew>& pitCrew() const { return m_pitCrew; }
    const std::shared_ptr<RaceEngineer>& raceEngineer() const { return m_raceEngineer; }
    const std::shared_ptr<ChiefDesigner>& chiefDesigner() const { return m_chiefDesigner; }

private:
    std::string m_name;
    std::string m_shortName;
    std::string m_colorHex;
    Rating m_reputation;
    Money m_budget;
    std::unique_ptr<Car> m_car;
    std::vector<std::shared_ptr<Driver>> m_drivers;
    std::vector<std::shared_ptr<Mechanic>> m_mechanics;
    std::shared_ptr<PitCrew> m_pitCrew;
    std::shared_ptr<RaceEngineer> m_raceEngineer;
    std::shared_ptr<ChiefDesigner> m_chiefDesigner;
};

}  // namespace f1
