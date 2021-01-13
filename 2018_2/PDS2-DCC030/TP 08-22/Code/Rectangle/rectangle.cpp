#include "rectangle.h"

Rectangle::Rectangle(float width, float height){
  this->width = width;
  this->height = height;
}

Rectangle::Rectangle(){
  this->width = 1;
  this->height = 1;
}

float Rectangle::get_width(){
  return width;
}

float Rectangle::get_height(){
  return height;
}

void Rectangle::set_width(float width){
  this->width = width;
}

void Rectangle::set_height(float height){
  this->height = height;
}

float Rectangle::get_perimeter(){
  return 2 * height + 2 * width;
}

float Rectangle::get_area(){
  return height * width;
}
