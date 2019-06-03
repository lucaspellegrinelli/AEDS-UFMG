#include "partition_function.hpp"

#define OPERATION_COST = 2

class Quicksort: public Sort{
public:
	Quicksort(int operation_cost, QuicksortRequest request) : Sort(operation_cost){
		this->request = request;
	}

	virtual void sort(int arr[], int left, int right){
		PartitionFunction *partition;

		swtich(this->request.get_variation()){
			case "QC":
				*partition = Classic();
				break;
			case "QM3":
				*partition = Median();
				break;
			case "QPE":
				*partition = FirstElement()/
				break;
			case "QT1":
				break;
			case "QT5":
				break;
			case "QT10":
				break;
			case "QNR":
				break;
		}
	}

	~Quicksort(){}
private:
	QuicksortRequest request;

	void recursive_sort(int arr[], int left, int right, PartitionFunction* partition){
		int i = left, j = right;

		int pivot_pos = (*partition)(arr, left, right);
		int pivot = arr[pivot_pos];

		while (i <= j) {
			while (arr[i] < pivot) i++;
			while (arr[j] > pivot) j--;
			
			if (i <= j) {
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;

				this->add_operation();
			}
		}

		if (left < j)	recursive_sort(arr, left, j);
		if (i < right) recursive_sort(arr, i, right);
	}

	void iterative_sort(int arr[], int left, int right, PartitionFunction* partition){

	}
};