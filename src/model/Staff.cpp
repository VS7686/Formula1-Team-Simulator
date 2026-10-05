#include "Staff.h"

#include <cmath>
#include <iomanip>
#include <ostream>

#include "../core/Exceptions.h"
#include "../core/IdGenerator.h"

namespace f1 {

Staff::Staff(std::string name, std::string nationality, int age, Money salary, int contractYears, Rating potential)
    : m_id(IdGenerator::next()),
      m_name(std::move(name)),
      m_nationality(std::move(nationality)),
      m_age(age),
      m_salary(salary),
      m_contractYears(contractYears),
      m_potential(potential) {
    if (m_name.empty()) throw InvalidStateException("Staff name cannot be empty");
    if (m_age < 17 || m_age > 45) throw InvalidStateException("Staff age must be between 17 and 45");
    setContractYears(contractYears);
}

void Staff::setContractYears(int years) {
    if (years < 0 || years > 5) throw ContractException("Contract length must be 0-5 years");
    m_contractYears = years;
}

Money Staff::exponentialValue(double scaleMillions, double growth) const {
    const int overall = overallRating();
    return Money::fromMillions(scaleMillions * std::exp(growth * (overall - 30)));
}

Money Staff::marketValue() const { return exponentialValue(0.25, 0.05); }

void Staff::print(std::ostream& os) const {
    os << std::left << std::setw(15) << role() << std::setw(18) << m_name << " age " << m_age << ", "
       << std::setw(10) << m_nationality << " overall " << std::setw(3) << overallRating() << " salary "
       << m_salary << "/season, contract " << m_contractYears << "y";
}

std::ostream& operator<<(std::ostream& os, const Staff& s) {
    s.print(os);
    return os;
}

}  // namespace f1
