#pragma once

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

namespace f1 {

// A lap/sector time stored as integer milliseconds. Prints as m:ss.mmm
class LapTime {
public:
    LapTime() = default;

    static LapTime fromSeconds(double s) { return LapTime(std::llround(s * 1000.0)); }
    static LapTime fromMilliseconds(long long ms) { return LapTime(ms); }

    long long milliseconds() const { return m_ms; }
    double seconds() const { return static_cast<double>(m_ms) / 1000.0; }

    LapTime operator+(const LapTime& o) const { return LapTime(m_ms + o.m_ms); }
    LapTime operator-(const LapTime& o) const { return LapTime(m_ms - o.m_ms); }
    LapTime& operator+=(const LapTime& o) { m_ms += o.m_ms; return *this; }

    bool operator==(const LapTime& o) const { return m_ms == o.m_ms; }
    bool operator!=(const LapTime& o) const { return m_ms != o.m_ms; }
    bool operator<(const LapTime& o) const { return m_ms < o.m_ms; }
    bool operator>(const LapTime& o) const { return m_ms > o.m_ms; }
    bool operator<=(const LapTime& o) const { return m_ms <= o.m_ms; }
    bool operator>=(const LapTime& o) const { return m_ms >= o.m_ms; }

    std::string str() const {
        const long long a = std::llabs(m_ms);
        std::ostringstream os;
        if (m_ms < 0) os << '-';
        os << a / 60000 << ':' << std::setw(2) << std::setfill('0') << (a % 60000) / 1000
            << '.' << std::setw(3) << std::setfill('0') << a % 1000;
        return os.str();
    }

private:
    explicit LapTime(long long ms) : m_ms(ms) {}
    long long m_ms = 0;
};

inline std::ostream& operator<<(std::ostream& os, const LapTime& t) { return os << t.str(); }

}  // namespace f1
