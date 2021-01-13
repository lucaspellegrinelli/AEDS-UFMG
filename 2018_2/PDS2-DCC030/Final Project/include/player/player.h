#ifndef PLAYER_H
#define PLAYER_H

#include "util/name_helper.h"

#include "game/game_action.h"
#include "game/game_action_types.h"
#include "game/actions/decision_game_action.h"
#include "game/actions/destination_game_action.h"
#include "game/actions/guess_game_action.h"
#include "game/actions/show_card_game_action.h"

#include "game/game_event.h"
#include "game/game_event_types.h"
#include "game/events/guess_game_event.h"
#include "game/events/show_guess_card_event.h"
#include "game/events/simple_game_event.h"

#include "cards/card.h"
#include "cards/deck.h"

#include "exceptions/game_exceptions.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

class Player{
protected:
  int id;
  std::string name;
  Deck hand;

  Deck allCardsList;
	std::vector<Suspect*> allSuspects;
	std::vector<Weapon*> allWeapons;
	std::vector<Place*> allPlaces;
public:
  void setName(std::string name);
  std::string getName();
  int getId() const;
  Deck getHand();
  virtual DecisionGameAction decision() = 0;
  virtual DestinationGameAction choose_destination(std::vector<Place> places) = 0;
  virtual GuessGameAction guess(Place place) = 0;
  virtual GuessGameAction make_accusation(Place place) = 0;
  virtual ShowCardAction show_card(GuessGameEvent guess) = 0;
  virtual void view_card(std::vector<Card> cards, Player *whoShowed) = 0;

  virtual ~Player(){}
};

#endif
