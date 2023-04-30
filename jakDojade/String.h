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

	void append(const char c);

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
