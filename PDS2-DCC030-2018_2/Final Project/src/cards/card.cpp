#include "cards/card.h"

Card::Card(){}

Card::Card(std::string idCard, Game_Object *object){
  _idCard = idCard;
  _object = object;
}

std::string Card::getIdCard(){
  return _idCard;
}

Game_Object* Card::getObject(){
  return _object;
}

// abre a imagem com a carta atraves do proprio sistema operacional
void Card::openImage(){
  std::string open1 = "display src/cards/imgcards/";
  std::string open2 = _object->getImage();
  open1 += open2;
  system(open1.c_str());
}
