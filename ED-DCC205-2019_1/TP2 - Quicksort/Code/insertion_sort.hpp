#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "sort.hpp"

class InsertionSort : public Sort{
public:
	InsertionSort() : Sort(){ }

	void sort(long long *arr, int left, int right) override{
		for (int i = left + 1; i < right; i++){
			long long key = arr[i];
			int j = i - 1;

			while (j >= left && arr[j] > key){
				arr[j + 1] = arr[j];
				j = j - 1;
			}

			arr[j + 1] = key;
		}
	}

	~InsertionSort(){}
};

#endif
