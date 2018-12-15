#include "cards/place.h"

Place::Place(std::string idPlace, std::string name, std::string image, Object_Type type):
  Game_Object(idPlace, name, image, type){}

Place::Place(){}

std::string Place::getIdPlace() {
  return _id;
}
