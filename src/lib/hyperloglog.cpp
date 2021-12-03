#include <iostream>
#include "hyperloglog.h"

Hyperloglog::Hyperloglog(uint8_t b) throw (std::invalid_argument){
   b_ = b;
   m_ = (1 << b);
   if(b < 4 or b > 30){
      throw std::invalid_argument("bit width out of range [4, 30]");
   }
}

uint8_t Hyperloglog::getBitWidth() const {
   return b_;
}

uint32_t Hyperloglog::getRegisterSize() const {
   return m_;
}
