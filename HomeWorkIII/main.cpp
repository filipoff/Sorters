#include "Sorter.h"

int main()
{
	Sorter<int> **sorters = new Sorter < int >*[5] ;
	sorters[0] = new QuickSorter <int> ();
	sorters[1] = new MergeSorter <int>();
	sorters[2] = new HeapSorter <int>();
	sorters[3] = new InsertionSorter <int> ();
	

	Tester<int> tester(sorters,4);
	tester.getSummary(cout);
	

	return 0;
}