#include "canopen_interface.hpp"

#include <stdexcept>
#include "constants.hpp"

CanopenInterface::CanopenInterface() {
    // Pre-populate TPDO entries so the device appears healthy on first read
    object_dict_[{TPDO_INDEX, SUB_STATUS}]     = STATUS_OK;
    object_dict_[{TPDO_INDEX, SUB_VELOCITY}]   = DEFAULT_VELOCITY;
    object_dict_[{TPDO_INDEX, SUB_ERROR_CODE}] = DEFAULT_ERROR_CODE;
}

void CanopenInterface::sendRPDO(uint16_t index, uint8_t subindex, int value) {
    object_dict_[{index, subindex}] = value;

    // Simulate device: echo the velocity command back through the TPDO so the
    // bridge can read "actual velocity" immediately without a real device.
    if (index == VELOCITY_INDEX && subindex == VELOCITY_SUBINDEX) {
        object_dict_[{TPDO_INDEX, SUB_VELOCITY}]   = value;
        object_dict_[{TPDO_INDEX, SUB_STATUS}]     = STATUS_OK;
        object_dict_[{TPDO_INDEX, SUB_ERROR_CODE}] = DEFAULT_ERROR_CODE;
    }
}

int CanopenInterface::readTPDO(uint16_t index, uint8_t subindex) {
    std::map<std::pair<uint16_t, uint8_t>, int>::iterator it = object_dict_.find({index, subindex});
    if (it == object_dict_.end()) {
        throw std::runtime_error("CANopen: no data at requested entry");
    }
    return it->second;
}
