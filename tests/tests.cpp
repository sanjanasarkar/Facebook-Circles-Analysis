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

/**
 * The "test_data_simple" Graph should look like this if single directed:
 * 0 ---> 1
 * |
 * |
 * V    
 * 2 ---> 3
 * 
 * and look like this if double directed:
 * 0 <--> 1
 * A
 * |
 * V    
 * 2 <--> 3 */

TEST_CASE("Simple FileReader test", "[filereader]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_simple.txt");

	REQUIRE(lines.size() == 6);

	string ans[] = {"0", "1", "0", "2", "2", "3"}; 

	for (size_t i = 0; i < lines.size(); ++i) {
		REQUIRE(lines[i] == ans[i]);
	}
}

TEST_CASE("Simple Graph Constructor test - from FileReader", "[graph][constructor][filereader][directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_simple.txt");

	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	REQUIRE(single_dir != double_dir);
	INFO("Single directed graph has size " + std::to_string(single_dir.getSize()) + ". Double directed graph has size "+ std::to_string(double_dir.getSize()));
	REQUIRE( (single_dir.getSize() == double_dir.getSize() && single_dir.getSize() == 4) );

	REQUIRE(single_dir.areConnected(0, 1));
	REQUIRE(single_dir.areConnected(0, 2));
	REQUIRE(single_dir.areConnected(2, 3));
	REQUIRE(!single_dir.areConnected(1, 0));
	REQUIRE(!single_dir.areConnected(2, 0));
	REQUIRE(!single_dir.areConnected(3, 2));
	REQUIRE(!single_dir.areConnected(0, 3));
	REQUIRE(!single_dir.areConnected(3, 0));

	REQUIRE(double_dir.areConnected(0, 1));
	REQUIRE(double_dir.areConnected(0, 2));
	REQUIRE(double_dir.areConnected(2, 3));
	REQUIRE(double_dir.areConnected(1, 0));
	REQUIRE(double_dir.areConnected(2, 0));
	REQUIRE(double_dir.areConnected(3, 2));
	REQUIRE(!double_dir.areConnected(0, 3));
	REQUIRE(!double_dir.areConnected(3, 0));
}

TEST_CASE("Simple Graph Constructor test - from vector", "[graph][constructor][edge][directed]") {
	vector<Graph::Edge> edges;

	edges.emplace_back(0, 1);
	edges.emplace_back(0, 2);
	edges.emplace_back(2, 3);

	Graph single_dir = Graph(edges, 4, false);
	Graph double_dir = Graph(edges, 4, true);

	REQUIRE(single_dir != double_dir);
	INFO("Single directed graph has size " + std::to_string(single_dir.getSize()) + ". Double directed graph has size "+ std::to_string(double_dir.getSize()));
	REQUIRE( (single_dir.getSize() == double_dir.getSize() && single_dir.getSize() == 4) );

	REQUIRE(single_dir.areConnected(0, 1));
	REQUIRE(single_dir.areConnected(0, 2));
	REQUIRE(single_dir.areConnected(2, 3));
	REQUIRE(!single_dir.areConnected(1, 0));
	REQUIRE(!single_dir.areConnected(2, 0));
	REQUIRE(!single_dir.areConnected(3, 2));
	REQUIRE(!single_dir.areConnected(0, 3));
	REQUIRE(!single_dir.areConnected(3, 0));

	REQUIRE(double_dir.areConnected(0, 1));
	REQUIRE(double_dir.areConnected(0, 2));
	REQUIRE(double_dir.areConnected(2, 3));
	REQUIRE(double_dir.areConnected(1, 0));
	REQUIRE(double_dir.areConnected(2, 0));
	REQUIRE(double_dir.areConnected(3, 2));
	REQUIRE(!double_dir.areConnected(0, 3));
	REQUIRE(!double_dir.areConnected(3, 0));
}

TEST_CASE("Simple Graph Function test", "[graph][functions][directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_simple.txt");

	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	REQUIRE(single_dir.getOutgoingEdges(0).size() == 2);
	REQUIRE(double_dir.getOutgoingEdges(0).size() == 2);

	REQUIRE(single_dir.getIncomingEdges(0).size() == 0);
	REQUIRE(double_dir.getIncomingEdges(0).size() == 2);

	REQUIRE(single_dir.getOutgoingEdges(3).size() == 0);
	REQUIRE(double_dir.getIncomingEdges(3).size() == 1);

	REQUIRE(single_dir.getWeight(0, 1) == 1);
	single_dir.changeWeight(Graph::Edge(0, 1, 0.1234));
	REQUIRE(single_dir.getWeight(0, 1) == 0.1234);
}

TEST_CASE("Simple IDDFS", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 1, 100, g);
	vector<int> test = {0, 1};
	REQUIRE(trav.size() == 2);
	REQUIRE(trav == test);

	trav = g.iddfs(0, 6, 100, g);
	test = {0, 2, 6};
	REQUIRE(trav.size() == 3);
	REQUIRE(trav == test);
}

TEST_CASE("Longer IDDFS", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 99, 200, g);
	vector<int> test = {0, 2, 6, 7, 8, 9, 10, 11, 99};
	REQUIRE(trav.size() == 9);
	REQUIRE(trav == test);
}

TEST_CASE("IDDFS find itself", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 0, 100, g);
	REQUIRE(trav.size() == 1);
	REQUIRE(trav[0] == 0);

	trav = g.iddfs(6, 6, 100, g);
	REQUIRE(trav.size() == 1);
	REQUIRE(trav[0] == 6);

}

TEST_CASE("IDDFS find nonexistent", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 100, 100, g);
	REQUIRE(trav.size() == 0);

	trav = g.iddfs(6, 100, 100, g);
	REQUIRE(trav.size() == 0);
}