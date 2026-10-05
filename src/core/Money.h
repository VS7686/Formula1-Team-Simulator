#pragma once

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

namespace f1 {

// Money stored as integer thousands of dollars ($K) to avoid floating-point drift.
class Money {
public:
    Money() = default;

    static Money fromThousands(long long k) { return Money(k); }
    static Money fromMillions(double m) { return Money(std::llround(m * 1000.0)); }

    long long thousands() const { return m_thousands; }
    double millions() const { return static_cast<double>(m_thousands) / 1000.0; }

    Money operator+(const Money& o) const { return Money(m_thousands + o.m_thousands); }
    Money operator-(const Money& o) const { return Money(m_thousands - o.m_thousands); }
    Money operator*(double factor) const { return Money(std::llround(static_cast<double>(m_thousands) * factor)); }
    Money operator-() const { return Money(-m_thousands); }
    Money& operator+=(const Money& o) { m_thousands += o.m_thousands; return *this; }
    Money& operator-=(const Money& o) { m_thousands -= o.m_thousands; return *this; }

    bool operator==(const Money& o) const { return m_thousands == o.m_thousands; }
    bool operator!=(const Money& o) const { return m_thousands != o.m_thousands; }
    bool operator<(const Money& o) const { return m_thousands < o.m_thousands; }
    bool operator>(const Money& o) const { return m_thousands > o.m_thousands; }
    bool operator<=(const Money& o) const { return m_thousands <= o.m_thousands; }
    bool operator>=(const Money& o) const { return m_thousands >= o.m_thousands; }

    // "$12.5M", "$850K", "-$2.0M"
    std::string str() const {
        std::ostringstream os;
        const long long a = std::llabs(m_thousands);
        if (m_thousands < 0) os << '-';
        if (a >= 1000) {
            // One decimal when it is exact ($12.5M), two otherwise ($13.25M).
            os << '$' << std::fixed << std::setprecision(a % 100 == 0 ? 1 : 2) << static_cast<double>(a) / 1000.0 << 'M';
        } else {
            os << '$' << a << 'K';
        }
        return os.str();
    }

private:
    explicit Money(long long thousands) : m_thousands(thousands) {}
    long long m_thousands = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Money& m) { return os << m.str(); }

}  // namespace f1
