#pragma once

#include <cstdint>

inline constexpr int DEFAULT_VELOCITY   = 0;
inline constexpr int DEFAULT_ERROR_CODE = 0;

inline constexpr uint16_t VELOCITY_INDEX    = 0x2000;
inline constexpr uint8_t  VELOCITY_SUBINDEX = 0x00;

// Mock object dictionary subindices for the device TPDO at 0x3000
inline constexpr uint16_t TPDO_INDEX     = 0x3000;
inline constexpr uint8_t  SUB_STATUS     = 0x01;
inline constexpr uint8_t  SUB_VELOCITY   = 0x02;
inline constexpr uint8_t  SUB_ERROR_CODE = 0x03;

// Device status codes
inline constexpr int STATUS_OK      =  1;
inline constexpr int STATUS_TIMEOUT = -1;

inline constexpr const char * STATUS_OK_STR      = "OK";
inline constexpr const char * STATUS_FAULT_STR   = "FAULT";
inline constexpr const char * STATUS_TIMEOUT_STR = "TIMEOUT";

inline constexpr int QOS_DEPTH       = 10;
inline constexpr int COMM_TIMEOUT_MS = 1000;
inline constexpr int TIMER_RATE_MS   = 100;

// Log message strings
inline constexpr const char * LOG_NODE_STARTED     = "CANopen bridge node started";
inline constexpr const char * LOG_RPDO_SEND_FAILED = "RPDO send failed: %s";
inline constexpr const char * LOG_VELOCITY_CMD     = "Velocity command: %.3f m/s -> %d (CANopen)";
inline constexpr const char * LOG_DEVICE_FAULT     = "Device fault - error_code=%d";
inline constexpr const char * LOG_COMM_TIMEOUT     = "CANopen communication timeout (%.1fs): %s";
inline constexpr const char * LOG_TPDO_READ_FAILED = "TPDO read failed: %s";
