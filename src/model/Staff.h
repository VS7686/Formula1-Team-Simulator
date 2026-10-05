#pragma once

#include <iosfwd>
#include <string>

#include "../core/Money.h"
#include "../core/Rating.h"

namespace f1 {

// Abstract base class for every person on a team (driver, mechanic, pit crew, ...).
class Staff {
public:
    Staff(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential);
    virtual ~Staff() = default;

    // Each kind of staff computes its own overall rating (pure virtual -> abstract class).
    virtual Rating overallRating() const = 0;
    virtual std::string role() const = 0;
    // Value on the transfer market, per season. Subclasses override with their own scale.
    virtual Money marketValue() const;
    virtual void print(std::ostream& os) const;

    // Morale 1..100 scales the main skills between 90% and 100%.
    double moraleFactor() const { return 0.90 + 0.10 * static_cast<int>(m_morale) / 100.0; }
    void adjustMorale(int delta) { m_morale += delta; }

    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    const std::string& nationality() const { return m_nationality; }
    int age() const { return m_age; }
    Money salary() const { return m_salary; }
    int contractYears() const { return m_contractYears; }
    Rating morale() const { return m_morale; }
    Rating potential() const { return m_potential; }

    void setSalary(Money salary) { m_salary = salary; }
    void setContractYears(int years);

protected:
    // Market value helper: scale * exp(growth * (overall - 30)), in millions of dollars.
    Money exponentialValue(double scaleMillions, double growth) const;

private:
    int m_id;
    std::string m_name;
    std::string m_nationality;
    int m_age;
    Money m_salary;
    int m_contractYears;
    Rating m_morale{60};
    Rating m_potential;
};

std::ostream& operator<<(std::ostream& os, const Staff& s);

}  // namespace f1
