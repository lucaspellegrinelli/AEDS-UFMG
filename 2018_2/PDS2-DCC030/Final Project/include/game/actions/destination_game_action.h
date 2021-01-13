#ifndef DESTINATION_GAME_ACTION_H
#define DESTINATION_GAME_ACTION_H

#include "game/game_action.h"
#include "cards/place.h"

/*
  A ação de destino, além do seu tipo, ela precisa da informação de lugar
*/

class DestinationGameAction : public GameAction{
private:
  Place place;
public:
  DestinationGameAction(GameActionTypes type, Place place);
  Place getPlace();
};

#endif
