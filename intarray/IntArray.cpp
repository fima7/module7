#include "IntArray.h"	

#include <cstring>

//
// �������� � ��������
//

IntArray::IntArray()
		: _size{}
		, _data{}
{}
 
IntArray::IntArray(size_t size)
		: _size(size)
		, _data(new int[_size])
{}

IntArray::IntArray(std::initializer_list<int> l)
	: _size(l.size())
	, _data(new int[_size])
{
	size_t i = 0;
	for (auto item : l) {
		if (i < _size) {
			_data[i++] = item;
		}
		else {
			break;
		}
	}
}

IntArray::IntArray(const IntArray& other)
	: _size(other._size)
	, _data(new int[_size])
{
	memcpy(_data, other._data, _size * sizeof(int));
}

IntArray::~IntArray()
{
	delete[] _data;
}

IntArray& IntArray::operator=(const IntArray& other)
{
	IntArray tmp(other);
	Swap(tmp);
	return *this;
}

//
// ������ � ���������  
// 

// ��������� ������� �������
size_t IntArray::GetSize() const noexcept
{
	return _size;
}

// ������ � �������� �� �������
int& IntArray::operator[] (size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}
	return _data[index];

}

// ������ � �������� �� �������
const int& IntArray::operator[] (size_t index) const
{
	return const_cast<IntArray*>(this)->operator[](index);
}

// �������� ������ ������� ������� � �������� 0
int IntArray::GetFront() const
{
	if (_size == 0) {
		throw OutOfRange(0, _size);
	}
	return _data[0];
}

// �������� ������� � �������� size - 1
int IntArray::GetBack() const
{
	if (_size == 0) {
		throw OutOfRange(0, _size);
	}
	return _data[_size - 1];
}

// ������ � ���������� �������� �� �������
bool IntArray::Find(int value, size_t& index) const noexcept
{
	for (size_t i = 0; i < _size; ++i) {
		if (_data[i] == value) {
			index = i;
			return true;
		}
	}
	return false;
}

//
// ��������� �������
//

// ������ ������ �������
// � ������� ������� � ����������� ���� ������
// � ������� ������� � ����������� ���������� ������
void IntArray::Resize(size_t size)
{
	IntArray tmp(size);

	size_t nbytes = (size < _size ? size : _size) * sizeof(int);
	memcpy(tmp._data, _data, nbytes);

	Swap(tmp);
}

// �������� ������� � ������ �������
// ���������� ����������� ���� ���������
void IntArray::PushFront(int value)
{
	IntArray tmp(_size + 1);

	size_t nbytes = _size * sizeof(int);

	tmp._data[0] = value;

	memcpy(tmp._data + 1, _data, nbytes);

	Swap(tmp);
}

// ������� ������� �� ������ �������
// ���������� ����������� ���� ���������
void IntArray::PopFront()
{
	Erase(0);
}

// �������� ������� � ����� ������� 
// ���������� ����������� ���� ���������
void IntArray::PushBack(int value)
{
	if (_size == 0) {
		PushFront(value);
	} else {
		Insert(value, _size - 1);
	}
}

// ������� ������� � ����� �������  
// ���������� ����������� ���� ���������
void IntArray::PopBack()
{
	Erase(_size - 1);
}

// �������� ������� � ������ ����� �������� �� ��������� �������
// ���������� ����������� ���� ���������
void IntArray::Insert(int value, size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}

	IntArray tmp(_size + 1);

	tmp._data[index + 1] = value;

	memcpy(tmp._data, _data, (index + 1) * sizeof(int));

	if (index < _size - 1) {
		memcpy(tmp._data + index + 2, _data + index + 1, (_size - index - 1) * sizeof(int));
	}

	Swap(tmp);
}

// ������� ������� �� ��������� �������
// ���������� ����������� ���� ���������
void IntArray::Erase(size_t index)
{
	if (index >= _size) {
		throw OutOfRange(index, _size);
	}

	IntArray tmp(_size - 1);

	if (index > 0) {
		memcpy(tmp._data, _data, (index + 1 - 1) * sizeof(int));
	}
	if (index < _size - 1) {
		memcpy(tmp._data + index, _data + index + 1, (tmp._size - index) * sizeof(int));
	}

	Swap(tmp);
}

// ���������� � ������� �����������
void IntArray::Sort() noexcept
{
	for (size_t i = 0; i < _size - 1; ++i) {
		for (size_t j = 0; j < _size - i - 1; ++j) {
			if (_data[j] > _data[j + 1]) {
				std::swap(_data[j], _data[j + 1]);
			}
		}
	}

}

// ���������� � ������� ��������
void IntArray::RSort() noexcept
{
	for (size_t i = 0; i < _size - 1; ++i) {
		for (size_t j = 0; j < _size - 1 - i; ++j) {
			if (_data[j] < _data[j + 1]) {
				std::swap(_data[j], _data[j + 1]);
			}
		}
	}

}

// 
// ��������������� ������ 
//

// ����� ����������� �������
std::ostream& operator<<(std::ostream& os, const IntArray& array)
{
	for (size_t i = 0; i < array._size; ++i) {
		os << array._data[i] << " ";
	}

	return os;
}

// �������� �� ��������� ��������
bool operator==(const IntArray& lhs, const IntArray& rhs)
{
	if (lhs._size != rhs._size) {
		return false;
	}

	for (size_t i = 0; i < lhs._size; ++i) {
		if (lhs._data[i] != rhs._data[i]) {
			return false;
		}
	}

	return true;
}

// �������� �� ����������� ��������
bool operator!=(const IntArray& lhs, const IntArray& rhs)
{
	return !(lhs == rhs);
}

//
// �������� ������ 
//

// ����� ����������� ����� ���������
void IntArray::Swap(IntArray& tmp)
{
	std::swap(_size, tmp._size);
	std::swap(_data, tmp._data);
}

