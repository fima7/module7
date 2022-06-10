#include "IntArray.h"

#include <cassert>
#include <iostream>
#include <iomanip>

#define TEST(x) { x(); std::cerr << std::left << std::setw(30) << #x << " pass" << std::endl; } 


//
// Тесты для IntArray
//

static IntArray test_pass_parameters(IntArray a) 
{
	return a;
}

static void TestConstructors()
{

	{ // Инициялизация пустого массива
		IntArray a;
		assert(a.GetSize() == 0);
	}

	{ // Инициялизация пустого массива
		IntArray a{};
		assert(a.GetSize() == 0);
	}

	{ // Инициализация с параметром
		IntArray a(10);

		assert(a.GetSize() == 10);

		for (int i = 0; i < 10; ++i) {
			a[i] = i;
		}


		for (int i = 0; i < a.GetSize(); ++i) {
			assert(a[i] == i);
		}
	}
		
	{ // Унифицированная инициализация
		IntArray a{ 0, 1, 2, 3, 4, 5 };

		for (int i = 0; i < a.GetSize(); ++i) {
			assert(a[i] == i);
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b = a;
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i < b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b(a);
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i <b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{ // Инициализация копированием
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b{ a };
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i <b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray b = test_pass_parameters(a);
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i < b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{
		const IntArray a{ 0, 1, 2, 3, 4, 5 };
		const int b = a[5];
		assert(b == 5);
	}

}

static void TestAssignment()
{
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		IntArray b;

		b = a;

		assert(b.GetSize() == a.GetSize());

		for (size_t i = 0; i < b.GetSize(); ++i) {
			assert(b[i] == a[i]);
		}
	}

}

static void TestAccess()
{
	{
		IntArray a{0, 1, 2, 3, 4, 5 };
		int v = a[5];
		assert(v == 5);
	}
	{
		try {
			IntArray a{ 1, 2, 3, 4, 5 };
			std::cout << a[16] << std::endl;
			assert(false);
		} catch (OutOfRange&) {
			// std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		try {
			IntArray a(10000000000);
			assert(false);
		} catch (std::bad_alloc&) {
			// std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		assert(a.GetFront() == 1);
	}
	{
		IntArray a{ 1, 2, 3, 4, 5 };
		assert(a.GetBack() == 5);
	}

}

static void TestResize()
{
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		a.Resize(10);
		for (int i = 6; i < a.GetSize(); ++i) {
			a[i] = i;
		}

		assert(a == e);
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		IntArray e{ 0, 1, 2, 3, 4, 5 };
		
		a.Resize(6);

		assert(a == e);
	}

}

static void TestInsert()
{

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 8, 1, 2, 3, 4, 5 };

		a.Insert(8, 0);

		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 8, 2, 3, 4, 5 };

		a.Insert(8, 1);

		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 8, 3, 4, 5 };

		a.Insert(8, 2);

		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 8, 4, 5 };

		a.Insert(8, 3);

		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 8, 5 };

		a.Insert(8, 4);

		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5, 8 };

		a.Insert(8, 5);

		assert(a == e);
	}
	{
		// Два блока try не нужны, использую только чтобы попрактиковаться

		std::string emsg("index 6 is out of 6");
		try {
			try {
				IntArray a{ 0, 1, 2, 3, 4, 5 };
				a.Insert(8, 6);
				assert(false);
			} catch (std::out_of_range& e) {
				std::string msg(e.what());
				assert(msg == emsg);
				throw;
			}
			assert(false);
		} catch (std::exception& e) {
			std::string msg(e.what());
			assert(msg == emsg);
		}
	}

}

static void TestPushFront()
{
	{
		IntArray a;
		IntArray e{ 5 };
		a.PushFront(5);
		assert(a.GetFront() == 5);
		assert(a == e);
	}
	{

		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ -2, -1, 0, 1, 2, 3, 4, 5 };

		a.PushFront(-1);
		assert(a.GetFront() == -1);

		a.PushFront(-2);
		assert(a.GetFront() == -2);
		
		assert(a == e);
	}

}

static void TestPushBack()
{

	{
		IntArray a;
		IntArray e{ 5 };

		a.PushBack(5);
		assert(a.GetBack() == 5);
		assert(a == e);
	}
	{

		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5, 6, 7 };

		a.PushBack(6);
		assert(a.GetBack() == 6);

		a.PushBack(7);
		assert(a.GetBack() == 7);
		
		assert(a == e);
	}

}

static void TestErase()
{

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 1, 2, 3, 4, 5 };
		a.Erase(0);
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 2, 3, 4, 5 };
		a.Erase(1);
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 3, 4, 5 };
		a.Erase(2);
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 4, 5 };
		a.Erase(3);
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 5 };
		a.Erase(4);
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4 };
		a.Erase(5);
		assert(a == e);
	}

}

static void TestSort()
{
	{
		IntArray a{ 5, 4, 3, 2, 1, 0 };
		IntArray e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		assert(a == e);
	}

	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		assert(a == e);
	}

	{
		IntArray a{ 5 };
		IntArray e{ 5 };
		a.Sort();
		assert(a == e);
	}
	{
		IntArray a{ 0, 1, 2, 3, 4, 5 };
		IntArray e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		assert(a == e);
	}

	{
		IntArray a{ 5, 4, 3, 2, 1, 0 };
		IntArray e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		assert(a == e);
	}

	{
		IntArray a{ 5 };
		IntArray e{ 5 };
		a.RSort();
		assert(a == e);
	}

}

static void TestAllocation() 
{

#if 0 // зависит от машины	
	{
		try {
			IntArray a(100'000'000'000);
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		IntArray a;
		try {
			a.Resize(100'000'000'000);
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		IntArray a;
		try {
			IntArray a(4'000'000'000);
			for (size_t i = 0; i < 1'000'000; ++i) {
				a.PushFront(i);
			}
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		IntArray a;
		try {
			IntArray a(4'000'000'000);
			for (size_t i = 0; i < 1'000'000; ++i) {
				a.PushBack(i);
			}
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
#endif

}

int main()
{

	TEST(TestConstructors);
	TEST(TestAssignment);
	TEST(TestAccess);
	TEST(TestResize);
	TEST(TestInsert);
	TEST(TestPushFront);
	TEST(TestPushBack);
	TEST(TestErase);
	TEST(TestSort);
	TEST(TestAllocation);

	return 0;

} 