#include <iostream>
#include <fstream>
#include "../lib/memory.h"
#include "../lib/hyperloglog.h"

int main(){
   std::ifstream fin("./data/cleaned-shakespeare.txt");

   long long b1 = bytesUsed();

   Hyperloglog hll(8);

   std::string s;
   long long tot = 0;
   while(fin >> s){
      /* hll.add(&s[0], s.length()); */
      hll.add(s);
      tot++;
   }

   std::cout << "Total words:    " << tot << "\n";
   std::cout << "Distinct words: " << hll.cardinality() << "\n\n";

   long long b2 = bytesUsed();
   std::cout << "Memory used: " << b2 - b1 << " bytes\n";
}
