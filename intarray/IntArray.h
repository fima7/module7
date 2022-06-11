#pragma once

#include <string>
#include <stdexcept>
#include <initializer_list>
#include <string>
#include <ostream>

// Объявление IntArray

class IntArray
{

public: // создание, удаление
	IntArray();
	explicit IntArray(size_t size);
	IntArray(std::initializer_list<int> l);
	IntArray(const IntArray& other);
	IntArray& operator=(const IntArray& other);
	virtual ~IntArray();
public: // доступ к элементам
	int& operator[] (size_t index);
	const int& operator[] (size_t index) const;
	size_t GetSize() const noexcept;
	int GetFront() const;
	int GetBack() const;
	bool Find(int value, size_t& index) const noexcept;
public: // изменение 
	void Resize(size_t size);
	void PushFront(int value);
	void PopFront();
	void PushBack(int value);
	void PopBack();
	void Insert(int value, size_t index);
	void Erase(size_t index);
	void Sort() noexcept;
	void RSort() noexcept;
public: // вспопогательное
	friend std::ostream& operator<<(std::ostream& os, const IntArray& array);
	friend bool operator==(const IntArray& lhs, const IntArray& rhs);
	friend bool operator!=(const IntArray& lhs, const IntArray& rhs);
private: // обмен содержимым
	void Swap(IntArray& tmp);
private:
	size_t _size;	// количество элементов
	int* _data;		// элементы
};

// исключение, индекс больше чем количество элементов
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

