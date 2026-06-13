#pragma once

int16_t to_canopen_velocity(double ros_vel) {
    return static_cast<int16_t>(ros_vel * 1000);
}
double from_canopen_velocity(int16_t can_vel) {
    return can_vel / 1000.0;
}
