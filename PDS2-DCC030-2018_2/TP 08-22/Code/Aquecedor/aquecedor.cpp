#include "aquecedor.h"

Aquecedor::Aquecedor(){
  this->temperatura = 20;
}

void Aquecedor::aquecer(){
  this->temperatura += 5;
}

void Aquecedor::resfriar(){
  this->temperatura -= 5;
}

double Aquecedor::get_temperatura(){
  return temperatura;
}
