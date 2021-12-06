#include <iostream>
#include <fstream>
#include "../lib/memory.h"
#include "../lib/hyperloglog.h"

int main(){
   std::ifstream fin("./data/cleaned-shakespeare.txt");

   Hyperloglog hll(4);
   std::cout << "created HLL with bit width " << static_cast<int>(hll.getBitWidth()) << " and register size " << hll.getRegisterSize() << "\n\n";

   std::string s;
   for(int i = 0; i < 100; i++){
      fin >> s;
      hll.add(s);
   }
   /* while(fin >> s){ */
   /*    hll.add(s); */
   /* } */

   showMemoryUsage(std::cout);
}
