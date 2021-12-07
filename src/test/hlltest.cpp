#include <iostream>
#include <fstream>
#include "../lib/memory.h"
#include "../lib/hyperloglog.h"

int main(){
   std::ifstream fin("./data/cleaned-shakespeare.txt");

   Hyperloglog hll(8);
   std::cout << "created HLL with bit width " << static_cast<int>(hll.getBitWidth()) << " and register size " << hll.getRegisterSize() << "\n";

   std::string s;
   while(fin >> s){
      hll.add(s);
   }

   std::cout << hll.cardinality() << " " << 1.04/(hll.getRegisterSize()) << std::endl << std::endl;

   showMemoryUsage(std::cout);
}
