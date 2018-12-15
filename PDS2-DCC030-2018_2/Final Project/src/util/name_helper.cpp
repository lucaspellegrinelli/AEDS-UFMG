#include "util/name_helper.h"

NameHelper::NameHelper(){
  srand(time(NULL));
}

std::string NameHelper::generateName(bool bot_prefix){
  const int NAME_COUNT = 27;

  std::string look_up_list[NAME_COUNT] = {
    "Otavio", "Francisco", "Sandra", "Mirela", "Lorenzo", "Pedro", "Luiza", "Juliana", "Diogo", "Hugo",
    "Giovana", "Leticia", "Adriano", "Rodolfo", "Larissa", "Bianca", "Alessandro", "Antonio", "Cristina", "Thais",
    "Felisberto", "Edna", "Afonso", "Alfredo", "Flávio", "Loureiro", "Coutinho"
  };

  return (bot_prefix ? "BOT " : "") + look_up_list[rand() % NAME_COUNT];
}

std::string NameHelper::askForName(int id){
  std::string name;
  std::cout << std::endl << "Jogador, qual seu nome?" << std::endl;
  std::cin >> name;
  std::cout << std::endl;
  return name;
}
