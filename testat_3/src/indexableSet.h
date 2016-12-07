#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <functional>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T,COMPARE>
{
public:
	int& operator[] (const int index);


};

#endif /* SRC_INDEXABLESET_H_ */
