#include "game/actions/guess_game_action.h"

GuessGameAction::GuessGameAction(GameActionTypes type, Place place, Weapon weapon, Suspect suspect, int id){
  this->type = type;
  this->place = place;
  this->weapon = weapon;
  this->suspect = suspect;
  this->id = id;
}

Place GuessGameAction::getPlace(){
  return this->place;
}

Weapon GuessGameAction::getWeapon(){
  return this->weapon;
}

Suspect GuessGameAction::getSuspect(){
  return this->suspect;
}
int GuessGameAction::getId(){
	return this->id;
}
