#include "game/game_action.h"

GameActionTypes GameAction::getActionType(){
  return this->type;
}

GameAction::~GameAction(){ }
