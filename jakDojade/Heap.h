#pragma once
#include <iostream> 

using namespace std;

// heap
int Parent(int i) { return (i - 1) / 2; }
int Left(int i) { return i * 2 + 1; }
int Right(int i) { return i * 2 + 2; }

void Heapify(int* arr, int i, int size) {
	int maxps;
	int left = Left(i);
	int right = Right(i);

	if (left <= size && arr[left - 1] > arr[i - 1]) {
		maxps = left;
	}
	else {
		maxps = i;
	}

	if (right <= size && arr[right - 1] > arr[maxps - 1]) {
		maxps = right;
	}
	if (maxps != i) {
		swap(arr[i - 1], arr[maxps - 1]);
		Heapify(arr, maxps, size);
	}
}

void BulidHeap(int* arr, int size) {
	for (int i = size; i >= 0; i--) {
		Heapify(arr, i, size);
	}
}

int HeapInsert(int* arr, int size, int newEle) {
	size = size + 1;
	int i = size;
	while (i > 1 && arr[Parent(i) - 1] < newEle) {
		arr[i - 1] = arr[Parent(i) - 1];
		i = Parent(i);
	}
	arr[i - 1] = newEle;

	return size;
}

int HeapGetMax(int* arr, int size) {
	int max = arr[0];

	arr[0] = arr[size - 1];

	size = size - 1;

	Heapify(arr, size);
	
	return 
}

class PriorityQueue {

};