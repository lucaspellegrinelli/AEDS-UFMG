#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "card.h"
#include "game_object.h"
#include "weapon.h"
#include "place.h"
#include "suspect.h"

/*
  Essa classe serve para construir um vetor de cartas e implementar metodos que
  serao utilizados pela classe final_deck.

  Descrição dos métodos no respectivo .cpp
*/

class Deck {
private:
  std::vector<Card> LittleDeck;

public:
  Deck();
  std::vector<Card> getLittleDeck();
  void addCard(Card card);
  void shuffle();
  void showCards();

  virtual ~Deck(){}
};

#endif
