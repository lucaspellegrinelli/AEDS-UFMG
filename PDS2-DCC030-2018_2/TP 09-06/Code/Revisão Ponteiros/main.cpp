#include <iostream>

#define SIZE 5

int main(){
  long value1 = 200000;
  long value2;

  long *long_ptr = &value1;

  std::cout << *long_ptr << " ";

  value2 = *long_ptr;

  std::cout << value2 << " ";

  std::cout << "0x*" << " ";
  //std::cout << &value1 << " ";

  std::cout << "0x*" << " ";
  //std::cout << long_ptr << " ";

  std::cout << (&value1 == long_ptr) << " ";

  unsigned int values[SIZE] = {2, 4, 6, 8, 10};

  unsigned int *v_ptr = values;

  for(int i = 0; i < SIZE; i++){
  std::cout << values[i] << " ";
  }

  v_ptr = &values[0];

  v_ptr = values;

  for(int i = 0; i < SIZE; i++){
  std::cout << *(v_ptr + i) << " ";
  }

  for(int i = 0; i < SIZE; i++){
  std::cout << *(values + i) << " ";
  }

  for(int i = 0; i < SIZE; i++){
  std::cout << v_ptr[i] << " ";
  }

  std::cout << values[4] << " ";
  std::cout << *(values + 4) << " ";
  std::cout << v_ptr[4] << " ";
  std::cout << *(v_ptr + 4) << " ";

  std::cout << "0x*" << " ";
  //std::cout << (v_ptr + 3) << " ";
  std::cout << *(v_ptr + 3) << " ";

  v_ptr = &values[4];

  std::cout << "0x*" << " ";
  //std::cout << v_ptr << " ";

  std::cout << *(v_ptr - 4) << " ";

  return 0;
}
