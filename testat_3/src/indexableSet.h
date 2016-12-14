#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <functional>
#include <iterator>
#include <cstdlib>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE>
{
	using Base = std::set<T, COMPARE>;
public:
	using Base::set;
	using size_type = typename Base::size_type;

	T const & operator[](int index) const {
		if ((size_type)std::abs(index) >= Base::size()) {
			throw std::out_of_range("Absolute of index must be smaller than size.");
		}
		auto it = index >= 0 ? Base::cbegin() : Base::cend();
		std::advance(it, index);
		return *it;
	}

	T const & front() const {
		if (Base::empty()) {
			throw std::out_of_range("Set is empty.");
		}
		return *Base::cbegin();
	}

	T const & back() const {
		if (Base::empty()) {
			throw std::out_of_range("Set is empty.");
		}
		return *Base::crbegin();
	}
};

#endif /* SRC_INDEXABLESET_H_ */
