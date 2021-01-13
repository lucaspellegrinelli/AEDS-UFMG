#include "game/game.h"

#include <iostream>

#include "../include/exceptions/game_exceptions.h"

void show_welcome_message();

int main(){
  try{
    show_welcome_message();
    Game game;
    game.initializePlayers();
    game.run();
  }
  catch(InvalidOption& e) {
    std::cerr << "***ERROR: " << e.what() <<
    " : Encerrando execução***" << std::endl;
  }
  catch(...) {
    std::cerr << "Exceção inesperada" << std::endl;
  }
}

void show_welcome_message(){
  std::cout << "  ||||||||  ||||||||  ||||||||  ||||||||  ||||||||  ||||||||  ||||||||  |||  |||  |||||||| |||||||| ||||||||" << std::endl;
  std::cout << "  |||  |||  |||       |||       |||  |||  |||       |||          ||     |||  |||  |||  |||    ||    |||  |||" << std::endl;
  std::cout << "  |||  |||  |||       |||       |||  |||  |||       |||          ||     |||| |||  |||  |||    ||    |||  |||" << std::endl;
  std::cout << "  ||||||||  ||||||||  ||||||||  ||||||||  ||||||||  ||||||||     ||     ||| ||||  ||||||||    ||    |||  |||" << std::endl;
  std::cout << "  |||  |||       |||       |||  |||  |||       |||       |||     ||     |||  |||  |||  |||    ||    |||  |||" << std::endl;
  std::cout << "  |||  |||       |||       |||  |||  |||       |||       |||     ||     |||  |||  |||  |||    ||    |||  |||" << std::endl;
  std::cout << "  |||  |||  ||||||||  ||||||||  |||  |||  ||||||||  ||||||||  ||||||||  |||  |||  |||  |||    ||    ||||||||" << std::endl;
  std::cout << " "                                                                                                            << std::endl;
  std::cout << " "                                                                                                            << std::endl;
  std::cout << "                                              |||  |||  ||||||||"                                             << std::endl;
  std::cout << "                                              |||  |||  |||  |||"                                             << std::endl;
  std::cout << "                                              |||| |||  |||  |||"                                             << std::endl;
  std::cout << "                                              ||| ||||  |||  |||"                                             << std::endl;
  std::cout << "                                              |||  |||  |||  |||"                                             << std::endl;
  std::cout << "                                              |||  |||  |||  |||"                                             << std::endl;
  std::cout << "                                              |||  |||  ||||||||"                                             << std::endl;
  std::cout << " "                                                                                                            << std::endl;
  std::cout << " "                                                                                                            << std::endl;
  std::cout << "                                    ||||||||  ||||||||  ||||||||  |||  |||   |"                               << std::endl;
  std::cout << "                                       ||     |||       |||       |||  |||   |"                               << std::endl;
  std::cout << "                                       ||     |||       |||        ||||||    |"                               << std::endl;
  std::cout << "                                       ||     |||       ||||||||     ||      |"                               << std::endl;
  std::cout << "                                       ||     |||       |||        ||||||    |"                               << std::endl;
  std::cout << "                                       ||     |||       |||       |||  |||   |"                               << std::endl;
  std::cout << "                                    ||||||||  ||||||||  ||||||||  |||  |||   | ___"                           << std::endl;
  std::cout << " "                                                                                                            << std::endl;
}
