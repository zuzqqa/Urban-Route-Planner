#pragma once

#include "Vector.h";
#include "String.h";
#include "Heap.h"

constexpr long long prime = 402653189;
constexpr long long prime1 = 201326611;
constexpr long long starting_hash = 3079;

template <typename KeyType, typename ValueType>
class HashMap
{
private:
	struct Node
	{
        KeyType key;
        ValueType value;
		Node* next;

		Node(const KeyType& key, const ValueType& value) : key(key), value(value), next(nullptr) {};

        ~Node()
        {
            delete value;
        }

        Node(const Node& other)
            : key(other.key), value(new ValueType(*(other.value)))
        {
        }

        Node& operator=(const Node& other)
        {
            if (this != &other)
            {
                key = other.key;
                delete value;
                value = new ValueType(*(other.value));
            }
            return *this;
        }
	};

	Vector<Vector<Node>> buckets_;
    long long int capacity_;
	long long int size_;
public:
	explicit HashMap(long long int capacity) : capacity_(capacity), size_(0)
    {
        buckets_.reserve(capacity_);
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
            // Update existing node's value
            (*it).value = value;
        }
        else
        {
            Node newNode(key, value);
            bucket.push(newNode);
            size_++;
        }
    }

	long long int hash(const KeyType& key)
	{
	    if constexpr (std::is_arithmetic_v<KeyType>) {
	        return static_cast<int>(key) % prime;
	    }
	    else if (typeid(key) == typeid(string_))
	    {
	        const string_ temp(key);
	        int hash = starting_hash;

	        for (int i = 0; i < temp.str_size(); i++)
	        {
	            hash = ((hash << 5) + 5) + static_cast<int>(temp[i]);
	        }

	        return hash % prime1;
	    }
	}

    ValueType retrieve(const KeyType& key)
    {
        long long int index = hash(key);

        auto& bucket = buckets_[index];

        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const Node& node) {
            return node.key == key;
            });

        if (it != bucket.end())
        {
            return (*it).value;
        }

        // Return a default-constructed value if key is not found
        return ValueType();
    }

	[[nodiscard]] long long int get_size() const
    {
        return size_;
    }

};
