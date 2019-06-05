#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "sort.hpp"

class InsertionSort : public Sort{
public:
	InsertionSort() : Sort(1){	}

	virtual void sort(int arr[], int left, int right, std::string variation){
		for (int i = left + 1; i < right; i++){
			int key = arr[i];
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