#include <string>
#include <vector>

#include "catch.hpp"
#include "../src/FileReader.h"


TEST_CASE("Do you even test?") {
	std::string res = "Hey";
	// always check "expected" == "actual" --> be consistent
	REQUIRE("Hey" == res);
}

// TEST_CASE("Verify that file_to_vector works on a small example") {
// 	std::vector<std::string> res = file_to_vector("tests/smallSample.txt");
// 	std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};
	
// 	REQUIRE(6 == res.size());

// 	for (int i = 0; i < res.size(); i++) {
// 		REQUIRE(expected[i] == res[i]);
// 	}
// }