#ifndef SORT_REQUEST
#define SORT_REQUEST

#include "quick_sort.hpp"

#include <string>

class SortRequest{
public:
	SortRequest(std::string variation, std::string arr_type, std::string arr_size, bool print_arr){
		this->variation = variation;
		this->arr_type = arr_type;
		this->arr_size = std::stoi(arr_size);
		this->print_arr = print_arr;
	}

	void run(){
		Quicksort *qs = new Quicksort(variation);
	}

	std::string get_variation(){
		return this->variation;
	}

	std::string get_arr_type(){
		return this->arr_type;
	}
private:
	std::string variation;
	std::string arr_type;
	int arr_size;
	bool print_arr;
};

#endif
