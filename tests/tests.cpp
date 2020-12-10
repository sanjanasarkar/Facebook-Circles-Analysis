#include <string>
#include <vector>

#include "catch.hpp"
#include "../src/FileReader.h"
#include "../src/Graph.h"

/* Dummy test case */
TEST_CASE("Do you even test?") {
	std::string res = "Hey";
	// always check "expected" == "actual" --> be consistent
	REQUIRE("Hey" == res);
}
