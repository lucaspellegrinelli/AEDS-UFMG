#ifndef QUICKSORT
#define QUICKSORT

#include "sort.hpp"
#include "insertion_sort.hpp"
#include "partition_function.hpp"
#include "change_sort_function.hpp"

#include <string>

class Quicksort : public Sort{
public:
	Quicksort() : Sort(2){ }

	void sort(int arr[], int left, int right, std::string variation) override {
		if(variation == "QNR"){
			PartitionFunction *partition;
			ChangeSortFunction *change_sort;

			*partition = Classic();
			*change_sort = NoChangeFunction();

			iterative_sort(arr, left, right, partition, change_sort);
		}else{
			PartitionFunction *partition;
			ChangeSortFunction *change_sort;

			Sort *insertion;
			*insertion = InsertionSort();

			if(variation == "QC"){
				*partition = Classic();
				*change_sort = NoChangeFunction();
			}else if(variation == "QM3"){
				*partition = Median();
				*change_sort = NoChangeFunction();
			}else if(variation == "QPE"){
				*partition = FirstElement();
				*change_sort = NoChangeFunction();
			}else if(variation == "QT1"){
				*partition = Median();
				*change_sort = ChangeSortFunction(insertion, 0.01, right - left);
			}else if(variation == "QT5"){
				*partition = Median();
				*change_sort = ChangeSortFunction(insertion, 0.05, right - left);
			}else if(variation == "QT10"){
				*partition = Median();
				*change_sort = ChangeSortFunction(insertion, 0.1, right - left);
			}

			recursive_sort(arr, left, right, partition, change_sort);
		}
	}

	~Quicksort(){}
private:
	void recursive_sort(int arr[], int left, int right, PartitionFunction*& partition, ChangeSortFunction*& change_sort){
		if((*change_sort)(left, right)){
			change_sort->get_new_sort()->sort(arr, left, right);
		}else{
			int i = left, j = right;

			int pivot_pos = (*partition)(arr, left, right);
			int pivot = arr[pivot_pos];

			while (i <= j) {
				while (arr[i] < pivot) i++;
				while (arr[j] > pivot) j--;
				
				if (i <= j) {
					int tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					i++;
					j--;

					this->add_operation();
				}
			}

			if (left < j)	recursive_sort(arr, left, j, partition, change_sort);
			if (i < right) recursive_sort(arr, i, right, partition, change_sort);
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

			if((*change_sort)(left, right)){
				change_sort->get_new_sort()->sort(arr, left, right);
				break;
			}else{
				int i = left, j = right;

				int pivot_pos = (*partition)(arr, left, right);
				int pivot =  arr[pivot_pos];

				while (i <= j) {
					while (arr[i] < pivot) i++;
					while (arr[j] > pivot) j--;
					
					if (i <= j) {
						int tmp = arr[i];
						arr[i] = arr[j];
						arr[j] = tmp;
						i++;
						j--;

						this->add_operation();
					}
				}

				if (pivot - 1 > i) {
					stack[++top] = i;
					stack[++top] = pivot - 1;
				}

				if (pivot + 1 < j) {
					stack[++top] = pivot + 1;
					stack[++top] = j;
				}
			}
		}
	}
};

#endif