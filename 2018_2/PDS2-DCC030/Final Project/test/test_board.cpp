#include "../third_party/doctest.h"
#include "../include/board/board.h"

TEST_CASE("Constructor") {
  std::vector<Place> places;
  CHECK_NOTHROW(Board(places));
}
