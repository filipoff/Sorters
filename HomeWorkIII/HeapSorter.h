#pragma once


template <class T>
class HeapSorter : public MySorterInterface < T >
{
public:

	virtual void sort(T* data, size_t count)
	{

		if (!data || count == 0)
			return;

		clock_t start, finish;
		start = clock();

		size_t index = count / 2;

		while (index--)
		{
			sift(data, index, count);
		}

		index = count;

		while (--index)
		{
			swap(data[0], data[index]);
			sift(data, 0, index);
		}

		finish = clock();

		timeTaken = finish - start;


	}
	virtual unsigned long long getSortTime() const
	{
		return timeTaken;
	}
	virtual const char* getSorterName() const
	{
		return "HeapSort";
	}
private:

	void sift(T* arr, size_t position, size_t size)
	{
		T toPosition(arr[position]);

		size_t currentNodeIndex = position;
		size_t currentChildNodeIndex = position * 2 + 1;

		while (currentChildNodeIndex < size)
		{
			if (currentChildNodeIndex < size - 1 && arr[currentChildNodeIndex] < arr[currentChildNodeIndex + 1])
			{
				currentChildNodeIndex++;
			}

			if (toPosition > arr[currentChildNodeIndex])
				break;

			arr[currentNodeIndex] = arr[currentChildNodeIndex];

			currentNodeIndex = currentChildNodeIndex;
			currentChildNodeIndex = currentChildNodeIndex * 2 + 1;

		}
		arr[currentNodeIndex] = toPosition;
	}
};