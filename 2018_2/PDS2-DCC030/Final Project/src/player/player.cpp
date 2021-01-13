#include "player/player.h"

void Player::setName(std::string name){
  this->name = name;
}

std::string Player::getName(){
  return this->name;
}

int Player::getId() const{
  return this->id;
}

Deck Player::getHand(){
	return this->hand;
}
