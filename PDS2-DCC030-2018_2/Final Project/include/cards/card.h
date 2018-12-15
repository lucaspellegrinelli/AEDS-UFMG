#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "game_object.h"

/*
  Classe responsável por armazenar informações sobre as cartas

  Descrição dos métodos no respectivo .cpp
*/

class Card {
protected:
  std::string _idCard;
  Game_Object *_object;

public:
  Card();
  Card(std::string idCard, Game_Object *object);
  std::string getIdCard();
  Game_Object* getObject();
  void openImage();
};

#endif
