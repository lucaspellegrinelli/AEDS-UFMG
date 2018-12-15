#ifndef FINAL_DECK_H
#define FINAL_DECK_H

#include "deck.h"

#include <algorithm>

#define NUM_OF_PLAYERS 6

/*
  Classe responsável por armazenar informações sobre o deck de cartas
  tanto quanto o top secret

  Descrição dos métodos no respectivo .cpp
*/

class Final_Deck {
private:
  Deck TopSecret;
  Deck allCards;
  std::vector<Deck> allDecks;

public:
  Final_Deck();
  Deck getTopSecret();
  Deck getAllCards();
  Deck getHand(int num);
  void solveMystery();

  virtual ~Final_Deck(){}
};

#endif
