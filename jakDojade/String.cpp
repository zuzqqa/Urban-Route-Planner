#include "String.h"

string_::string_()
{
	data_ = new char[1];
	size_ = 0;

	data_[0] = '\0';
}

string_::string_(const char* str)
{
	data_ = nullptr;
	size_ = 0;

	if (str != nullptr) {
		const size_t length = strlen(str);

		const auto str_data = new char[length + 1];

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

string_& string_::operator=(const string_& other)
{
	if (this != &other) {
		delete[] data_;

		size_ = other.size_;
		data_ = new char[size_ + 1];

		memcpy_s(data_, size_ + 1, other.data_, size_ + 1);
	}
	return *this;
}

void string_::append(const char c) {
	const auto str_data = new char[size_ + 2];

	if (data_ != nullptr)
	{
		for (int i = 0; i < size_; i++)
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

void string_::flip() {
	const auto str_data = new char[size_];

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

char& string_::operator[](const int index) const
{
	return data_[index];
}

bool string_::operator==(const string_& other) const
{
	return (size_ == other.size_) && (strcmp(data_, other.data_) == 0);
}

bool string_::operator!=(const string_& other) const
{
	return !(*this == other);
}

char* string_::get_str() const
{
	return data_;
}

int string_::str_size() const
{
	return size_;
}

string_ string_::substr(const int buffer, const int length) const
{
	const auto new_string = new char[length + 1];

	memcpy(new_string, &data_[buffer], length);
	new_string[length] = '\0';

	string_ result(new_string);

	delete[] new_string;

	return result;
}

void string_::str_delete()
{
	if (data_ != nullptr) {
		delete[] data_;

		size_ = 0;
		data_ = new char[1];
		data_[0] = '\0';
	}
}

string_::~string_()
{
	if (data_ != nullptr) {
		data_ = nullptr;
	}
}
