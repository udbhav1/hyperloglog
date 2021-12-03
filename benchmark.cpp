#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main(){
   /* std::ios_base::sync_with_stdio(false); */
   /* std::cin.tie(NULL); */

   // TODO fstream slow??
   std::ifstream fin("data/cleaned-shakespeare.txt");

   std::set<std::string> s;
   std::string word;
   long long int tot = 0;
   while(fin >> word){
      s.insert(word);
      tot++;
   }
   std::cout << "Total words:    " << tot << std::endl;
   std::cout << "Distinct words: " << s.size() << std::endl;
}

