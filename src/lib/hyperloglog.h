#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <stdint.h>
#include <string>
#include <sstream>

#define SEED 110

class Hyperloglog {
    private:
        uint8_t b_; // first b bits used to determine register
        uint32_t m_; // number of registers = 2^b
        std::vector<uint8_t> M_; // registers
        double alpham_; // constant to remedy hash collisions
    public:
        Hyperloglog(uint8_t bw) throw (std::invalid_argument);
        Hyperloglog(const Hyperloglog &hll);

        uint8_t getBitWidth() const;
        uint32_t getRegisterSize() const;
        double getAlpha() const;

        void add(const std::string &s);
        double cardinality() const;
        void merge(const Hyperloglog &hll) throw (std::invalid_argument);
        void empty();
};

#endif
