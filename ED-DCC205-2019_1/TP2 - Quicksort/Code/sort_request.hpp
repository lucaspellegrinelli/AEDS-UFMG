#ifndef SORT_REQUEST
#define SORT_REQUEST

#include "quick_sort.hpp"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <string>

//#define MAX_RAND_N 9223372036854775806
#define MAX_RAND_N 3
#define NUMBER_OF_TESTS 20

class SortRequest{
public:
	SortRequest(std::string variation, std::string arr_type, std::string arr_size, bool print_arr){
		this->variation = variation;
		this->arr_type = arr_type;
		this->arr_size = std::stoi(arr_size);
		this->print_arr = print_arr;
	}

	void run(){
		Quicksort *qs = new Quicksort(this->variation);

		long long **arrs = new long long*[NUMBER_OF_TESTS];
		long long *comparisions = new long long[NUMBER_OF_TESTS];
		long long *moves = new long long[NUMBER_OF_TESTS];
		long long *times = new long long[NUMBER_OF_TESTS];

		for(int i = 0; i < NUMBER_OF_TESTS; i++){
			std::cout << 0 << std::endl;
			qs->reset_comparasion_count();
			std::cout << 1 << std::endl;
			qs->reset_move_count();
			std::cout << 2 << std::endl;
			arrs[i] = generate_array(this->arr_type, this->arr_size);
			std::cout << 3 << std::endl;
			long long *arr_copy = copy_array(arrs[i], this->arr_size);
			std::cout << 4 << std::endl;
			output_array(arr_copy, this->arr_size);
			times[i] = time_sort(qs, arr_copy, this->arr_size);
			output_array(arr_copy, this->arr_size);
			std::cout << 5 << std::endl;
			comparisions[i] = qs->get_comparation_count();
			std::cout << 6 << std::endl;
			moves[i] = qs->get_move_count();
		}

		std::cout << 7 << std::endl;

		long long avg_comp = get_average(comparisions, NUMBER_OF_TESTS);
		long long avg_moves = get_average(moves, NUMBER_OF_TESTS);
		long long med_times = get_median(times, NUMBER_OF_TESTS);

		output_sort_info(avg_comp, avg_moves, med_times);
	}
private:
	std::string variation;
	std::string arr_type;
	int arr_size;
	bool print_arr;

	long long get_average(long long *arr, int size){
		long long sum = 0;
		for(int i = 0; i < size; i++){
			sum += arr[i];
		}

		return sum / size;
	}

	long long get_median(long long *arr, int size){
		Quicksort *qs = new Quicksort("QM3");
		qs->sort(arr, 0, size - 1);

		if(size % 2 == 0){
			return (arr[size / 2] + arr[size / 2 - 1]) / 2;
		}else{
			return arr[size / 2];
		}
	}

	long long time_sort(Quicksort *qs, long long *arr, int size){
		std::cout << 41 << std::endl;
		auto begin = std::chrono::high_resolution_clock::now();
		std::cout << 42 << std::endl;
		qs->sort(arr, 0, size - 1);
		std::cout << 43 << std::endl;
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << 44 << std::endl;
		auto dur = end - begin;
		auto dur_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		return dur_in_ms;
	}

	long long * copy_array(long long *arr, int size){
		long long *new_arr = new long long[size];
		for(int i = 0; i < size; i++){
			new_arr[i] = arr[i];
		}
		return new_arr;
	}

	long long * generate_array(std::string type, int size){
		long long *arr = new long long[size];
		for(int i = 0; i < size; i++){
			if(type == "Ale") arr[i] = rand() % MAX_RAND_N;
			else if(type == "OrdC") arr[i] = i;
			else if(type == "OrdD") arr[i] = MAX_RAND_N - i;
		}

		return arr;
	}

	void output_sort_info(long long comparisions, long long moves, long long time){
		std::cout << this->variation << " " <<
								 this->arr_type << " " <<
								 this->arr_size << " " <<
								 comparisions << " " <<
								 moves << " " <<
								 time << std::endl;
	}

	void output_array(long long *arr, int size){
		for(int i = 0; i < size; i++){
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
};

#endif
