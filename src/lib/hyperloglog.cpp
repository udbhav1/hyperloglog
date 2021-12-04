#include <iostream>
#include "hyperloglog.h"

Hyperloglog::Hyperloglog(uint8_t bw) throw (std::invalid_argument){
   if(bw < 4 or bw > 30){
      std::ostringstream ss;
      ss << "bit width " << static_cast<int>(bw) << " out of range [4, 30]";
      throw std::invalid_argument(ss.str());
   }

   b_ = bw;
   m_ = (1 << bw);
   M_.resize(m_, 0);

   if(m_ == 16){
      alpham_ = 0.673;
   }
   else if(m_ == 32){
      alpham_ = 0.697;
   }
   else if(m_ == 64){
      alpham_ = 0.709;
   }
   else{
      alpham_ = 0.7213/(1 + (1.079/m_));
   }
}

Hyperloglog::Hyperloglog(const Hyperloglog &hll){
   b_ = hll.b_;
   m_ = hll.m_;
   M_ = hll.M_;
   alpham_ = hll.alpham_;
}

uint8_t Hyperloglog::getBitWidth() const {
   return b_;
}

uint32_t Hyperloglog::getRegisterSize() const {
   return m_;
}

double Hyperloglog::getAlpha() const {
   return alpham_;
}

void Hyperloglog::merge(const Hyperloglog &hll) throw (std::invalid_argument){
   if(m_ != hll.m_){
      std::ostringstream ss;
      ss << "Cannot merge HLL of " << static_cast<int>(m_) << " registers with HLL of " << static_cast<int>(hll.m_) << " registers";
      throw std::invalid_argument(ss.str());
   }
   for(int i = 0; i < m_; i++){
      M_[i] = std::max(M_[i], hll.M_[i]);
   }
}

void Hyperloglog::empty(){
   std::fill(M_.begin(), M_.end(), 0);
}
