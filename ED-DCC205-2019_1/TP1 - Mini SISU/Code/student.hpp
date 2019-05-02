#ifndef ALUNO_H
#define ALUNO_H

#include <string>

class Student{
public:
  int id;
  std::string name;
  float grade;
  int first_option;
  int second_option;

  Student(){ }

  Student(int id, std::string name, float grade, int first_option, int second_option){
    this->id = id;
    this->name = name;
    this->grade = grade;
    this->first_option = first_option;
    this->second_option = second_option;
  }

  bool apllied_for(int course){
    return this->first_option == course || this->second_option == course;
  }

  bool operator>=(Student other) const{
    if(this->grade != other.grade){
      return this->grade >= other.grade;
    }else{
      return this->id <= other.id;
    }
  }

  bool operator==(Student other) const{
    return this->id == other.id;
  }
};

#endif
