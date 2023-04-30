#pragma once
#include <iostream>

#include "Vector.h"

struct edge {
	int city;
	int distance;
};

class Heap
{
private:
	Vector<edge> w_;
	int size_ = -1;

	static int parent(const int i) { return (i - 1) / 2; }
	static int left(const int i) { return i * 2 + 1; }
	static int right(const int i) { return i * 2 + 2; }

	void up_heap(int index)
	{
		while (index > 0)
		{
			if (w_[parent(index)].distance < w_[index].distance)
			{
				std::swap(w_[parent(index)], w_[index]);

				index = parent(index);
			}
			else break;
		}
	}

	void down_heap(const int index)
	{
		int max = index;
		const int l = left(index), r = right(index);

		if (l <= size_ && w_[l].distance < w_[max].distance) max = l;

		if (r <= size_ && w_[r].distance < w_[max].distance) max = r;

		if (index != max)
		{
			std::swap(w_[index], w_[max]);
			down_heap(max);
		}
	}
public:
	Heap() = default;

	~Heap() = default;

	[[nodiscard]] bool is_empty() const {
		return size_ == -1;
	}

	[[nodiscard]] int size() const {
		return size_ + 1;
	}

	void build_heap(const Vector<edge>& elements) {
		w_ = elements;
		size_ = elements.get_size() - 1;
		 
		for (int i = size_ / 2; i >= 0; i--) {
			down_heap(i);
		}
	}

	edge get_top()
	{
		return { w_[0].city, w_[0].distance };
	}


	edge delete_top()
	{
		const edge result = { w_[0].city, w_[0].distance };

		w_[0].city = w_[size_].city;
		w_[0].distance = w_[size_].distance;

		size_--;

		w_.pop_front();

		down_heap(0);

		return result;
	}

	void insert(const edge e1)
	{
		w_.push(e1);
		size_++;
		down_heap(size_);
	}

	void print_heap() const{
		for (int i = 0; i < w_.get_size(); i++) {
			cout << "(" << w_[i].city << ", " << w_[i].distance << ") ";
		}
		cout << endl;
	}
};
