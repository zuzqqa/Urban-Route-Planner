#pragma once

#include "Vector.h"
#include "String.h"

constexpr long long prime = 201326611;
constexpr int starting_hash = 5381;

class HashMap_id
{
public:
    struct Node
    {
        int city_id;
        string_ city_name;
        Node* next{};

        Node() : city_id(0), city_name(nullptr), next(nullptr) {}
        Node(const int key, const string_& value) : city_id(key), city_name(value) {}
    };

    HashMap_id()
    {
        allocate_buckets();
    }

    static long long int hash(const int key)
    {
        return key % prime;
    }

    void insert(const int key, const string_& value) {
        const long long int h = hash(key);

        const auto new_node = new Node(key, value);

        if (buckets_[h] == nullptr) {
            buckets_[h] = new_node;
        }
        else {
            Node* current = buckets_[h];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }

        size_++;
    }

    [[nodiscard]] string_ retrieve(const int key) const
    {
        const long long int h = hash(key);

        Node* current = buckets_[h];

        while (current != nullptr)
        {
            if (current->city_id == key) return current->city_name;

            current = current->next;
        }

        return {};
    }

    [[nodiscard]] long long int get_size() const
    {
        return size_;
    }

    ~HashMap_id()
    {
        deallocate_buckets();
    }
private:
    static constexpr int initial_bucket_count = 10007;
    static constexpr int prime = 10007;

    Node** buckets_{};
    int size_ = 0;

    void allocate_buckets()
    {
        buckets_ = new Node * [initial_bucket_count]();
    }

    void deallocate_buckets() const
    {
        if (buckets_ != nullptr)
        {
            for (int i = 0; i < initial_bucket_count; i++)
            {
                Node* current = buckets_[i];
                while (current != nullptr)
                {
	                const Node* temp = current;
                    current = current->next;
                    delete temp;
                }
            }

            delete[] buckets_;
        }
    }
};



class HashMap_str
{
public:
    struct Node
    {
        string_ city_name;
        int city_id;
        Node* next;

        Node() : city_name(""), city_id(0), next(nullptr) {}  
        Node(const string_& value, const int key) : city_name(value), city_id(key), next(nullptr) {}
    };

    HashMap_str() {
        allocate_buckets();
    }

    static long long int hash(const string_& key)
    {
        long long int hash = starting_hash;

        for (int i = 0; i < key.str_size(); i++)
        {
            hash = ((hash << 5) + hash) + key[i];
        }
 
        return hash % initial_bucket_count;
    }

    void insert(const string_& key, const int value) {
        const long long int h = hash(key);

        const auto new_node = new Node(key, value);
        new_node->next = buckets_[h];
        buckets_[h] = new_node;

        size_++;
    }

    [[nodiscard]] int retrieve(const string_& key) const
    {
		const long long int h = hash(key);

		const Node* current = buckets_[h];

        while(current!=nullptr)
        {
            if (current->city_name == key) 
                return current->city_id;

            current = current->next;
        }

	    return 0;
    }

    [[nodiscard]] long long int get_size() const
    {
        return size_;
    }

    ~HashMap_str()
    {
        deallocate_buckets();
    }
private:
    static constexpr int initial_bucket_count = 10007;
    static constexpr int prime = 201326611;

    Node** buckets_{};
    long long int size_{};

    void allocate_buckets()
    {
        buckets_ = new Node *[initial_bucket_count]();
    }

    void deallocate_buckets() const
    {
        if (buckets_ != nullptr)
        {
            for (int i = 0; i < initial_bucket_count; i++)
            {
                Node* current = buckets_[i];
                while (current != nullptr)
                {
	                const Node* temp = current;
                    current = current->next;
                    delete temp;
                }
            }

            delete[] buckets_;
        }
    }
};
