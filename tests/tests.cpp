#include <string>
#include <vector>

#include "catch.hpp"
#include "../src/FileReader.h"
#include "../src/Graph.h"

/************************************** Tests for Graph Set-Up **************************************/

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

/*********************************** Tests for Traversals (BFS and DFS) ***********************************/

TEST_CASE("Simple BFS test", "[graph][functions][directed]") {
	// Setup Graph
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	// run BFS
	vector<int> path = double_dir.BFS(0, double_dir);

	// check if BFS ran a breadth first traversal
	REQUIRE(path.front() == 0);
	REQUIRE(path.back() == 77);
	REQUIRE(path.size() == 18);

	// run BFS
	path = double_dir.BFS(11, double_dir);

	// check if BFS ran a breadth first traversal
	REQUIRE(path.front() == 11);
	REQUIRE(path.back() == 1);
	REQUIRE(path.size() == 18);
	REQUIRE(path[14] == 0);
}

TEST_CASE("Full BFS test", "[graph][functions][directed]") {
	// Setup Graph
	vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");
	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	// run BFS
	vector<int> path = double_dir.BFS(0, double_dir);

	// check if BFS ran a breadth first traversal
	REQUIRE(path.front() == 0);
	REQUIRE(path.back() == 855);
	REQUIRE(path.size() == 4039);

	// run BFS
	path = double_dir.BFS(1000, double_dir);

	// check if BFS ran a breadth first traversal
	REQUIRE(path.front() == 1000);
	REQUIRE(path.back() == 855);
	REQUIRE(path.size() == 4039);
}

TEST_CASE("Simple DFS test", "[graph][functions][directed]") {
	// Setup Graph
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	// initialized what is needed for DFS Traversal
	vector<bool> visited;
	vector<int> traversal;
	for (int i = 0; i < single_dir.getSize(); i++) visited.push_back(false);

	double_dir.DFS(0, double_dir, visited, traversal);

	// Check if DFS does a depth search first traversal
	REQUIRE(traversal.front() == 0);
	REQUIRE(traversal.back() == 99);
	REQUIRE(traversal.size() == 18);

	// reset DFS
	for (int i = 0; i < single_dir.getSize(); i++) visited[i] = false;
	traversal.clear();

	// Check DFS at new starting point
	double_dir.DFS(11, double_dir, visited, traversal);

	// Check if DFS does a depth search first traversal
	REQUIRE(traversal.front() == 11);
	REQUIRE(traversal.back() == 99);
	REQUIRE(traversal.size() == 18);
	REQUIRE(traversal[7] == 0);
}

TEST_CASE("FULL DFS test", "[graph][functions][directed]") {
	// Setup Graph
	vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");
	Graph single_dir = Graph(lines, false);
	Graph double_dir = Graph(lines, true);

	// initialized what is needed for DFS Traversal
	vector<bool> visited;
	vector<int> traversal;
	for (int i = 0; i < single_dir.getSize(); i++) visited.push_back(false);

	double_dir.DFS(0, double_dir, visited, traversal);

	// Check if DFS does a depth search first traversal
	REQUIRE(traversal.front() == 0);
	REQUIRE(traversal.back() == 335);
	REQUIRE(traversal.size() == 4039);

	// reset DFS
	for (int i = 0; i < single_dir.getSize(); i++) visited[i] = false;
	traversal.clear();

	// Check DFS at new starting point
	double_dir.DFS(1000, double_dir, visited, traversal);

	// Check if DFS does a depth search first traversal
	REQUIRE(traversal.front() == 1000);
	REQUIRE(traversal.back() == 1834);
	REQUIRE(traversal.size() == 4039);
}

/*********************************** Tests for Complex Algorithm (IDDFS) ***********************************/
TEST_CASE("Simple IDDFS", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 1, 100);
	vector<int> test = {0, 1};
	REQUIRE(trav.size() == 2);
	REQUIRE(trav == test);

	trav = g.iddfs(0, 6, 100);
	test = {0, 2, 6};
	REQUIRE(trav.size() == 3);
	REQUIRE(trav == test);
}

TEST_CASE("Longer IDDFS", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 99, 200);
	vector<int> test = {0, 2, 6, 7, 8, 9, 10, 11, 99};
	REQUIRE(trav.size() == 9);
	REQUIRE(trav == test);
}

