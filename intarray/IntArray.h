#pragma once

#include <string>
#include <stdexcept>

class IntArray
{
public:
	IntArray();
	explicit IntArray(size_t size);
	IntArray(std::initializer_list<int> l);
	IntArray(const IntArray& other);
	virtual ~IntArray();
public:
	IntArray& operator=(const IntArray& other);
	int& operator[] (size_t index);
	const int& operator[] (size_t index) const;
public:
	friend std::ostream& operator<<(std::ostream& os, const IntArray& array);
	friend bool operator!=(const IntArray& lhs, const IntArray& rhs);
public:
	size_t GetSize() const noexcept;
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
	void Swap(IntArray& tmp);
private:
	size_t _size;
	int* _data;
};

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
