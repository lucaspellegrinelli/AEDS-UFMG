#include "../third_party/doctest.h"
#include "../include/game/game.h"

TEST_CASE("Running") {
  CHECK_NOTHROW(Game());
}
