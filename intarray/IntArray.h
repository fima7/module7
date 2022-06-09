#pragma once

#include <string>
#include <stdexcept>

#include <iostream>

class OutOfRange : public std::out_of_range
{
public:
	OutOfRange(size_t index, size_t size)
		: std::out_of_range("out of range")
		, _msg("index " + std::to_string(index) + " is out of " + std::to_string(size))
	{}
public:
	const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;

};

class IntArray
{
public:
	IntArray();
	explicit IntArray(size_t size);
	IntArray(std::initializer_list<int> l);
	IntArray(const IntArray& other);
	virtual ~IntArray();
public:
	IntArray& operator=(const IntArray& other)
	{
		IntArray tmp(other);
		Swap(tmp);
		return *this;
	}

private:
	void Swap(IntArray& tmp)
	{
		std::swap(_size, tmp._size);
		std::swap(_data, tmp._data);
	}
public:
	friend std::ostream& operator<<(std::ostream& os, const IntArray& array);
	friend bool operator!=(const IntArray& lhs, const IntArray& rhs);


public:
	size_t GetSize() const noexcept;
	int& operator[] (size_t index);
	const int& operator[] (size_t index) const;
	void Resize(size_t size);
	int GetFront() const;
	int GetBack() const;
	void PushFront(int value);
	void PopFront();
	void PushBack(int value);
	void PopBack();
	void Insert(int value, size_t index);
	void Erase(size_t index);
	bool Find(int value, size_t& index) const noexcept;
	void Sort() noexcept;
	void RSort() noexcept;

private:
	size_t _size;
	int* _data;
};
