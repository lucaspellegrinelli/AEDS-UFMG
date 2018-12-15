#include "cards/weapon.h"

Weapon::Weapon(std::string idWeapon, std::string name, std::string image, Object_Type type):
  Game_Object(idWeapon, name, image, type){}

Weapon::Weapon(){}

std::string Weapon::getIdWeapon() {
  return _id;
}
