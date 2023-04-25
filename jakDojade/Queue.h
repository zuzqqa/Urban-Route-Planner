#pragma once
#include "Vector.h"

using namespace std;

template <typename T>
class queue {
	Vector<T> arr_;
public:
	void push(const T& ele) {
		arr_.push(ele);
	}

	void pop() {
		arr_.pop_front();
	}

	T& operator[](int index) {
		return arr_[index];
	}

	[[nodiscard]] T& front() {
		return arr_[0];
	}

	[[nodiscard]] int size() {
		return arr_.get_size();
	}

	[[nodiscard]] bool empty()  {
		return arr_.get_empty();
	}

	friend ostream& operator << (ostream& os, const queue& atr) {
		os << "Property: " << atr.arr_;
		return os;
	};
};