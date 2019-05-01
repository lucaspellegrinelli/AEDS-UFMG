#ifndef ALUNO_H
#define ALUNO_H

#include <string>

class Student{
public:
  std::string name;
  float grade;
  int first_option;
  int second_option;

  Student(){ }

  Student(std::string name, float grade, int first_option, int second_option){
    this->name = name;
    this->grade = grade;
    this->first_option = first_option;
    this->second_option = second_option;
  }
};

#endif
