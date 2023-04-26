#pragma once
#include <iostream>
#include <cstring>
#include <cctype>

#define CRT_SECURE_NO_WARNINGS

class string_ {
	char* data_;
	int size_;
public:
	string_();

	string_(const char* str);

	string_& operator=(const string_& other);

	string_& operator+(const string_& other) const;

	void append(char c);

	void flip();

	char& operator[](const int index) const;

	bool operator==(const string_& other) const;

	bool operator!=(const string_& other) const;

	[[nodiscard]] char* get_str() const;

	[[nodiscard]] int str_size() const;

	[[nodiscard]] string_ substr(const int buffer, const int length) const;

	void str_delete();

	~string_();
};

inline string_::string_()
{
	data_ = new char[1];
	size_ = 0;

	data_[0] = '\0';
}

inline string_::string_(const char* str)
{
	data_ = nullptr;
	size_ = 0;

	if (str != nullptr) {
		int length = strlen(str);

		auto str_data = new char[length + 1];

		for (size_t i = 0, j = 0; i < length; i++) {
			if (str[i] != '\n') {
				str_data[j] = str[i];

				j++;
				size_++;
			}
		}

		str_data[size_] = '\0';

		data_ = str_data;
	}
	else {
		data_ = new char[1];
		data_[0] = '\0';
	}
}

inline string_& string_::operator=(const string_& other)
{
	if (this != &other) {

		if (data_ != nullptr) {
			data_ = nullptr;
		}

		size_ = other.size_;
		data_ = new char[size_ + 1];

		memcpy_s(data_, size_ + 1, other.data_, size_ + 1);
	}
	return *this;
}

inline void string_::append(const char c) {
	auto str_data = new char[size_ + 2];

	if(data_ != nullptr)
	{
		for(int i = 0; i < size_; i++)
		{
			str_data[i] = data_[i];
		}
		delete[] data_;
	}

	data_ = str_data;
	data_[size_] = c;
	data_[size_ + 1] = '\0';

	size_++;
}

inline void string_::flip() {
	auto str_data = new char[size_];

	if (data_ != nullptr)
	{
		int j = 0;

		for (int i = size_ - 1; i >= 0; i--)
		{
			str_data[j++] = data_[i];
		}
		delete[] data_;
	}

	data_ = str_data;
}


inline char& string_::operator[](const int index) const
{
	return data_[index];
}

inline bool string_::operator==(const string_& other) const
{
	return (size_ == other.size_) && (strcmp(data_, other.data_) == 0);
}

inline bool string_::operator!=(const string_& other) const
{
	return !(*this == other);
}

inline char* string_::get_str() const
{
	return data_;
}

inline int string_::str_size() const
{
	return size_;
}

inline string_ string_::substr(const int buffer, const int length) const
{
	auto newString = new char[length + 1];

	memcpy(newString, &data_[buffer], length);

	newString[length] = '\0';

	return {newString};
}

inline void string_::str_delete()
{
	if (data_ != nullptr) {
		delete[] data_;

		size_ = 0;
		data_ = new char[1];
		data_[0] = '\0';
	}
}

inline string_::~string_()
{
	if (data_ != nullptr) {
		data_ = nullptr;
	}
}
