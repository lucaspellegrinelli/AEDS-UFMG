#include "game/events/guess_game_event.h"

GuessGameEvent::GuessGameEvent(GameEventTypes type, Place place, Weapon weapon, Suspect suspect){
  this->type = type;
  this->place = place;
  this->weapon = weapon;
  this->suspect = suspect;
}

Place GuessGameEvent::getPlace(){
  return this->place;
}

Weapon GuessGameEvent::getWeapon(){
  return this->weapon;
}

Suspect GuessGameEvent::getSuspect(){
  return this->suspect;
}
