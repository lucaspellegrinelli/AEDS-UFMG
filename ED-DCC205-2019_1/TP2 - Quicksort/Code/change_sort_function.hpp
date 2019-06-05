#ifndef CHANGE_SORT_FUNCTION
#define CHANGE_SORT_FUNCTION

#include "sort.hpp"

class ChangeSortFunction{
public:
	ChangeSortFunction(){ }

	ChangeSortFunction(Sort *new_sort, double percent, int original_size){
		this->new_sort = new_sort;
		this->limit = (int)(percent * original_size);
	}

	virtual bool operator() (int left, int right){
		return (right - left) <= this->limit;
	}

	Sort * get_new_sort(){
		return this->new_sort;
	}

	~ChangeSortFunction(){
		delete this->new_sort;
	}
private:
	int limit;
	Sort *new_sort;
};

class NoChangeFunction : public ChangeSortFunction{
public:
	NoChangeFunction() : ChangeSortFunction(){ }

	virtual bool operator() (int left, int right){
		return false;
	}
};

#endif