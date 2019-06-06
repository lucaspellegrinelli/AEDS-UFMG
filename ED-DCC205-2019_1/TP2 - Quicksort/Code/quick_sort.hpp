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
	Quicksort(std::string variation) : Sort(){
		this->variation = variation;
	}

	void sort(long long *arr, int left, int right) override {
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
private:
	std::string variation;

	void swap(long long& a, long long &b){
		long long t = a;
		a = b;
		b = t;

		this->add_move(2);
	}

	int* partitionate_array(long long *arr, int left, int right, PartitionFunction*& partition){
    long long pivot = arr[(*partition)(arr, left, right)];

		int i = left;
		int j = right;

		while(i <= j){
			while(arr[i] < pivot) i++;
			while(arr[j] > pivot) j--;
			if(i <= j) swap(arr[i++], arr[j--]);
		}

		int *r = new int[2];
		r[0] = i;
		r[1] = j;
		return r;
	}

	void recursive_sort(long long *arr, int left, int right, PartitionFunction*& partition, ChangeSortFunction*& change_sort){
		this->add_comparision(1);
		if(left < right){
			this->add_comparision(1);
			if((*change_sort)(left, right)){
				change_sort->get_new_sort()->sort(arr, left, right);
			}else{
				int *p = partitionate_array(arr, left, right, partition);
				if(p[1] > left) recursive_sort(arr, left, p[1], partition, change_sort);
				if(p[0] < right) recursive_sort(arr, p[0], right, partition, change_sort);
			}
		}
	}

	void iterative_sort(long long *arr, int left, int right, PartitionFunction*& partition, ChangeSortFunction*& change_sort){
		int stack[right - left + 1];
		int top = -1;

		stack[++top] = left;
		stack[++top] = right;

		while(top >= 0){
			this->add_comparision(1);
			right = stack[top--];
			left = stack[top--];

			int *p = partitionate_array(arr, left, right, partition);

			this->add_comparision(1);
			if (p[1] > left) {
				stack[++top] = left;
				stack[++top] = p[1];
			}

			this->add_comparision(1);
			if (p[0] < right) {
				stack[++top] = p[0];
				stack[++top] = right;
			}
		}

		this->add_comparision(1);
	}
};

#endif
