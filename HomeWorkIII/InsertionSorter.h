#pragma once

template <class T>
class InsertionSorter : public MySorterInterface <T>
{
public:
	virtual void sort(T* data, size_t count)
	{

		if (!data || count == 0)
			return;
		clock_t start, finish;
		start = clock();
		for (size_t i = 1; i < count; i++)
		{
			T hand = data[i];
			int j = i;

			while (j > 0 && data[j - 1] > hand)
			{
				data[j] = data[j - 1];
				j--;
			}
			data[j] = hand;
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
		return "Insertion Sort";
	}
private:
	unsigned long long timeTaken;
};