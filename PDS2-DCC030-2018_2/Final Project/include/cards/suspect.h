#ifndef SUSPECT_H
#define SUSPECT_H

#include "game_object.h"

/*
  Classe responsável por armazenar informações sobre os suspeitos

  Descrição dos métodos no respectivo .cpp
*/

class Suspect : public Game_Object {
public:
  Suspect(std::string idSuspect, std::string name, std::string image, Object_Type type);
  Suspect();
  std::string getIdSuspect();

  ~Suspect(){}
};

#endif
