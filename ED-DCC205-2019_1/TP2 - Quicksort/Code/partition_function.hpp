class PartitionFunction{
public:
	PartitionFunction(){}
	virtual int operator() (int arr[], int left, int right) = 0;
};

class Classic: public PartitionFunction{
public:
	Classic(){}
	virtual int operator() (int arr[], int left, int right){
		return (left + right) / 2;
	}
}

class Median: public PartitionFunction{
public:
	Median(){}
	virtual int operator() (int arr[], int left, int right){
		int a_index = left;
		int a = arr[a];
		int b_index = right - 1;
		int b = arr[b];
		int c_index = (left + right) / 2;
		int c = arr[c];

		if(a > b){
			if(b > c) return b_index;
			else if(a > c) return c_index;
			else return a;
		}else{
			if (a > c) return a_index;
			else if (b > c)	return c_index;
			else return b;
		} 
	}
}

class FirstElement: public PartitionFunction{
public:
	FirstElement(){}
	virtual int operator() (int arr[], int left, int right){
		return left;
	}
}