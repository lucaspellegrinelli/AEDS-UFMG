#ifndef SORT_REQUEST
#define SORT_REQUEST

#include "quick_sort.hpp"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <string>

#define MAX_RAND_N 9223372036854775806
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
		Quicksort *qs;

		if(this->variation == "QC"){
			qs = new Quicksort(Quicksort::MIDDLE_ELEMENT_PARTITION, 0.0, false);
		}else if(this->variation == "QM3"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.0, false);
		}else if(this->variation == "QPE"){
			qs = new Quicksort(Quicksort::FIRST_ELEMENT_PARTITION, 0.0, false);
		}else if(this->variation == "QT1"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.01, false);
		}else if(this->variation == "QT5"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.05, false);
		}else if(this->variation == "QT10"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.1, false);
		}else if(this->variation == "QNR"){
			qs = new Quicksort(Quicksort::MIDDLE_ELEMENT_PARTITION, 0.0, true);
		}

		long long **arrs = new long long*[NUMBER_OF_TESTS];
		long long *comparisions = new long long[NUMBER_OF_TESTS];
		long long *moves = new long long[NUMBER_OF_TESTS];
		long long *times = new long long[NUMBER_OF_TESTS];

		for(int i = 0; i < NUMBER_OF_TESTS; i++){
			qs->reset_comparasion_count();
			qs->reset_move_count();

			arrs[i] = generate_array(this->arr_type, this->arr_size);
			long long *arr_copy = copy_array(arrs[i], this->arr_size);

			times[i] = time_sort(qs, arr_copy, this->arr_size);

			comparisions[i] = qs->get_comparation_count();
			moves[i] = qs->get_move_count();
		}

		long long avg_comp = get_average(comparisions, NUMBER_OF_TESTS);
		long long avg_moves = get_average(moves, NUMBER_OF_TESTS);
		long long med_times = get_median(times, NUMBER_OF_TESTS);

		output_sort_info(avg_comp, avg_moves, med_times);

		if(this->print_arr){
			for(int i = 0; i < NUMBER_OF_TESTS; i++){
				output_array(arrs[i], this->arr_size);
			}
		}
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
		Quicksort *qs = new Quicksort();
		qs->sort(arr, 0, size - 1);

		if(size % 2 == 0){
			return (arr[size / 2] + arr[size / 2 - 1]) / 2;
		}else{
			return arr[size / 2];
		}
	}

	long long time_sort(Quicksort *qs, long long *arr, int size){
		auto begin = std::chrono::high_resolution_clock::now();
		qs->sort(arr, 0, size - 1);
		auto end = std::chrono::high_resolution_clock::now();
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
