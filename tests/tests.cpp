#include <string>
#include <vector>

#include "catch.hpp"
#include "../src/FileReader.h"
#include "../src/Graph.h"

/** Floyd Warshall for a Single Directed "test_simple_data" graph should look like:
 *          0		1		1		2
 * 			inf		0		inf		inf
 * 			inf		inf		0		1
 * 			inf		inf		inf		0
 * Note: in our implementation, infinity (inf) is defined as __INT_MAX_ (approx 2.14748e+09)
 */

TEST_CASE("Shortest Path test simple - single directed", "[floyd-warshall][simple][single-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test.txt");
	Graph g(lines, false);  // single directed graph
	double INF = __INT_MAX__;
	
	vector<vector<double>> expected = { {0, 1, 1, 2},
										{INF, 0, INF, INF},
										{INF, INF, 0, 1},
										{INF, INF, INF, 0}
									  };

	vector<vector<double>> fw_mat = g.FloydWarshall();
	REQUIRE(expected == fw_mat);
}

/** Floyd Warshall for a Double Directed "test_simple_data" graph should look like:
 *          0		1		1		2
 * 			1		0		2		3
 * 			1		2		0		1
 * 			2		3		1		0
 * Note: in our implementation, infinity (inf) is defined as __INT_MAX_ (approx 2.14748e+09)
 */

TEST_CASE("Shortest Path test simple - double directed", "[floyd-warshall][simple][double-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test.txt");
	Graph g(lines, true);  // double directed graph
	
	vector<vector<double>> expected = { {0, 1, 1, 2},
										{1, 0, 2, 3},
										{1, 2, 0, 1},
										{2, 3, 1, 0}
									  };

	vector<vector<double>> fw_mat = g.FloydWarshall();
	REQUIRE(expected == fw_mat);
}

