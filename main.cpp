#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("tests/test_data_path.txt");
    
    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;
    
    bool double_directed = true;
    Graph g(lines, double_directed);
    std::cout << "Size: " << g.getSize() << std::endl;
    
    // Prints out subset of adjacency matrix. Starts at matrix[0][0] and goes to matrix[num][num]
    
    vector<vector<double>> adj_mat = g.getAdjacencyMatrix();
    
    vector<vector<double>> fw_mat = g.FloydWarshall();
    cout << g << endl;

    // Prints out floyd-warshall matrix
    unsigned num = g.getSize();
    for (unsigned i = 0; i < num; i++) {
        for (unsigned j = 0; j < num; j++) {
            if (fw_mat[i][j] == __INT_MAX__) {
                std::cout << " " << "INF";
                continue;
            }
            std::cout << " " << fw_mat[i][j];
        }
        std::cout << std::endl;
    }

    // vector<Vertex> verts = g.get_vertices();
    // for (unsigned i = 0; i < verts.size(); i++) {
    //     cout << verts[i] << " ";
    // }

    g.print_longest_paths(fw_mat, double_directed);
    g.print_shortest_paths(fw_mat, double_directed);
}