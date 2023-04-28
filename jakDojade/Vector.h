#pragma once

using namespace std;

template <typename T>
class Vector
{
	int capacity_{};
	int size_{};
	T* arr_;
public:
	Vector();

	Vector(const int size, const T& value);

	Vector(const int size);

	Vector(const Vector& second);

	Vector(Vector&& second) noexcept;

	~Vector();

	// assignment operators

	T& operator[](int index);

	T& operator[](int index) const;

	bool operator==(const Vector& other) {
		return this->arr_ == other.arr_ && this->size_ == other.size_ && this->capacity_ == other.capacity_;
	}

	bool operator!= (const Vector& other) {
		return !this->operator==(other);
	}

	Vector& operator=(const Vector& second);

	void pop();

	void pop_front();

	void push(T data);

	void print();

	void reserve(int new_capacity);

	[[nodiscard]] int get_size() const;

	[[nodiscard]] int get_capacity() const;

	[[nodiscard]] bool get_empty() const;

	class Iterator { 

		const Vector<T>* current_;
		int index_;

	public:
		Iterator(const Vector<T>* current_, int index_);

		const T& operator*() const;

		Iterator& operator++();

		bool operator==(const Iterator& other) const;

		bool operator!=(const Iterator& other) const;

		Vector<T>::Iterator operator->() const;
	};

	[[nodiscard]] Iterator begin() const;

	[[nodiscard]] Iterator end() const;
};

// functions for vector

template <typename T>
Vector<T>::Vector(): capacity_(10), size_(0), arr_(new T[10])
{}

template <typename T>
Vector<T>::Vector(const int size, const T& value): capacity_(size), size_(size), arr_(new T[size])
{
	for (int i = 0; i < size; i++) {
		arr_[i] = value;
	}
}

template<typename T>
inline Vector<T>::Vector(const int size)
{
	this->arr_ = new T[size];
	this->capacity_ = size;
	this->size_ = size;
}

template <typename T>
Vector<T>::Vector(const Vector& second)
{
	T* temp = new T[second.capacity_];

	size_ = second.size_;
	capacity_ = second.capacity_;

	for (int i = 0; i < size_; i++) {
		temp[i] = second[i];
	}

	delete[] arr_;

	arr_ = temp;
}

template <typename T>
Vector<T>::Vector(Vector&& second) noexcept: capacity_(std::move(second.capacity_)), size_(std::move(second.size_)), arr_(std::move(second.arr_))
{
	second.size_ = 0;
	second.arr_ = nullptr;
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] arr_;
	size_ = 0;
	capacity_ = 1;
}

template <typename T>
T& Vector<T>::operator[](int index)
{
	return arr_[index];
}

template<typename T>
inline T& Vector<T>::operator[](int index) const
{
	return this->arr_[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& second)
{
	if (*this != second) {

		size_ = second.size_;
		capacity_ = second.capacity_;

		arr_ = new T[capacity_];

		for (int i = 0; i < size_; i++) {
			arr_[i] = second.arr_[i];
		}
	}

	return *this;
}

template <typename T>
void Vector<T>::pop()
{ size_--; }

template <typename T>
void Vector<T>::pop_front()
{
	if (size_ == 0) return;

	for (int i = 0; i < size_ - 1; i++) {
		arr_[i] = arr_[i + 1];
	}

	size_--;
}

template <typename T>
void Vector<T>::push(T data)
{

	if (size_ >= capacity_) {
		T* temp = new T[2 * capacity_];

		for (int i = 0; i < size_; i++) {
			temp[i] = arr_[i];
		}

		capacity_ = capacity_ * 2;

		swap(arr_, temp);

		delete[] temp;
	}

	// push data at the back

	arr_[size_] = data;
	size_++;
}

template <typename T>
void Vector<T>::print()
{
	for (int i = 0; i < size_; i++) {
		cout << arr_[i] << " ";
	}
}

template <typename T>
void Vector<T>::reserve(int new_capacity) {
	if (new_capacity > capacity_) {

		T* new_data = new T[new_capacity];
		if (arr_) {
			std::copy(arr_, arr_ + size_, new_data);
			delete[] arr_;
		}

		arr_ = new_data;
		capacity_ = new_capacity;
	}
}

template <typename T>
int Vector<T>::get_size() const
{ 

	return size_; 
}

template <typename T>
int Vector<T>::get_capacity() const
{
	return capacity_; 
}

template <typename T>
bool Vector<T>::get_empty() const
{
	return (size_ == 0);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const
{
	return Iterator(this, 0);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const
{
	return Iterator(this, size_);
}
// functions for iterator

template <typename T>
Vector<T>::Iterator::Iterator(const Vector<T>* current_, int index_)
	: current_(current_), index_(index_) {}

template <typename T>
const T& Vector<T>::Iterator::operator*() const
{
	return current_->arr_[index_];
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	index_++;
	return *this;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& other) const
{
	return current_ == other.current_;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& other) const
{
	return current_ != other.current_;
}
