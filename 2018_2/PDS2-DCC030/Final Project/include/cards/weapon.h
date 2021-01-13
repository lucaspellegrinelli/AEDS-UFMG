#ifndef WEAPON_H
#define WEAPON_H

#include "game_object.h"

/*
  Classe responsável por armazenar informações sobre as armas

  Descrição dos métodos no respectivo .cpp
*/

class Weapon : public Game_Object {
public:
  Weapon(std::string idWeapon, std::string name, std::string image, Object_Type type);
  Weapon();
  std::string getIdWeapon();

  ~Weapon(){}
};

#endif
