#pragma once

#include <algorithm>
template <class T>
class MergeSorter : public MySorterInterface < T >
{
public:

	virtual void sort(T* data, size_t count)
	{

		if (!data || count == 0)
			return;

		T* buffer = new T[count];

		step(data, count, buffer);

		delete[] buffer;


		clock_t start, finish;
		start = clock();

		std::sort(data, data + count);

		finish = clock();
		timeTaken = finish - start;


	}
	virtual unsigned long long getSortTime() const
	{
		return timeTaken;
	}
	virtual const char* getSorterName() const
	{
		return "Merge Sort";
	}

private:
	void step(T* arr, size_t size, T* buffer)
	{
		if (size <= 1)
			return;
		size_t halfSize = size / 2;
		step(arr, halfSize, buffer);
		step(arr + halfSize, size - halfSize, buffer - halfSize);


	}
};