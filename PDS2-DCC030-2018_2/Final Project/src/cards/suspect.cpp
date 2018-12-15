#include "cards/suspect.h"

Suspect::Suspect(std::string idSuspect, std::string name, std::string image, Object_Type type):
  Game_Object(idSuspect, name, image, type){}

Suspect::Suspect() {}

std::string Suspect::getIdSuspect() {
  return _id;
}
