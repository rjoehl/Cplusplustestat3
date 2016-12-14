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
		auto actualIndex = index >= 0 ? index : Base::size() + index;
		if (actualIndex >= Base::size()) {
			throw std::out_of_range("Absolute of index must be smaller than size.");
		}
		return *std::next(Base::cbegin(), actualIndex);
	}

	T const & at(int index) const {
		return operator[](index);
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
