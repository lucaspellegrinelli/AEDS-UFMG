#ifndef SHOW_GUESS_CARD_EVENT_H
#define SHOW_GUESS_CARD_EVENT_H

#include "game/game_event.h"

/*
  Evento pedindo para o usuário mostrar uma de suas cartas que coincidem com
  o palpite
*/

class ShowGuessCardGameEvent : public GameEvent{
private:
  Place place;
  Weapon weapon;
  Suspect suspect;
  int player;
public:
  ShowGuessCardGameEvent(GameEventTypes type, Place place, Weapon weapon, Suspect suspect, int player);
  Place getPlace();
  Weapon getWeapon();
  Suspect getSuspect();
  int getPlayer();
};

#endif
