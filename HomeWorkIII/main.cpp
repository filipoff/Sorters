#include "Sorter.h"

int main()
{
	Sorter<int> **sorters = new Sorter < int >*[5] ;
	sorters[0] = new QuickSorter <int> ();
	sorters[2] = new InsertionSorter <int>();
	sorters[1] = new MergeSorter <int> ();
	//sorters[2] = new InsertionSorter <int> ();
	
	Tester<int> tester(sorters,2);
	tester.getSummary(std::cout);
	

	return 0;
}