#ifndef SORT
#define SORT

#include <string>

class Sort{
public:
	Sort(int operation_cost){
		this->operation_count = 0;
		this->operation_cost = operation_cost;
	}

	virtual void sort(int arr[], int left, int right) = 0;

	int get_operation_count(){
		return this->operation_count;
	}

	void reset_operation_count(){
		this->operation_count = 0;
	}

	virtual ~Sort(){}
private:
	int operation_count;
	int operation_cost;

protected:
	void add_operation(){
		this->operation_count += operation_cost;
	}
};

#endif
