#include "../third_party/doctest.h"
#include "../include/cards/deck.h"

TEST_CASE("Constructor") {
  Deck deck;
  int x = deck.getLittleDeck().size();
  Game_Object *object1 = new Game_Object("o1", "generic", "o1.jpg", WEAPON);
  Card card1("c1", object1);
  Game_Object *object2 = new Game_Object("o2", "generic", "o2.jpg", PLACE);
  Card card2("c2", object2);
  deck.addCard(card1);
  deck.addCard(card2);
  x = deck.getLittleDeck().size();
  CHECK_EQ(x, 2);
  delete object1;
  delete object2;
}