#include "../third_party/doctest.h"
#include "../include/player/bot.h"
#include "../include/cards/final_deck.h"

TEST_CASE("Constructor") {
  Final_Deck finalDeck;
  Deck allCardsList = finalDeck.getAllCards();
  Deck hand = finalDeck.getHand(0);
  Bot b0(0, "dummy", allCardsList, hand);
  int x = b0.getId();
  std::string y = b0.getName();
  int z = b0.getHand().getLittleDeck().size();
  CHECK_EQ(x, 0);
  CHECK_EQ(y, "dummy");
  CHECK_EQ(z, 3);
}
