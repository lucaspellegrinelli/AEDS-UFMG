#include "../third_party/doctest.h"
#include "../include/cards/final_deck.h"

TEST_CASE("Constructor") {
  Final_Deck finalDeck;
  Deck secret = finalDeck.getTopSecret();
  Object_Type t0 = secret.getLittleDeck()[0].getObject()->getType();
  Object_Type t1 = secret.getLittleDeck()[1].getObject()->getType();
  Object_Type t2 = secret.getLittleDeck()[2].getObject()->getType();
  CHECK_EQ(t0, 0);
  CHECK_EQ(t1, 1);
  CHECK_EQ(t2, 2);

  int i = finalDeck.getAllCards().getLittleDeck().size();
  CHECK_EQ(i, 21);

  int h = finalDeck.getHand(0).getLittleDeck().size();
  CHECK_EQ(h, 3);
}
