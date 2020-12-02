#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");

    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;

    Vertex max_node = 0;
    for (size_t i = 0; i < lines.size()/2; ++i) {
        Graph::Edge edge(lines[2*i], lines[2*i + 1], 1);
        edges.push_back(edge);
        max_node = std::max(edge.maxVertex(), max_node);
        /*if (i % 1000 == 0)
            std::cout << edge << max_node <<std::endl;*/
    }

    Graph g(edges, max_node);
    Graph f(lines);
    //std::cout << g << std::endl;
    //std::cout << f;
    std::cout << (g == f) << std::endl;
}