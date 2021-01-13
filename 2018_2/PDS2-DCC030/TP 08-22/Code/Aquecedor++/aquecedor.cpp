#include "aquecedor.h"
#include <iostream>

Aquecedor::Aquecedor(){
  this->temperatura = 20;
  this->temp_minima = 10;
  this->temp_maxima = 40;
  this->fat_inc = 5;
}

Aquecedor::Aquecedor(double temp_init){
  this->temperatura = temp_init;
  this->temp_minima = 10;
  this->temp_maxima = 40;
  this->fat_inc = 5;
}

Aquecedor::Aquecedor(double temp_init, double fat_inc){
  this->temperatura = temp_init;
  this->temp_minima = 10;
  this->temp_maxima = 40;
  this->fat_inc = fat_inc;
}

void Aquecedor::aquecer(){
  if(this->temperatura + fat_inc > temp_maxima) return;
  this->temperatura += fat_inc;
}

void Aquecedor::resfriar(){
  if(this->temperatura - fat_inc < temp_minima) return;
  this->temperatura -= fat_inc;
}

double Aquecedor::get_temperatura(){
  return temperatura;
}

void Aquecedor::set_fator_incremento(double fat_inc){
  this->fat_inc = fat_inc;
}
