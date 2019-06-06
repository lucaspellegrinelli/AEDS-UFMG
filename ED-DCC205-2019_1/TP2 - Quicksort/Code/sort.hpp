#ifndef SORT
#define SORT

#include <string>

class Sort{
public:
	Sort(){
		this->comparasion_count = 0;
		this->move_count = 0;
	}

	virtual void sort(long long *arr, int left, int right) = 0;

	int get_comparation_count(){
		return this->comparasion_count;
	}

	int get_move_count(){
		return this->move_count;
	}

	void reset_comparasion_count(){
		this->comparasion_count = 0;
	}

	void reset_move_count(){
		this->move_count = 0;
	}

	virtual ~Sort(){}
private:
	int comparasion_count;
	int move_count;
	int operation_cost;

protected:
	void add_comparision(int how_much){
		this->comparasion_count += how_much;
	}

	void add_move(int how_much){
		this->move_count += how_much;
	}
};

#endif
