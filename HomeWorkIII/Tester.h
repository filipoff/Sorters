#pragma once

#include "Sorter.h"


const size_t TEST_ARRAY_SIZE = 100000;
const size_t NUMBER_OF_TEST_ARRAYS = 3;
const char* TEST_NAMES[] = { "Random array", "Reversed array", "Constant element array" };


struct SorterInfo
{
	SorterInfo() : sorterName(NULL), testArraysSortTimes(NULL), sortingStatuses(NULL), testNames(NULL) {}
	~SorterInfo()
	{
		delete[] sorterName;
		delete[] sortingStatuses;
		delete[] testArraysSortTimes;
		for (size_t i = 0; i < NUMBER_OF_TEST_ARRAYS; i++)
		{
			delete[] testNames[i];
		}
		delete testNames;

	}
	char* sorterName;
	char** testNames;
	unsigned long long* testArraysSortTimes;
	bool* sortingStatuses;


};

template <class T>
class Tester : public SortTester < T >
{

public:

	Tester(Sorter <T> **sorters, size_t count) : SortTester <T>(sorters, count)
	{
		this->sorters = sorters;
		numberOfSorters = count;

		initInfoKeeper();

		runTests(sorters);
	}

	~Tester()
	{
		delete[] infoKeeper;
		for (size_t i = 0; i < numberOfSorters; i++)
		{
			delete[] sorters[i];
		}
		delete sorters;
	}


	virtual void getSummary(std::ostream & out)
	{

		out << "Testing sorters on arrays with size : " << TEST_ARRAY_SIZE << endl;
		for (size_t i = 0; i < numberOfSorters; i++)
		{
			out << "Sorter name : " << infoKeeper[i].sorterName << endl;

			for (size_t j = 0; j < NUMBER_OF_TEST_ARRAYS; j++)
			{
				out << "Status on " << infoKeeper[i].testNames[j] << " test: ";
				if (infoKeeper[i].sortingStatuses[j])
					out << "Passed" << endl;

				else
					out << "Failed " << endl;
				out << "Time taken: " << infoKeeper[i].testArraysSortTimes[j] << " ms" << endl;
			}
			out << endl;
		}

	}

private:
	Sorter <T>** sorters;
	SorterInfo* infoKeeper;
	size_t numberOfSorters;

	T* generateRandArray()
	{
		T* randArray = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			randArray[i] = rand() % 100000;
		}
		return randArray;
	}

	T* generateReversedArray()
	{
		T* reversedArray = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			reversedArray[i] = TEST_ARRAY_SIZE - i;
		}
		return reversedArray;
	}

	T* generateConstantElementArray()
	{
		T* constantArray = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			constantArray[i] = 1;
		}
		return constantArray;
	}

	void initInfoKeeper()
	{
		infoKeeper = new SorterInfo[numberOfSorters];
	}

	bool testSorterOnRandArray(Sorter <T> *sorter, T* randArray)
	{
		T* randArrayCopy = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			randArrayCopy[i] = randArray[i];
		}


		sorter->sort(randArrayCopy, TEST_ARRAY_SIZE);


		if (isSorted(randArrayCopy, TEST_ARRAY_SIZE))
		{
			delete[] randArrayCopy;
			return true;
		}
		else
		{
			delete[] randArrayCopy;
			return false;
		}
	}

	bool testSorterOnReversedArray(Sorter <T> *sorter, T* reversedArray)
	{
		T* reversedArrayCopy = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			reversedArrayCopy[i] = reversedArray[i];
		}


		sorter->sort(reversedArrayCopy, TEST_ARRAY_SIZE);


		if (isSorted(reversedArrayCopy, TEST_ARRAY_SIZE))
		{
			delete[] reversedArrayCopy;
			return true;
		}
		else
		{
			delete[] reversedArrayCopy;
			return false;
		}
	}

	bool testSorterOnConstantElementArray(Sorter <T> *sorter, T* constantElementArray)
	{
		T* constantElementArrayCopy = new T[TEST_ARRAY_SIZE];

		for (size_t i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			constantElementArrayCopy[i] = constantElementArray[i];
		}


		sorter->sort(constantElementArrayCopy, TEST_ARRAY_SIZE);


		if (isSorted(constantElementArrayCopy, TEST_ARRAY_SIZE))
		{
			delete[] constantElementArrayCopy;
			return true;
		}
		else
		{
			delete[] constantElementArrayCopy;
			return false;
		}
	}

	bool isSorted(T* arr, size_t size)
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i + 1])
				return false;
		}
		return true;
	}

	void runTests(Sorter <T> **sorters)
	{
		T* originalRandArray = generateRandArray();
		T* originalReversedArray = generateReversedArray();
		T* originalConstantElementArray = generateConstantElementArray();
		MySorterInterface<T> *moreInfo;

		for (size_t i = 0, currentTestNumber = 0; i < numberOfSorters; i++, currentTestNumber = 0)
		{

			moreInfo = dynamic_cast <MySorterInterface<T>*>(sorters[i]);

			infoKeeper[i].sorterName = new char[strlen(moreInfo->getSorterName()) + 1];
			strncpy(infoKeeper[i].sorterName, moreInfo->getSorterName(), strlen(moreInfo->getSorterName()) + 1);

			infoKeeper[i].testNames = new char*[NUMBER_OF_TEST_ARRAYS];

			infoKeeper[i].sortingStatuses = new bool[NUMBER_OF_TEST_ARRAYS];

			infoKeeper[i].testArraysSortTimes = new unsigned long long[NUMBER_OF_TEST_ARRAYS];



			for (size_t cnt = 0; cnt < NUMBER_OF_TEST_ARRAYS; cnt++)
			{
				infoKeeper[i].sortingStatuses[cnt] = false;
				infoKeeper[i].testArraysSortTimes[cnt] = 0;
				infoKeeper[i].testNames[cnt] = new char[strlen(TEST_NAMES[cnt]) + 1];
				strncpy(infoKeeper[i].testNames[cnt], TEST_NAMES[cnt], strlen(TEST_NAMES[cnt]) + 1);
			}

			if (testSorterOnRandArray(sorters[i], originalRandArray))
			{
				infoKeeper[i].sortingStatuses[currentTestNumber] = true;
				infoKeeper[i].testArraysSortTimes[currentTestNumber] = sorters[i]->getSortTime();
			}
			currentTestNumber++;

			if (testSorterOnReversedArray(sorters[i], originalReversedArray))
			{
				infoKeeper[i].sortingStatuses[currentTestNumber] = true;
				infoKeeper[i].testArraysSortTimes[currentTestNumber] = sorters[i]->getSortTime();
			}
			currentTestNumber++;

			if (testSorterOnConstantElementArray(sorters[i], originalConstantElementArray))
			{
				infoKeeper[i].sortingStatuses[currentTestNumber] = true;
				infoKeeper[i].testArraysSortTimes[currentTestNumber] = sorters[i]->getSortTime();
			}
		}
		delete[] originalRandArray;
		delete[] originalReversedArray;
		delete[] originalConstantElementArray;
	}
};