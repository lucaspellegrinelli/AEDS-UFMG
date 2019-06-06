#ifndef QUICKSORT
#define QUICKSORT

#include "sort.hpp"
#include "insertion_sort.hpp"
#include "partition_function.hpp"
#include "change_sort_function.hpp"

#include <iostream>
#include <string>

class Quicksort : public Sort{
public:
	Quicksort(std::string variation) : Sort(2){
		this->variation = variation;
	}

	void sort(int arr[], int left, int right) override {
		if(variation == "QNR"){
			PartitionFunction *partition = new Classic();
			ChangeSortFunction *change_sort = new NoChangeFunction();

			iterative_sort(arr, left, right, partition, change_sort);
		}else{
			PartitionFunction *partition;
			ChangeSortFunction *change_sort;

			Sort *insertion = new InsertionSort();

			if(this->variation == "QC"){
				partition = new Classic();
				change_sort = new NoChangeFunction();
			}else if(variation == "QM3"){
				partition = new Median();
				change_sort = new NoChangeFunction();
			}else if(variation == "QPE"){
				partition = new FirstElement();
				change_sort = new NoChangeFunction();
			}else if(variation == "QT1"){
				partition = new Median();
				change_sort = new ChangeSortFunction(insertion, 0.01, right - left);
			}else if(variation == "QT5"){
				partition = new Median();
				change_sort = new ChangeSortFunction(insertion, 0.05, right - left);
			}else if(variation == "QT10"){
				partition = new Median();
				change_sort = new ChangeSortFunction(insertion, 0.1, right - left);
			}

			recursive_sort(arr, left, right, partition, change_sort);
		}
	}

	~Quicksort(){}
private:
	std::string variation;

	void swap(int& a, int &b){
		int temp = a;
		a = b;
		b = temp;

		this->add_operation();
	}

	int partitionate_array(int arr[], int left, int right, PartitionFunction*& partition){
    int pivot = arr[(*partition)(arr, left, right)];

		while (left <= right){
			while (arr[left] < pivot) left++;
			while (arr[right] > pivot) right--;
			if(left <= right) swap(arr[left++], arr[right++]);
		}

		return right;
	}

	void recursive_sort(int arr[], int left, int right, PartitionFunction*& partition, ChangeSortFunction*& change_sort){
		if(left < right){
			if((*change_sort)(left, right)){
				change_sort->get_new_sort()->sort(arr, left, right);
			}else{
				int p = partitionate_array(arr, left, right, partition);
				recursive_sort(arr, left, p - 1, partition, change_sort);
				recursive_sort(arr, p + 1, right, partition, change_sort);
			}
		}
	}

	void iterative_sort(int arr[], int left, int right, PartitionFunction*& partition, ChangeSortFunction*& change_sort){
		int stack[right - left + 1];
		int top = -1;

		stack[++top] = left;
		stack[++top] = right;

		while(top >= 0){
			right = stack[top--];
			left = stack[top--];

			int p = partitionate_array(arr, left, right, partition);

			if (p - 1 > left) {
				stack[++top] = left;
				stack[++top] = p - 1;
			}

			if (p + 1 < right) {
				stack[++top] = p + 1;
				stack[++top] = right;
			}
		}
	}
};

#endif
