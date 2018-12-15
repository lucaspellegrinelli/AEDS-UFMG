#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

#include "cards/place.h"
#include "player/player.h"

/*
  Classe responsável por armazenar informações sobre o tabuleiro

  Descrição dos métodos no respectivo .cpp
*/

class Board {
private:
  std::vector<Place> places;
  std::vector<Player*> boardPlayers;
  std::vector<Place> playerPlaces;

  std::string processName(std::string);
  bool hasPlayerInPlace(std::string);
  Player* getPlayerInPlace(std::string placeName);
public:
  Board();
  Board(std::vector<Place>);
  std::vector<Place> getPlaces();
  void addPlayer(Player*, Place);
  void move(Player*, Place);
  Place getPosition(Player*);
  std::vector<Place> getMaxPlace(int, Place);
  void printMap();
};

#endif
