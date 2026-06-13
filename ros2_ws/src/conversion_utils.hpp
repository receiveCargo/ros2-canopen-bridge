#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>

inline constexpr int16_t to_canopen_velocity(double ros_vel) {
    constexpr double kMax = std::numeric_limits<int16_t>::max() / 1000.0;
    constexpr double kMin = std::numeric_limits<int16_t>::min() / 1000.0;
    return static_cast<int16_t>(std::clamp(ros_vel, kMin, kMax) * 1000.0);
}

inline constexpr double from_canopen_velocity(int16_t can_vel) {
    return can_vel / 1000.0;
}
