#pragma once
#include "Vector.h"

template <typename T>
class Queue {
	Vector<T> arr;
public:
	void push(const T& ele) {
		arr.push(ele);
	}

	void pop() {
		arr.pop_front();
	}

	T& front() const{
		return arr[0];
	}

	int size() const{
		return arr.getSize();
	}

	bool empty() const {
		return arr.getEmpty();
	}
};