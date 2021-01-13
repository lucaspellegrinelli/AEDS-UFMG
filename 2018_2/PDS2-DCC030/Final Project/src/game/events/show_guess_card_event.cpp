#include "game/events/show_guess_card_event.h"

ShowGuessCardGameEvent::ShowGuessCardGameEvent(GameEventTypes type, Place place, Weapon weapon, Suspect suspect, int player){
  this->type = type;
  this->place = place;
  this->weapon = weapon;
  this->suspect = suspect;
  this->player = player;
}

Place ShowGuessCardGameEvent::getPlace(){
  return this->place;
}

Weapon ShowGuessCardGameEvent::getWeapon(){
  return this->weapon;
}

Suspect ShowGuessCardGameEvent::getSuspect(){
  return this->suspect;
}

int ShowGuessCardGameEvent::getPlayer(){
  return this->player;
}
