#include "cards/game_object.h"

Game_Object::Game_Object(std::string id, std::string name, std::string image, Object_Type type){
  _id = id;
  _name = name;
  _image = image;
  _type = type;
}

Game_Object::Game_Object(){
  _id = "?";
  _name = "?";
  _image = "?";
  _type = WEAPON;
}

std::string Game_Object::getId(){
  return _id;
}

std::string Game_Object::getName(){
  return _name;
}

std::string Game_Object::getImage(){
  return _image;
}

Object_Type Game_Object::getType(){
  return _type;
}
