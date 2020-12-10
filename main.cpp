#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/twitter_combined.txt");

    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;

    Graph g(lines, true);
    std::cout << g.getSize() << std::endl;

    // Prints out subset of adjacency matrix. Starts at matrix[0][0] and goes to matrix[num][num]
    vector<vector<double>> adj_mat = g.getAdjacencyMatrix();
    // Define subset size here
    unsigned num = 50;
    for (unsigned i = 0; i < num; i++) {
        for (unsigned j = 0; j < num; j++) {
            std::cout << adj_mat[i][j];
        }
        std::cout << std::endl;
    }
}