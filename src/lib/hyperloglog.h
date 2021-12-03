#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <stdint.h>

class Hyperloglog {
    private:
        uint8_t b_;
        uint32_t m_;
    public:
        Hyperloglog(uint8_t b) throw (std::invalid_argument);
        uint8_t getBitWidth() const;
        uint32_t getRegisterSize() const;
};

#endif
