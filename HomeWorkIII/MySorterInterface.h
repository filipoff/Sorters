#pragma once

template <class T>
class MySorterInterface : public Sorter < T >
{
public:
	virtual const char* getSorterName() const = 0;
	unsigned long long timeTaken;
};
