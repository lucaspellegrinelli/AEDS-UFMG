#ifndef GUESS_GAME_EVENT_H
#define GUESS_GAME_EVENT_H

#include "game/game_event.h"

/*
  Evento pedindo para o usuário escolher a arma, suspeito e local de seu palpite/
  acusação
*/

class GuessGameEvent : public GameEvent{
private:
  Place place;
  Weapon weapon;
  Suspect suspect;
public:
  GuessGameEvent(GameEventTypes type, Place place, Weapon weapon, Suspect suspect);
  Place getPlace();
  Weapon getWeapon();
  Suspect getSuspect();
};

#endif
