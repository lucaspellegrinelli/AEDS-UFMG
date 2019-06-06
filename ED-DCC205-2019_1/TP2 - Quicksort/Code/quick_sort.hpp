#ifndef QUICKSORT
#define QUICKSORT

#include "sort.hpp"
#include "insertion_sort.hpp"

#include <iostream>
#include <string>

#define Partition(name) int (*name)(long long*, int, int)

class Quicksort : public Sort{
public:
	Quicksort() : Sort(){
		this->partition = Quicksort::MIDDLE_ELEMENT_PARTITION;
		this->iterative = false;
		this->change_sort_perc = 0.0;
		this->change_sort_limit = 0;
	}

	Quicksort(Partition(partition), double change_sort_perc, bool iterative) : Sort(){
		this->partition = partition;
		this->iterative = iterative;
		this->change_sort_perc = change_sort_perc;
		this->change_sort_limit = 0;
	}

	void sort(long long *arr, int left, int right) override {
		this->change_sort_limit = (right - left + 1) * change_sort_perc;

		if(this->iterative){
			iterative_sort(arr, left, right);
		}else {
			recursive_sort(arr, left, right);
		}

		this->change_sort_limit = 0;
	}

	/* -------------------- PARTITIONS -------------------- */
	static int FIRST_ELEMENT_PARTITION(long long *arr, int left, int right){
		return left;
	};

	static int MIDDLE_ELEMENT_PARTITION(long long *arr, int left, int right){
		return (left + right) / 2;
	};

	static int MEDIAN_OF_3_PARTITION(long long *arr, int left, int right){
		int a_index = left;
		int b_index = (left + right) / 2;
		int c_index = right;

		long long a = arr[a_index];
		long long b = arr[b_index];
		long long c = arr[c_index];
		
		if(a > b){
			if(b > c) return b_index;
			else if(a > c) return c_index;
			else return a_index;
		}else {
			if(a > c)	return a_index;
			else if(b > c)	return c_index;
			else return b_index;
		}
	};

private:
	Partition(partition);
	bool iterative;
	double change_sort_perc;
	int change_sort_limit;

	void recursive_sort(long long *arr, int left, int right){
		this->add_comparision(1); // If embaixo
		if((right - left + 1) <= this->change_sort_limit){
			InsertionSort insertion = InsertionSort();
			insertion.sort(arr, left, right);

			// Adicionando as comparações/movimentos do outro sort
			this->add_comparision(insertion.get_comparation_count());
			this->add_move(insertion.get_move_count());
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
			this->add_comparision(2); // Um para o if e outro para o while
		}
		this->add_comparision(1); // Teste que deu false do while

		return new int[2]{i, j};
	}

	void swap(long long& a, long long &b){
		long long t = a;
		a = b;
		b = t;

		this->add_move(2); // As duas movimentações de valores
	}
};

#endif
