#pragma once
#include <cstring>
#include <cctype>

class String
{
	char* arr;
	int size;
public:
	String()
		: size(0), arr(new char[1]) {
		arr[0] = '\0';
	};

	String(const char* str) {
		arr = nullptr;
		size = 0;

		if (str != nullptr) {
			int length = strlen(str);

			char* strData = new char[length + 1];

			for (size_t i = 0, j = 0; i < length; i++) {
				if (str[i] != '\n') {
					strData[j] = str[i];

					j++;
					size++;
				}
			}

			strData[size] = '\0';

			arr = strData;
		}
		else { //default wartosci
			arr = new char[1];
			arr[0] = '\0';
		}
	};

	String substr(int buffer, int length) {
		char* newString = new char[length + 1];

		memcpy(newString, &arr[buffer], length);

		newString[length] = '\0';

		return String(newString);
	};

	String& operator=(const String& other) {
		if (this != &other) {

			if (arr != nullptr) {
				arr = nullptr;
			}

			size = other.size;
			arr = new char[size + 1];

			memcpy_s(arr, size + 1, other.arr, size + 1);
		}
		return *this;
	};

	String& operator+(const String& other) const {
		String result;

		result.size = size + other.size;
		result.arr = new char[result.size + 1];

		strcpy(result.arr, arr);
		strcat(result.arr, other.arr);

		return result;
	};

	char& operator[](int index) const {
		return arr[index];
	};

	bool operator==(const String& other) const {
		return (size == other.size) && (strcmp(arr, other.arr) == 0);
	};

	bool operator!=(const String& other) const {
		return !(*this == other);
	};

	void Sdelete() {
		if (arr != nullptr) {
			delete[] arr;

			size = 0;
			arr = new char[1];
			arr[0] = '\0';
		}
	};
};