TEST_CASE("IDDFS find itself", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 0, 100);
	REQUIRE(trav.size() == 1);
	REQUIRE(trav[0] == 0);

	trav = g.iddfs(6, 6, 100);
	REQUIRE(trav.size() == 1);
	REQUIRE(trav[0] == 6);

}

TEST_CASE("IDDFS find nonexistent", "[graph][functions][directed][Search][IDDFS]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_abitlesssimple.txt");
	Graph g = Graph(lines, false);

	vector<int> trav = g.iddfs(0, 100, 100);
	REQUIRE(trav.size() == 0);

	trav = g.iddfs(6, 100, 100);
	REQUIRE(trav.size() == 0);
}

/****************************** Tests for Shortest Path Alg (Floyd-Warshall) ******************************/

/** Floyd Warshall for a Single Directed "test_simple_data" graph should look like:
 *          0		1		1		2
 * 			inf		0		inf		inf
 * 			inf		inf		0		1
 * 			inf		inf		inf		0
 * Note: in our implementation, infinity (inf) is defined as __INT_MAX_ (approx 2.14748e+09)
 */

TEST_CASE("Shortest Path test simple - single directed", "[floyd-warshall][simple][single-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_simple.txt");
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
 */

TEST_CASE("Shortest Path test simple - double directed", "[floyd-warshall][simple][double-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_simple.txt");
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
 * The "test_data_complex_path" Graph should look like this if single directed:
 * 0 ---> 1 ---> 2
 *  \	  |		 |
 *   \	  |		 |
 *    \   V		 V
 * 	   \> 3		 6
 * 		  |		 ^
 *  	  |		 |
 *        V		/
 * 		  4	   /	 
 * 		  |	  /	 
 *  	  |	 /	 
 *        V	/	 
 * 		  5		 
 * 
 * and look like this if double directed:
 * 0 <---> 1 <---> 2
 * ^\	  ^		 ^
 *   \	  |		 |
 *    \   V		 V
 * 	   \> 3		 6
 * 		  ^		 ^
 *  	  |		 |
 *        V	 	 /
 * 		  4	    /	 
 * 		  ^	   /	 
 *  	  |	  /	 
 *        V  /	 
 * 		  5</
 * */

TEST_CASE("Shortest Path test complex - single directed", "[floyd-warshall][complex][single-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_complex_path.txt");
	Graph g(lines, false);  // single directed graph
	double INF = __INT_MAX__;
	
	vector<vector<double>> expected = { {0, 1, 2, 2, 3, 1, 2},
										{INF, 0, 1, 1, 2, INF, 2},
										{INF, INF, 0, INF, INF, INF, 1},
										{INF, INF, INF, 0, 1, INF, INF},
										{INF, INF, INF, INF, 0, INF, INF},
										{INF, INF, INF, INF, INF, 0, 1},
										{INF, INF, INF, INF, INF, INF, 0}
									  };

	vector<vector<double>> fw_mat = g.FloydWarshall();
	REQUIRE(expected == fw_mat);
}

TEST_CASE("Shortest Path test complex - double directed", "[floyd-warshall][complex][double-directed]") {
	vector<string> lines = FileReader::fileToVector("tests/test_data_complex_path.txt");
	Graph g(lines, true);  // single directed graph
	double INF = __INT_MAX__;
	
	vector<vector<double>> expected = { {0, 1, 2, 2, 3, 1, 2},
										{1, 0, 1, 1, 2, 2, 2},
										{2, 1, 0, 2, 3, 2, 1},
										{2, 1, 2, 0, 1, 3, 3},
										{3, 2, 3, 1, 0, 4, 4},
										{1, 2, 2, 3, 4, 0, 1},
										{2, 2, 1, 3, 4, 1, 0}
									  };

	vector<vector<double>> fw_mat = g.FloydWarshall();

	vector<double> min_max_paths_expected = {1, 4};
	vector<double> min_max_paths = g.find_min_max_paths(fw_mat);

	// Check if min_max_paths function is working
	REQUIRE(min_max_paths_expected == min_max_paths);

	REQUIRE(expected == fw_mat);
}
