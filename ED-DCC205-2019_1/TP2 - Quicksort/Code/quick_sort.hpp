#ifndef QUICKSORT
#define QUICKSORT

#include "sort.hpp"
#include "insertion_sort.hpp"

#include <iostream>
#include <string>

#define Partition(name) int (*name)(long long*, int, int)
#define ChangeSort(name) bool (*name)(int, int)

class Quicksort : public Sort{
public:
	Quicksort() : Sort(){
		this->partition = Quicksort::MIDDLE_ELEMENT_PARTITION;
		this->change_sort = Quicksort::NO_CHANGE_SORT;
		this->iterative = false;
	}

	Quicksort(Partition(partition), ChangeSort(change_sort), bool iterative) : Sort(){
		this->partition = partition;
		this->change_sort = change_sort;
		this->iterative = iterative;
	}

	void sort(long long *arr, int left, int right) override {
		if(this->iterative)	iterative_sort(arr, left, right);
		else recursive_sort(arr, left, right);
	}

	/* -------------------- PARTITIONS -------------------- */
	static int FIRST_ELEMENT_PARTITION(long long *arr, int left, int right){
		return left;
	};

	static int MIDDLE_ELEMENT_PARTITION(long long *arr, int left, int right){
		return (left + right) / 2;
	};

	static int MEDIAN_OF_3_PARTITION(long long *arr, int left, int right){
		int a = left, b = (left + right) / 2, c = right;
		if(arr[a - b] * arr[b - c] > 0) return b;
		if(arr[a - b] * arr[a - c] > 0) return c;
		return a;
	};

	/* -------------------- CHANGE SORTS -------------------- */
	static bool NO_CHANGE_SORT(int left, int right){
		return false;
	};

private:
	Partition(partition);
	ChangeSort(change_sort);
	bool iterative;

	void recursive_sort(long long *arr, int left, int right){
		this->add_comparision(1); // If embaixo
		if(this->change_sort(left, right)){
			InsertionSort insertion = InsertionSort();
			insertion.sort(arr, left, right);
		}else{
			int *p = partitionate_array(arr, left, right);
			if(p[1] > left) recursive_sort(arr, left, p[1]);
			if(p[0] < right) recursive_sort(arr, p[0], right);
			this->add_comparision(2); // Dois ifs em cima
		}
	}

	void iterative_sort(long long *arr, int left, int right){
		int stack[right - left + 1];
		int top = -1;

		stack[++top] = left;
		stack[++top] = right;

		while(top >= 0){
			this->add_comparision(1); // If do while
			right = stack[top--];
			left = stack[top--];

			int *p = partitionate_array(arr, left, right);

			this->add_comparision(1); // If embaixo
			if (p[1] > left) {
				stack[++top] = left;
				stack[++top] = p[1];
			}

			this->add_comparision(1); // If embaixo
			if (p[0] < right) {
				stack[++top] = p[0];
				stack[++top] = right;
			}
		}

		this->add_comparision(1); // Teste do while que deu false
	}

	int* partitionate_array(long long *arr, int left, int right){
    long long pivot = arr[this->partition(arr, left, right)];

		int i = left;
		int j = right;

		while(i <= j){
			while(arr[i] < pivot){
				i++;
				this->add_comparision(1); // Teste do while
			}
			this->add_comparision(1); // Teste que deu false do while

			while(arr[j] > pivot){
				j--;
				this->add_comparision(1); // Teste do while
			}
			this->add_comparision(1); // Teste que deu false do while

			if(i <= j) swap(arr[i++], arr[j--]);
			this->add_comparision(2); // Um para o if e outro para o loop
		}
		this->add_comparision(1); // Teste que deu false do while

		return new int[2]{i, j};
	}

	void swap(long long& a, long long &b){
		long long t = a;
		a = b;
		b = t;

		this->add_move(2);
	}
};

#endif
