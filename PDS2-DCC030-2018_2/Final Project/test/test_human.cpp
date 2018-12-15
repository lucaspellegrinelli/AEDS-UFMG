#include "../third_party/doctest.h"
#include "../include/player/human.h"
#include "../include/cards/final_deck.h"

TEST_CASE("Constructor") {
  Final_Deck finalDeck;
  Deck allCardsList = finalDeck.getAllCards();
  Deck hand = finalDeck.getHand(0);
  Human h0(0, "Nome", allCardsList, hand);
  int x = h0.getId();
  std::string y = h0.getName();
  int z = h0.getHand().getLittleDeck().size();
  CHECK_EQ(x, 0);
  CHECK_EQ(y, "Nome");
  CHECK_EQ(z, 3);
}
