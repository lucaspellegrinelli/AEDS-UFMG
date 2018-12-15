#include "../third_party/doctest.h"
#include "../include/cards/game_object.h"

TEST_CASE("Constructor") {
  Game_Object object("o1", "generic", "o1.jpg", WEAPON);
  std::string x = object.getId();
  std::string y = object.getName();
  std::string z = object.getImage();
  Object_Type t = object.getType();
  CHECK_EQ(x, "o1");
  CHECK_EQ(y, "generic");
  CHECK_EQ(z, "o1.jpg");
  CHECK_EQ(t, 0);

  Game_Object object2;
  x = object2.getId();
  y = object2.getName();
  z = object2.getImage();
  t = object2.getType();
  CHECK_EQ(x, "?");
  CHECK_EQ(y, "?");
  CHECK_EQ(z, "?");
  CHECK_EQ(t, 0);
}
