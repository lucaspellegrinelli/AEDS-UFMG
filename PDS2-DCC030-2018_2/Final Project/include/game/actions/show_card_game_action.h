#ifndef SHOW_CARD_GAME_ACTION_H
#define SHOW_CARD_GAME_ACTION_H

#include "game/game_action.h"

/*
  A ação de mostrar carta, além do seu tipo, ela precisa da informação de qual carta
*/

class ShowCardAction : public GameAction{
private:
  Card card;
  bool valid;

public:
  ShowCardAction(GameActionTypes type, Card card);
  ShowCardAction(GameActionTypes type, bool valid);
  Card getCard();
  bool isValid();

};

#endif
