#pragma once

#include "Vector.h";
#include "String.h";
#include "Heap.h"

template <typename KeyType, typename ValueType>
class HashMap
{
private:
	struct Node
	{
		KeyType key;
		ValueType value;
		Node* next;

		Node(const int key, const string_& value) : key(key), value(value), next(nullptr) {};
	};

	Vector<Vector<edge>> buckets_;
	int capacity_;
	int size_;

	size_t hash(const KeyType& key)
	{
		// Compute the hash value for the given key
		// You can use any hash function that suits your needs
		// In this example, a simple modulo operation is used
		return key % capacity_;
	}
public:
    HashMap(size_t capacity) : capacity_(capacity_), size(0)
    {
        buckets_.reserve(capacity);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        int index = hash(key);

        auto& bucket = buckets_[index];

        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const Node& node) {
            return node.key == key;
            });

        if (it != bucket.end())
        {
            it->value = value;
        }
        else
        {
            // Insert a new node
            bucket.push(key, value);
            size++;
        }
    }

    ValueType retrieve(const KeyType& key)
    {
        size_t index = hash(key);

        auto& bucket = buckets_[index];

        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const Node& node) {
            return node.key == key;
            });

        if (it != bucket.end())
        {
            return it->value;
        }

        // Return a default-constructed value if key is not found
        return ValueType();
    }

    size_t getSize() const
    {
        return size;
    }
};
