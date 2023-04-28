#pragma once

#include "Vector.h"
#include "String.h"

constexpr long long prime = 402653189;
constexpr long long prime1 = 201326611;
constexpr int starting_hash = 5381;
constexpr int buckets_size = 100007;

class HashMap_id
{
public:
    // Node structure to hold key-value pairs
    struct Node
    {
        int city_id;
        string_ city_name;
        Node() : city_id(0), city_name("") {}  // Default constructor
        Node(int key, string_& value) : city_id(key), city_name(value) {}
    };

    HashMap_id() {
        buckets_.reserve(buckets_size);
    }

    static long long int hash(const int key)
    {
    	return key % prime;
    }

    void insert(const int key, string_& value) {
	    const int h = hash(key);

       /* cout << "kLUCZ: " << key;
        cout << " miasto podane: " << value.get_str();*/

        buckets_[h] = { key, value };

        // prawidlowo przypisuje
        // cout <<"Wartosc przypisana: " << buckets_[h].city_name.get_str();

        size_++;
    }

    // Retrieve the value associated with a given key
    string_ retrieve(const int key) const
    {
	    const int h = hash(key);
        return buckets_[h].city_name;
    }

    [[nodiscard]] long long int get_size() const
    {
        return size_;
    }

private:
    Vector<Node> buckets_;  // Vector of linked lists to store the nodes
    int size_ = 0;                              // Current size of the hash map
};


class HashMap_str
{
public:

    // Node structure to hold key-value pairs
    struct Node
    {
        string_ city_name;
        int city_id;
        Node() : city_name(""), city_id(0) {}  
        Node(string_& value, int key) : city_name(value), city_id(key) {}
    };

    HashMap_str() {
        buckets_.reserve(buckets_size);
    }

	long long int hash(string_ key)
    {
        long long int hash = starting_hash;

        for (int i = 0; i < key.str_size(); i++)
        {
            hash = ((hash << 5) + hash) + key[i];
        }
 
        return hash % buckets_size;
    }

    void insert(string_& key, const int value) {
        const int h = hash(key);

        buckets_[h] = { key, value };

        size_++;
    }

    // Retrieve the value associated with a given key
    [[nodiscard]] int retrieve(string_ key)
    {
		long long int h = hash(key);
	    return buckets_[h].city_id;
    }

    [[nodiscard]] long long int get_size() const
    {
        return size_;
    }

private:
    Vector<Node> buckets_;  // Vector of linked lists to store the nodes
    int size_ = 0;                              // Current size of the hash map
};
