#include "IntArray.h"

#include <iostream>
#include <cassert>
#include <iomanip>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <random>

#define TEST(x) { assert(x()); std::cerr << std::left << std::setw(30) << #x << " pass" << std::endl; } 

static IntArray test_pass_parameters(IntArray a) 
{
	return a;
}

bool TestConstructors()
{

	{ // Инициялизация пустого массива
		IntArray a;
		if (a.GetSize() != 0) {
			return false;
		}
	}

	{ // Инициялизация пустого массива
		IntArray a{};
		if (a.GetSize() != 0) {
			return false;
		}
	}

	{ // Инициализация с параметром
		IntArray a(10);

		if (a.GetSize() != 10) {
			return false;
		}

		for (int i = 0; i < 10; ++i) {
			a[i] = i;
		}


		for (int i = 0; i < a.GetSize(); ++i) {
			if (a[i] != i) {
				return false;
			}
		}

	}
		
	{ // Унифицированная инициализация
		IntArray a{ 0, 1, 2, 3, 4, 5 };

		for (int i = 0; i < a.GetSize(); ++i) {
			if (a[i] != i) {
				return false;
			}
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b = a;
		if (a.GetSize() != b.GetSize()) {
			return false;
		}

		for (int i = 0; i < b.GetSize(); ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b(a);
		if (a.GetSize() != b.GetSize()) {
			return false;
		}

		for (int i = 0; i <b.GetSize(); ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b{ a };
		if (a.GetSize() != b.GetSize()) {
			return false;
		}

		for (int i = 0; i <b.GetSize(); ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b = test_pass_parameters(a);
		if (a.GetSize() != b.GetSize()) {
			return false;
		}
		for (int i = 0; i < b.GetSize(); ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}

	{
		const IntArray a{ 0, 1, 2, 3, 4, 5 };
		const int b = a[5];
		if (b != 5) {
			return false;
		}
	}

	return true;
}

bool TestAssignment()
{
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		IntArray b;

		b = a;

		if (b.GetSize() != a.GetSize()) {
			return false;
		}

		for (size_t i = 0; i < b.GetSize(); ++i) {
			if (b[i] != a[i]) {
				return false;
			}
		}
	}

	return true;

}

bool TestAccess()
{
	{
		IntArray a{0, 1, 2, 3, 4, 5 };
		int v = a[5];
		if (v != 5) {
			return false;
		}
	}
	{
		try {
			IntArray a{ 1, 2, 3, 4, 5 };
			std::cout << a[16] << std::endl;
			return false;
		} catch (OutOfRange& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		try {
			IntArray a(10000000000);
			return false;
		} catch (std::bad_alloc& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		if (a.GetFront() != 1) {
			return false;
		}
	}
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		if (a.GetBack() != 5) {
			return false;
		}
	}

	return true;
}

bool TestResize()
{
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };

		a.Resize(10);

		if (a.GetSize() != 10) {
			return false;
		}

		for (int i = 0; i <= 5; ++i) {
			if (a[i] != i) {
				return false;
			}
		}

		for (int i = 6; i < a.GetSize(); ++i) {
			a[i] = i;
		}

		for (size_t i = 6; i < a.GetSize(); ++i) {
			if (a[i] != i) {
				return false;
			}
		}
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		
		a.Resize(6);

		if (a.GetSize() != 6) {
			return false;
		}

		for (size_t i = 0; i < a.GetSize(); ++i) {
			if (a[i] != i) {
				return false;
			}
		}
	}

	return true;
}

static bool set_out_of_size()
{
	return true;
}

bool TestInsert()
{

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 8, 1, 2, 3, 4, 5 };

		a.Insert(8, 0);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 8, 2, 3, 4, 5 };

		a.Insert(8, 1);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 8, 3, 4, 5 };

		a.Insert(8, 2);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 8, 4, 5 };

		a.Insert(8, 3);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 8, 5 };

		a.Insert(8, 4);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5, 8 };

		a.Insert(8, 5);

		assert(a.GetSize() == e.GetSize());
		for (size_t i = 0; i < e.GetSize(); ++i) {
			assert(a[i] == e[i]);
		}
	}
	{
		// Два блока try не нужны, использую только чтобы попрактиковаться

		std::string emsg("index 6 is out of 6");
		try {
			try {
				IntArray a{ 0, 1, 2, 3, 4, 5 };
				a.Insert(8, 6);
				return false;
			} catch (std::out_of_range& e) {
				std::string msg(e.what());
				if (msg != emsg) {
					std::cerr << "\"" << msg << "\""
						<< " differs "
						<< "\"" << emsg << "\""
						<< std::endl;
				}

				throw; // можно так не делать, просто решил потренироваться 
				// throw e; // так будет скоприровано out_of_ragne, и перехваченное e.what() даст "out of range"
			}
			return false;
		} catch (std::exception& e) {
			std::string msg(e.what());
			if (msg != emsg) {
				std::cerr << "\"" << msg << "\""
					<< " differs "
					<< "\"" << emsg << "\""
					<< std::endl;
			}
		}
	}

	return true;
}

