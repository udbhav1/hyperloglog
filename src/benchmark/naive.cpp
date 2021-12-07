#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "../lib/memory.h"

int main(){
   // TODO fstream slow??
   // path relative to final executable in project root
   std::ifstream fin("./data/cleaned-shakespeare.txt");

   long long b1 = bytesUsed();

   std::set<std::string> s;
   std::string word;
   long long tot = 0;
   while(fin >> word){
      s.insert(word);
      tot++;
   }

   std::cout << "Total words:    " << tot << "\n";
   std::cout << "Distinct words: " << s.size() << "\n\n";

   long long b2 = bytesUsed();
   std::cout << "Memory used: " << b2 - b1 << " bytes\n";
}
