#ifndef PARTITION_FUNCTION
#define PARTITION_FUNCTION

#include <iostream>

class PartitionFunction{
public:
	PartitionFunction(){}
	virtual int operator() (long long *arr, int left, int right) = 0;
};

class Classic: public PartitionFunction{
public:
	Classic(){}
	virtual int operator() (long long *arr, int left, int right){
		return (left + right) / 2;
	}
};

class Median: public PartitionFunction{
public:
	Median(){}
	virtual int operator() (long long *arr, int left, int right){
		int a_index = left;
		int a = arr[a_index];
		int b_index = right;
		int b = arr[b_index];
		int c_index = (left + right) / 2;
		int c = arr[c_index];

		if(a > b){
			if(b > c) return b_index;
			else if(a > c) return c_index;
			else return a_index;
		}else{
			if (a > c) return a_index;
			else if (b > c)	return c_index;
			else return b_index;
		}
	}
};

class FirstElement: public PartitionFunction{
public:
	FirstElement(){}
	virtual int operator() (long long *arr, int left, int right){
		return left;
	}
};

#endif
