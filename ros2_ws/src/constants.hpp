#define DEFAULT_VELOCITY   0
#define DEFAULT_ERROR_CODE 0

#define VELOCITY_INDEX    0x2000
#define VELOCITY_SUBINDEX 0x00

// Mock object dictionary subindices for the device TPDO at 0x3000
#define TPDO_INDEX     0x3000
#define SUB_STATUS     0x01
#define SUB_VELOCITY   0x02
#define SUB_ERROR_CODE 0x03

// Device status codes
#define STATUS_OK    1
#define STATUS_FAULT 0
#define STATUS_TIMEOUT -1

#define STATUS_OK_STR "OK"
#define STATUS_FAULT_STR "FAULT"
#define STATUS_TIMEOUT_STR "TIMEOUT"

#define DEFAULT_QUALITY_OF_SERVICE 10

#define COMM_TIMEOUT_MS    1000
#define TIMER_RATE_MS       100