bool TestPushFront()
{
	
	{

		IntArray a{ 0, 1, 2, 3, 4, 5 };

		size_t prev_size = a.GetSize();

		a.PushFront(-1);
		
		if (a.GetSize() != (prev_size + 1)) {
			return false;
		}

		if (a.GetFront() != -1) {
			return false;
		}

		prev_size = a.GetSize();

		a.PushFront(-2);
		
		if (a.GetSize() != (prev_size + 1)) {
			return false;
		}

		if (a.GetFront() != -2) {
			return false;
		}

		if (a.GetSize() != 8) {
			return false;
		}

		for (size_t i = 0; i < a.GetSize(); ++i) {
			if (a[i] != i - 2) {
				return false;
			}
		}

	}

	return true;
}

bool TestErase()
{

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 1, 2, 3, 4, 5 };
		a.Erase(0);
		if (a != e) {
			return false;
		}
		// std::cout << a << std::endl;
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 2, 3, 4, 5 };
		a.Erase(1);
		if (a != e) {
			return false;
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 3, 4, 5 };
		a.Erase(2);
		if (a != e) {
			return false;
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 4, 5 };
		a.Erase(3);
		if (a != e) {
			return false;
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 5 };
		a.Erase(4);
		if (a != e) {
			return false;
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4 };
		a.Erase(5);
		if (a != e) {
			return false;
		}
	}

	return true;
}

bool TestSort()
{
	{
		IntArray a{ 5, 4, 3, 2, 1, 0 };
		IntArray e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		if (a != e) {
			return false;
		}
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		if (a != e) {
			return false;
		}
	}

	{
		IntArray a{ 5 };
		IntArray e{ 5 };
		a.Sort();
		if (a != e) {
			return false;
		}
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		if (a != e) {
			return false;
		}
	}

	{
		IntArray a{ 5, 4, 3, 2, 1, 0 };
		IntArray e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		if (a != e) {
			return false;
		}
	}

	{
		IntArray a{ 5 };
		IntArray e{ 5 };
		a.RSort();
		if (a != e) {
			return false;
		}
	}

	/*
	{
		IntArray a(256);
		srand(time(NULL));
		for (size_t i = 0; i < 256; ++i) {
			a[i] = std::rand() % 255;
		}

		std::cout << a << std::endl;

		a.RSort();

		std::cout << a << std::endl;

	}
	*/

	return true;
}

int main()
{
	/*
	try {
		throw new int;
	}
	catch (const int* i) {
		std::cerr << "Caught" << std::endl;
	}

	return 0;
	*/


	TEST(TestConstructors);
	TEST(TestAssignment);
	TEST(TestAccess);
	TEST(TestResize);
	TEST(TestInsert);
	TEST(TestPushFront);
	TEST(TestErase);
	TEST(TestSort);


} 