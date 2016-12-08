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
	decltype(auto) operator[](int index) const {
		auto it = index >= 0 ? Base::cbegin() : Base::cend();
		std::advance(it, index);
		return *it;
	}
	decltype(auto) operator[](int index) {
		auto it = index >= 0 ? Base::begin() : Base::end();
		std::advance(it, index);
		return *it;
	}

};

#endif /* SRC_INDEXABLESET_H_ */
