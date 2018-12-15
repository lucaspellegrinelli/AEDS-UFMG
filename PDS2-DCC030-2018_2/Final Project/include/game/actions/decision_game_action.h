#ifndef DECISION_GAME_ACTION_H
#define DECISION_GAME_ACTION_H

#include "game/game_action.h"

/*
  A ação de decisão não precisa de nenhum atributo extra, apenas seu tipo pois
  é apenas para informar o que o jogador deseja fazer
*/

class DecisionGameAction : public GameAction{
public:
  DecisionGameAction(GameActionTypes type);
};

#endif
