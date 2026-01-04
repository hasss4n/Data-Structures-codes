#include <iostream>
using namespace std;

class Queue {
private: int queue_size;
	   int ifront;
	   int iback;
	   int array_capacity;
	   int* array;
public:
	Queue(int n):
		queue_size(0),
		ifront(0),
		iback(-1),
		array_capacity(n),
		array(new int[array_capacity]){ }
	bool empty()const {
		return(queue_size == 0);
	}
	int front()const {
		if (empty()) {
			throw underflow_error("Queue Overflow!");
		}
		return array[ifront];
	}
	void push(int n) {
		if (queue_size == array_capacity) {
			cout << "Queue Overflow! ";
		}
		++iback;
		if (iback == array_capacity) {
			iback = 0;
		}
		array[iback = n];
		++queue_size;
	}
	int pop() {
		if (empty()) {
			cout << "Queue Overflow! ";
		}
		--queue_size;
		++ifront;
		return array[ifront - 1];
	}

};