//#include "game/game.h"
//
//#include <iostream>
//
//int main(){
//  const int NUMBER_OF_HUMANS = 1;
//  const int NUMBER_OF_BOTS = 5;
//
//  std::cout << "Criando jogo" << std::endl;
//
//  Game game = Game(NUMBER_OF_HUMANS, NUMBER_OF_BOTS);
//
//  std::cout << "Jogo criado, inicializando jogadores" << std::endl;
//
//  game.initializePlayers();
//
//  std::cout << "Jogadores inicializados:" << std::endl;
//
//  for(auto i : game.getPlayers()){
//    std::cout << "\t" << "[" << i->getId() << "] " << i->getName() << std::endl;
//  }
//
//  std::cout << std::endl;
//
//  game.run();
//
//  std::cout << "Jogo começou" << std::endl;
//}
//