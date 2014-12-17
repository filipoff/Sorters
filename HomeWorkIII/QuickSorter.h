#pragma once




template <class T>
class QuickSorter : public MySorterInterface < T >
{
public:

	virtual void sort(T* data, size_t count)
	{

		if (!data || count <= 1)
			return;

		clock_t start, finish;
		start = clock();

		size_t endPositionOfSubArray = partition(data, count);
		sort(data, endPositionOfSubArray);
		sort(data + endPositionOfSubArray + 1, count - endPositionOfSubArray - 1);

		finish = clock();
		timeTaken = finish = start;


	}
	virtual unsigned long long getSortTime() const
	{
		return timeTaken;
	}

	virtual const char* getSorterName() const
	{
		return "Quick Sort";
	}
private:
	size_t partition(T* arr, size_t size)
	{
		if (size == 2)
		{
			swapif(arr[0], arr[1]);
			return 1;
		}
		T& pivot = choosePivot(arr, size);
		size_t leftBorder = 0;
		size_t rightBorder = size - 2;

		while (true)
		{
			// move left border to right until 
			// element thats bigger than the pivot is found
			while (arr[++leftBorder] < pivot)
				;
			// move right border to left until
			// element thats smaller than the pivot is found
			// or stop when the two borders are on the same element
			while (arr[--rightBorder] > pivot)
			{
				if (leftBorder == rightBorder)
					// all elements smaller than the pivot are on the left
					// and all the bigger are on the right of the pivot
					break;
			}

			if (leftBorder >= rightBorder)
				// borders are on the same element or they crossed
				// so element movement is completed
				break;

			// until all elements smaller than the pivot are on the left
			// and all the bigger are on the right of the pivot
			// swap bigger element than pivot with smaller element than pivot
			swap(arr[leftBorder], arr[rightBorder]);
		}

		// put pivot in the right position
		swap(arr[leftBorder], pivot);

		// return new end of the subarray to sort
		return leftBorder;

	}
	T& choosePivot(T* arr, size_t size)
	{
		size_t middle = size / 2;
		swapif(arr[0], arr[middle]);
		swapif(arr[0], arr[size - 1]);
		swapif(arr[middle], arr[size - 1]);
		swap(arr[middle], arr[size - 2]);
		return arr[size - 2];
	}

};