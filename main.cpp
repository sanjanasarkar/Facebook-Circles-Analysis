#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");

    vector<Graph::Edge> edges;

    Vertex max_node = 0;
    // Adds all Edges to edges with random weights
    for (size_t i = 0; i < 10; ++i) {
        double rand_weight = ((double) (rand() % 10000) )/100.0;
        Graph::Edge edge(lines[2*i], lines[2*i + 1], rand_weight);
        edges.push_back(edge);
        max_node = std::max(edge.maxVertex(), max_node);
    }

    Graph g(edges, max_node);
    std::cout << g;
}