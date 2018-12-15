#ifndef GAME_H
#define GAME_H

#include "player/player.h"
#include "player/bot.h"
#include "player/human.h"

#include "util/name_helper.h"

#include "game_action.h"
#include "actions/decision_game_action.h"
#include "actions/destination_game_action.h"
#include "actions/guess_game_action.h"
#include "actions/show_card_game_action.h"

#include "game_event.h"
#include "events/simple_game_event.h"
#include "events/guess_game_event.h"
#include "events/show_guess_card_event.h"

#include "board/board.h"

#include "cards/final_deck.h"
#include "cards/card.h"
#include "cards/game_object.h"
#include "cards/place.h"
#include "cards/suspect.h"
#include "cards/weapon.h"
#include "exceptions/game_exceptions.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

/*
  Classe responsável por gerenciar o fluxo do jogo

  Descrição dos métodos no respectivo .cpp
*/

class Game{
private:
  int n_of_humans;
  int n_of_bots;
  std::vector<Player*> players;
  bool finished;
  Final_Deck finalDeck;
  Board board;

public:
  Game();
  bool humanLost;
  void initializePlayers();
  void run();
  std::vector<Player*> getPlayers();
  void interpretDecision(DecisionGameAction decision, int turnPlayer);
  void walkDecision(int turnPlayer, Place place);
  void guessDecision(int turnPlayer);
  void accusationDecision(int turnPlayer);
  void showCardsToEveryone(int turnPlayer, std::vector<Card> cards);

  ~Game();
};

#endif
