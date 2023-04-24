#pragma once

using namespace std;

template <typename T>
class Vector
{
	int capacity;
	int size;
	T* arr;
public:
	Vector() 
		: arr(new T[1]), capacity(1), size(0) {};

	Vector(const int size, const T& value) : arr(new T[size]), capacity(size), size(size) {
		for (int i = 0; i < size; i++) {
			arr[i] = value;
		}
	};

	Vector(const Vector& second) {
		T* temp = new T[second.capacity];

		size = second.size;
		capacity = second.capacity;

		for (int i = 0; i < size; i++) {
			temp[i] = second[i];
		}

		delete[] arr;

		arr = temp;
	};

	Vector(Vector&& second)
		: size(std::move(second.size)), capacity(std::move(second.capacity)), arr(std::move(second.arr)) {
		second.size = 0;
		second.arr = nullptr;
	};

	~Vector() { delete[] arr; };

	// assignment operators

	T& operator[](int index) {
		return arr[index];
	};

	Vector& operator=(const Vector& second) {
		if (this != second) {

			size = second.size;
			capacity = second.capacity;

			arr = new T[capacity];

			for (int i = 0; i < size; i++) {
				arr[i] = second.arr[i];
			}
		}
	};

	// pop, push, pushAtIndex(?), print

	void pop() { size--; };

	void pop_front() {
		T* temp = new T[capacity-1];

		for (int i = 1; i < size; i++) {
			temp[i - 1] = arr[i];
		}

		delete[] arr;

		arr = temp;

		size--;
	}

	void push(T data) {
		if (size == capacity) {
			T* temp = new T[2 * capacity];

			for (int i = 0; i < size; i++) {
				temp[i] = arr[i];
			}

			delete[] arr;

			capacity = capacity * 2;
			arr = temp;
		}

		// push data at the back

		arr[size] = data;
		size++;
	};

	void print(){
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
	};

	int getSize() const{ 
		return size; 
	};

	int getCapacity() const{
		return capacity; 
	};

	bool getEmpty() const {
		return (size == 0);
	};
};

