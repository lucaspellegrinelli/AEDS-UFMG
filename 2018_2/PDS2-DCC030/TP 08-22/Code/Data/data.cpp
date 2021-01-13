#include "data.h"

Data::Data(int dia, int mes, int ano){
  this->dia = dia;
  this->mes = mes;
  this->ano = ano;
}

int Data::get_dia(){
  return dia;
}

int Data::get_mes(){
  return mes;
}

int Data::get_ano(){
  return ano;
}

std::string Data::get_data_curto(){
  return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano);
}

std::string Data::get_data_longo(){
  std::string meses[12] = {
    "janeiro",
    "fevereiro",
    "marco",
    "abril",
    "maio",
    "junho",
    "julho",
    "agosto",
    "setembro",
    "outubro",
    "novembro",
    "dezembro"
  };
  
  return std::to_string(dia) + " de " + meses[mes - 1] + " de " + std::to_string(ano);
}
