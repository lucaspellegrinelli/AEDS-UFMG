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

  bool more_equal(Student other, int course){
    if(this->grade == other.grade){
      if(this->first_option == other.first_option){
        return this->id < other.id;
      }else{
        return this->first_option == course;
      }
    }else{
      return this->grade > other.grade;
    }
  }

  bool operator>=(Student other) const{
    if(this->grade != other.grade){
      return this->grade >= other.grade;
    }else{
      return this->id <= other.id;
    }
  }
};

#endif
