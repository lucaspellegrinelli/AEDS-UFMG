#include <map>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstdio>

int main(){
  std::map<std::string, int> count;

  std::string row;

  int num_words = 0;
  while(std::getline(std::cin, row)){
    std::istringstream row_stream(row);
    std::string word;
    while(std::getline(row_stream, word, ' ')){
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      num_words++;
      count[word]++;
    }
  }

  for(auto itr = count.begin(); itr != count.end(); itr++){
    double perc = (double)itr->second / (double)num_words;
    printf("%s %d %.2f\n", (itr->first).c_str(), itr->second, perc);
  }
}
