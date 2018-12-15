#ifndef PLACE_H
#define PLACE_H

#include "game_object.h"

/*
  Classe responsável por armazenar informações sobre os lugares

  Descrição dos métodos no respectivo .cpp
*/

class Place : public Game_Object {
public:
  Place(std::string idPlace, std::string name, std::string image, Object_Type type);
  Place();
  std::string getIdPlace();

  ~Place(){}
};

#endif
