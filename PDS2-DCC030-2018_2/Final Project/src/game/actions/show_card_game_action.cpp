#include "game/actions/show_card_game_action.h"

ShowCardAction::ShowCardAction(GameActionTypes type, Card card){
  this->type = type;
  this->card = card;
}

ShowCardAction::ShowCardAction(GameActionTypes type, bool valid){
  this->type = type;
  this->valid = valid;
}

Card ShowCardAction::getCard(){
  return this->card;
}

bool ShowCardAction::isValid(){
  return this->valid;
}
