#include "game/actions/destination_game_action.h"

DestinationGameAction::DestinationGameAction(GameActionTypes type, Place place){
  this->type = type;
  this->place = place;
}

Place DestinationGameAction::getPlace(){
  return this->place;
}
