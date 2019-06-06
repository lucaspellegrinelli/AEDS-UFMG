#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "sort.hpp"

class InsertionSort : public Sort{
public:
	InsertionSort() : Sort(){ }

	void sort(long long *arr, int left, int right) override{
		for (int i = left + 1; i < right; i++){
			this->add_comparision(1); // Teste do for

			long long key = arr[i];
			int j = i - 1;

			while (j >= left && arr[j] > key){
				this->add_comparision(1); // Teste do while
				arr[j + 1] = arr[j];
				j = j - 1;
			}

			this->add_comparision(1); // Teste que falhou do while

			arr[j + 1] = key;
		}

		this->add_comparision(1); // Teste que falhou do for
	}

	~InsertionSort(){}
};

#endif
