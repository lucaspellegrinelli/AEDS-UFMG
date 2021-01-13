#include "../third_party/doctest.h"
#include "../include/cards/card.h"

TEST_CASE("Constructor") {
  Game_Object *object = new Game_Object("o1", "generic", "o1.jpg", WEAPON);
  Card card("c1", object);
  std::string i = card.getIdCard();
  std::string x = card.getObject()->getId();
  std::string y = card.getObject()->getName();
  std::string z = card.getObject()->getImage();
  Object_Type t = card.getObject()->getType();
  CHECK_EQ(i, "c1");
  CHECK_EQ(x, "o1");
  CHECK_EQ(y, "generic");
  CHECK_EQ(z, "o1.jpg");
  CHECK_EQ(t, 0);
  delete object;
}
