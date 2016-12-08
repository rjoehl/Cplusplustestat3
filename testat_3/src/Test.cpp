#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "indexableSet.h"

#include <set>

void indexableSet_subscript_operator_should_return_element_at_index() {
	indexableSet<int> const cvalues{0, 1, 2, 3, 4, 5};
	indexableSet<int> values{0, 1, 2, 3, 4, 5};
	ASSERT_EQUAL(3, cvalues[3]);
	ASSERT_EQUAL(3, values[3]);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(indexableSet_subscript_operator_should_return_element_at_index));
	//TODO add your test here
	//s.push_back(CUTE(indexableSet_ctor_should_work_like_set));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
