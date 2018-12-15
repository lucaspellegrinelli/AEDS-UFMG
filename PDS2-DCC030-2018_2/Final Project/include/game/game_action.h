#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "game_action_types.h"
#include "cards/place.h"
#include "cards/weapon.h"
#include "cards/suspect.h"
#include "cards/card.h"

/*
  Ações de usuário no jogo
*/

class GameAction{
protected:
  GameActionTypes type;

public:
  GameActionTypes getActionType();
  virtual ~GameAction();
};

#endif
