#include "board/board.h"

Board::Board(){}

Board::Board(std::vector<Place> all) {
  this->places = all;
}

std::vector<Place> Board::getPlaces() {
  return this->places;
}

void Board::addPlayer(Player* h, Place p) {
  this->boardPlayers.push_back(h);
  this->playerPlaces.push_back(p);
}

void Board::move(Player* player, Place place) {
  for(int i = 0; i < (int)this->boardPlayers.size(); i++){
    if(this->boardPlayers[i]->getId() == player->getId()){
      this->playerPlaces[i] = place;
      break;
    }
  }
}

Place Board::getPosition(Player* p) {
  for(int i = 0; i < (int)this->boardPlayers.size(); i++){
    if(this->boardPlayers[i]->getId() == p->getId()){
      return this->playerPlaces[i];
    }
  }
}

Player* Board::getPlayerInPlace(std::string placeName){
  for(int i = 0; i < (int)this->playerPlaces.size(); i++){
    if(this->playerPlaces[i].getName() == placeName){
      return this->boardPlayers[i];
    }
  }
}

bool Board::hasPlayerInPlace(std::string placeName){
  for(int i = 0; i < (int)this->playerPlaces.size(); i++){
    if(this->playerPlaces[i].getName() == placeName){
      return true;
    }
  }

  return false;
}

std::vector<Place> Board::getMaxPlace(int moves, Place actual) {
  std::vector<Place> possiblePlaces;
  int currPlaceId = -1;
  for(int i = 0; i < (int)this->places.size(); i++){
    if(this->places[i].getIdPlace() == actual.getIdPlace()){
      currPlaceId = i;
      break;
    }
  }

  if(currPlaceId == -1) return possiblePlaces;

  for(int i = 0; i < moves; i++){
    int realPos = (currPlaceId + i) % this->places.size();
    possiblePlaces.push_back(this->places[realPos]);
  }

  return possiblePlaces;
}

std::string Board::processName(std::string name){
  double offsize = 17 - name.size();
  int before = ceil(offsize / 2);
  int after = floor(offsize / 2);

  std::string newName = "";
  for(int i = 0; i < before; i++){
    newName += " ";
  }

  newName += name;

  for(int i = 0; i < after; i++){
    newName += " ";
  }
  return newName;
}

void Board::printMap(){
  std::string salaName = hasPlayerInPlace("Sala") ? processName(getPlayerInPlace("Sala")->getName()) :                  "                 ";
  std::string banheiroName = hasPlayerInPlace("Banheiro") ? processName(getPlayerInPlace("Banheiro")->getName()) :      "                 ";
  std::string cabineName = hasPlayerInPlace("Cabine") ? processName(getPlayerInPlace("Cabine")->getName()) :            "                 ";
  std::string crcName = hasPlayerInPlace("CRC") ? processName(getPlayerInPlace("CRC")->getName()) :                     "                 ";
  std::string loungeName = hasPlayerInPlace("Lounge") ? processName(getPlayerInPlace("Lounge")->getName()) :            "                 ";
  std::string daName = hasPlayerInPlace("DA") ? processName(getPlayerInPlace("DA")->getName()) :                        "                 ";
  std::string museuName = hasPlayerInPlace("Museu") ? processName(getPlayerInPlace("Museu")->getName()) :               "                 ";
  std::string corredorName = hasPlayerInPlace("Corredor") ? processName(getPlayerInPlace("Corredor")->getName()) :      "                 ";
  std::string bolaName = hasPlayerInPlace("Bola") ? processName(getPlayerInPlace("Bola")->getName()) :                  "                 ";


  std::cout << " ___________________________________________________________________________________________________________ " << std::endl;
  std::cout << " ||__                                                  |                                                __|| " << std::endl;
  std::cout << " |   |__                       Bola                    |                   Sala                      __|   | " << std::endl;
  std::cout << " |     |____                                           |                                         ___|      | " << std::endl;
  std::cout << " |         |_____       " << bolaName <<  "            |            " << salaName <<  "    _____|          | " << std::endl;
  std::cout << " |               |_                                    |                                 _|                | " << std::endl;
  std::cout << " |     Corredor    |___________________________________|_______________________________|                   | " << std::endl;
  std::cout << " |                   |                                                                 |     Banheiro      | " << std::endl;
  std::cout << " |                   |                                                                 |                   | " << std::endl;
  std::cout << " |                   |                                                                 |                   | " << std::endl;
  std::cout << " |"<<corredorName<< "|                                                                 |"<<banheiroName<< "| " << std::endl;
  std::cout << " |                   |                                                                 |                   | " << std::endl;
  std::cout << " |___________________|                     Andar no sentido horário                    |___________________| " << std::endl;
  std::cout << " |                   |                                                                 |                   | " << std::endl;
  std::cout << " |     Museu         |                                                                 |       Cabine      | " << std::endl;
  std::cout << " |                   |                                                                 |                   | " << std::endl;
  std::cout << " |" <<museuName<<   "|                                                                 |"<<cabineName<<   "| " << std::endl;
  std::cout << " |                  _|_________________________________________________________________|                   | " << std::endl;
  std::cout << " |                _|                 |                                      |          |_                  | " << std::endl;
  std::cout << " |            ___|                   |                                      |            |__               | " << std::endl;
  std::cout << " |        ____|           DA         |              Lounge                  |   CRC         |___           | " << std::endl;
  std::cout << " |     __|                           |                                      |                   |__        | " << std::endl;
  std::cout << " |   __|      " << daName  <<   "    |         " << loungeName <<"          |                      |__     | " << std::endl;
  std::cout << " |  |                                |                                      |  " << crcName  <<  "    |__  | " << std::endl;
  std::cout << " |__|                                |                                      |                            |_| " << std::endl;
  std::cout << " |___________________________ _______|______________________________________|______________________________| " << std::endl;
}