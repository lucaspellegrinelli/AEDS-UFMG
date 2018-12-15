#ifndef GUESS_GAME_ACTION_H
#define GUESS_GAME_ACTION_H

#include "game/game_action.h"

/*
  A ação de tentativa, além do seu tipo, ela precisa da informação de assassino, lugar e arma
*/

class GuessGameAction : public GameAction{
private:
  Place place;
  Weapon weapon;
  Suspect suspect;
  int id;

public:
  GuessGameAction(GameActionTypes type, Place place, Weapon weapon, Suspect suspect, int id);
  Place getPlace();
  Weapon getWeapon();
  Suspect getSuspect();
  int getId();
};

#endif
