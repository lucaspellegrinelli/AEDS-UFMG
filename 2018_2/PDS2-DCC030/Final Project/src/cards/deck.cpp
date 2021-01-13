#include "cards/deck.h"

Deck::Deck(){
  std::vector<Card> v;
  LittleDeck = v;
}

std::vector<Card> Deck::getLittleDeck(){
  return LittleDeck;
}

//Inclui as cartas no Deck. Sera utilizada no construtor da classe Final_Deck.
void Deck::addCard(Card card){
  LittleDeck.push_back(card);
}

//Embaralha as cartas do Deck. Sera utilizada no construtor da classe Final_Deck.
void Deck::shuffle(){
  std::random_shuffle(LittleDeck.begin(), LittleDeck.end());
}

//Fornece o nome de todas as cartas presentes no Deck.
void Deck::showCards(){
  for (std::vector<Card>::iterator it = LittleDeck.begin(); it != LittleDeck.end(); it++)
    std::cout << " " << it->getObject()->getName();
  std::cout << std::endl;
}
