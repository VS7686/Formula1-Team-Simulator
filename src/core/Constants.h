#pragma once

namespace f1::constants {

// Lap-time spread: how many seconds per lap separate a perfect car (100) from a terrible one (0).
inline constexpr double kCarRange = 3.2;
// Same idea for drivers.
inline constexpr double kDriverRange = 1.4;
// Part condition lost per race lap before any multipliers.
inline constexpr double kBasePartWearPerLap = 0.12;
// Base mechanical-failure probability per part per lap.
inline constexpr double kBaseFailurePerLap = 0.00008;

}  // namespace f1::constants
