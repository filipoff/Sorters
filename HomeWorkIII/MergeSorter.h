#pragma once

template <class T>
class MergeSorter : public MySorterInterface < T >
{
public:

	virtual void sort(T* data, size_t count)
	{

		if (!data || count == 0)
			return;


		clock_t start, finish;
		start = clock();

		T* buffer = new T[count];

		step(data, count, buffer);

		finish = clock();
		delete[] buffer;
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

		// break the array into arrays with one element

		if (size <= 1)
			return;

		size_t halfSize = size / 2;

		// break the left side of the array
		step(arr, halfSize, buffer);

		// break the right side of the array
		step(arr + halfSize, size - halfSize, buffer + halfSize);

		// merge two nearby arrays
		merge(arr, halfSize, arr + halfSize, size - halfSize, buffer);

		// insert result of the merge in the array
		for (size_t i = 0; i < size; i++)
			arr[i] = buffer[i];
	}
	void merge(T* first, size_t sizeOfFirst, T* second, size_t sizeOfSecond, T* result)
	{
		size_t resultIndex = 0;
		size_t firstIndex = 0;
		size_t secondIndex = 0;

		// get element from first and second array, compare them
		// insert the smaller element to the result array
		while (firstIndex < sizeOfFirst  && secondIndex < sizeOfSecond)
			result[resultIndex++] = (first[firstIndex] < second[secondIndex] ? first[firstIndex++] : second[secondIndex++]);

		// insert the rest of the elements in the result array

		while (firstIndex < sizeOfFirst)
			result[resultIndex++] = first[firstIndex++];

		while (secondIndex < sizeOfSecond)
			result[resultIndex++] = second[secondIndex++];
	}
};