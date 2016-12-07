#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <functional>
#include <iterator>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE>
{
	using Base = std::set<T, COMPARE>;
public:
	using Base::set;
	using size_type = typename Base::size_type;
	decltype(auto) operator[](size_type index) const {
		auto it = Base::cbegin();
		std::advance(it, index);
		return *it;
	}

};

#endif /* SRC_INDEXABLESET_H_ */
