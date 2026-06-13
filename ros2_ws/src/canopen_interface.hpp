#pragma once

#include <cstdint>
#include <map>
#include <utility>

class CanopenInterface {
public:
    CanopenInterface();

    // Send a Receive PDO (host → device): writes value to object dictionary entry
    void sendRPDO(uint16_t index, uint8_t subindex, int value);

    // Read a Transmit PDO (device → host): returns value from object dictionary entry
    // Throws std::runtime_error if the entry has never been written
    int readTPDO(uint16_t index, uint8_t subindex) const;

private:
    // Flat object dictionary keyed by (index, subindex)
    std::map<std::pair<uint16_t, uint8_t>, int> object_dict_;
};
