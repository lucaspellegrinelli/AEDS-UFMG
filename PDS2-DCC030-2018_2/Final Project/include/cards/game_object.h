#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <string>

enum Object_Type {WEAPON, PLACE, SUSPECT};

/*
  Classe responsável por armazenar informações sobre cada tipo de carta
  (arma, lugar e suspeito), como nome, link para a imagem e tipo

  Descrição dos métodos no respectivo .cpp
*/

class Game_Object {
protected:
  std::string _id;

private:
  std::string _name;
  std::string _image;
  Object_Type _type;

public:
  Game_Object(std::string id, std::string name, std::string image, Object_Type type);
  Game_Object();
  std::string getId();
  std::string getName();
  std::string getImage();
  Object_Type getType();

  virtual ~Game_Object(){}
};

#endif
