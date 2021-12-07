#include <iostream>
#include <cmath>
#include "hyperloglog.h"
#include "xxhash32.h"

Hyperloglog::Hyperloglog(const uint8_t bw) throw (std::invalid_argument){
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

std::vector<uint8_t> Hyperloglog::getRegisters() const {
   return M_;
}

double Hyperloglog::getAlpha() const {
   return alpham_;
}

double Hyperloglog::getStandardError() const {
   return 1.04/sqrt(m_);
}

uint8_t Hyperloglog::leadingZeros(const uint32_t w, const uint8_t b) const {
   if(!w){
      return 32 - b;
   }
   return __builtin_clz(w);
}

void Hyperloglog::add(const std::string &s){
   add(&s[0], s.length());
}

void Hyperloglog::add(const void *item, const size_t sz){
   // this xxhash implementation is little-endian only
   uint32_t res = XXHash32::hash(item, sz, SEED);
   uint32_t addr = res >> (32 - b_); // first b bits
   uint8_t pw = leadingZeros(res << b_, b_) + 1; // leftmost 1 of remaining bits
   M_[addr] = std::max(M_[addr], pw);
}

double Hyperloglog::cardinality() const {
   double Z = 0;
   for(uint32_t i = 0; i < m_; i++){
      Z += (1.0 / (1 << M_[i]));
   }

   Z = 1.0 / Z;
   double E = alpham_ * m_ * m_ * Z;

   if(E < (2.5*m_)){
      // switch to linear counting
      std::cout << "below 5/2 m" << std::endl;
      double V = 0;
      for(uint32_t i = 0; i < m_; i++){
         if(!M_[i]){
            V++;
         }
      }
      if(V > 0){
         return m_ * std::log(m_/V);
      }
   }
   else if(E > (4294967296.0/30.0)){
      // near upper bound of 32-bit registers
     return -4294967296.0 * std::log(1.0 - (E/4294967296.0)); 
   }

   return E;
}

void Hyperloglog::merge(const Hyperloglog &hll) throw (std::invalid_argument){
   if(m_ != hll.m_){
      std::ostringstream ss;
      ss << "Cannot merge HLL of " << static_cast<int>(m_) << " registers with HLL of " << static_cast<int>(hll.m_) << " registers";
      throw std::invalid_argument(ss.str());
   }
   for(uint32_t i = 0; i < m_; i++){
      M_[i] = std::max(M_[i], hll.M_[i]);
   }
}

void Hyperloglog::empty(){
   std::fill(M_.begin(), M_.end(), 0);
}
