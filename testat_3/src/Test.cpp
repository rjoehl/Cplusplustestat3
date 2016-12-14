#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "indexableSet.h"

#include <set>
#include <string>
#include <functional>
#include <cctype>
#include <algorithm>
#include <vector>

void indexableSet_subscript_operator_should_return_element_at_index() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_EQUAL(3, values[3]);
}

void indexableSet_subscript_operator_should_return_element_at_negative_index() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_EQUAL(4, values[-2]);
}

void indexableSet_subscript_operator_should_throw_when_index_out_of_range() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_THROWS(values[15], std::out_of_range);
}

void indexableSet_subscript_operator_should_throw_when_negative_index_out_of_range() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_THROWS(values[-15], std::out_of_range);
}

void indexableSet_front_should_return_first_element() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_EQUAL(0, values.front());
}

void indexableSet_front_should_throw_when_empty() {
	indexableSet<int> const values{};
	ASSERT_THROWS(values.front(), std::out_of_range);
}

void indexableSet_back_should_return_last_element() {
	indexableSet<int> const values{0, 5, 3, 4, 1, 2};
	ASSERT_EQUAL(5, values.back());
}

void indexableSet_back_should_throw_when_empty() {
	indexableSet<int> const values{};
	ASSERT_THROWS(values.back(), std::out_of_range);
}

struct caselessCompare {
	bool operator()(std::string const &lhs, std::string const &rhs) {
		return lexicographical_compare( begin(lhs), end(lhs), begin(rhs), end(rhs), [](auto ch1, auto ch2) {
			return std::tolower(ch1) < std::tolower(ch2);
		});
	}
};

void indexableSet_using_caseless_compare_functor() {
	indexableSet<std::string, caselessCompare> words{"Ich", "Aber", "auch", "nicht"};
	std::vector<std::string> expected{"Aber", "auch", "Ich", "nicht"};
	std::vector<std::string> actual{begin(words), end(words)};
	ASSERT_EQUAL(expected, actual);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(indexableSet_subscript_operator_should_return_element_at_index));
	s.push_back(CUTE(indexableSet_subscript_operator_should_return_element_at_negative_index));
	s.push_back(CUTE(indexableSet_subscript_operator_should_throw_when_index_out_of_range));
	s.push_back(CUTE(indexableSet_subscript_operator_should_throw_when_negative_index_out_of_range));
	s.push_back(CUTE(indexableSet_front_should_return_first_element));
	s.push_back(CUTE(indexableSet_front_should_throw_when_empty));
	s.push_back(CUTE(indexableSet_using_caseless_compare_functor));
	s.push_back(CUTE(indexableSet_back_should_return_last_element));
	s.push_back(CUTE(indexableSet_back_should_throw_when_empty));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
