#pragma once
#include <time.h>
#include <iostream>
using namespace std;

template <class T>
class Sorter
{
public:
	virtual void sort(T* data, size_t count) = 0;
	virtual unsigned long long getSortTime() const = 0;
};

template <class T>
class SortTester
{
public:
	SortTester(Sorter<T> **sorters, size_t count) {}
	virtual void getSummary(std::ostream & out) = 0;
};

template <class T>
void swapif(T& a, T& b)
{
	if (b < a)
	{
		T temp(a);
		a = b;
		b = temp;
	}
}

#include "MySorterInterface.h"
#include "MergeSorter.h"
#include "QuickSorter.h"
#include "InsertionSorter.h"
#include "Tester.h"
#include "HeapSorter.h"

