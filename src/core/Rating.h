#pragma once

#include <algorithm>
#include <ostream>

namespace f1 {

// A skill/part rating that is always clamped to 1..100.
class Rating {
public:
    static constexpr int kMin = 1;
    static constexpr int kMax = 100;

    Rating(int value = 50) : m_value(clamp(value)) {}

    Rating& operator=(int value) { m_value = clamp(value); return *this; }
    Rating& operator+=(int delta) { m_value = clamp(m_value + delta); return *this; }
    Rating& operator-=(int delta) { m_value = clamp(m_value - delta); return *this; }

    operator int() const { return m_value; }
    int value() const { return m_value; }

private:
    static int clamp(int v) { return std::max(kMin, std::min(kMax, v)); }
    int m_value;
};

inline std::ostream& operator<<(std::ostream& os, const Rating& r) { return os << r.value(); }

}  // namespace f1
