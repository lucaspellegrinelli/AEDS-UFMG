#ifndef NAME_HELPER_H
#define NAME_HELPER_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class NameHelper{
public:
  NameHelper();
  std::string askForName(int id);
  std::string generateName(bool bot_prefix);
};

#endif
