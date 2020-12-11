#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
<<<<<<< HEAD
    vector<string> lines = FileReader::fileToVector("tests/test_data_path.txt");
    
    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;
    
    bool double_directed = true;
    Graph g(lines, double_directed);
    std::cout << "Size: " << g.getSize() << std::endl;
    
=======
    vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");

    Graph g(lines, true);
  
    std::cout << "Number of Nodes in Facebook graph: " << g.getSize() << std::endl;
    
    unsigned num = 50;
    std::cout << "Subset of Adjacency matrix with dimensions [" << num << "] x [" << num << "]: " <<std::endl;
>>>>>>> 46efc207f9085568c546f1d8ef1691bfa9bc1dfa
    // Prints out subset of adjacency matrix. Starts at matrix[0][0] and goes to matrix[num][num]
    
    vector<vector<double>> adj_mat = g.getAdjacencyMatrix();
<<<<<<< HEAD
    
    vector<vector<double>> fw_mat = g.FloydWarshall();
    cout << g << endl;

    // Prints out floyd-warshall matrix
    unsigned num = g.getSize();
=======
    // Define subset size here
>>>>>>> 46efc207f9085568c546f1d8ef1691bfa9bc1dfa
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

<<<<<<< HEAD
    // vector<Vertex> verts = g.get_vertices();
    // for (unsigned i = 0; i < verts.size(); i++) {
    //     cout << verts[i] << " ";
    // }

    g.print_longest_paths(fw_mat, double_directed);
    g.print_shortest_paths(fw_mat, double_directed);
=======
    // Do some cool algorithms here guys!
  
    //std::cout << g << std::endl;
    //std::cout << f;
    std::cout << g.getSize() << std::endl;

    std::cout << " 1  ";
    // iddfs basic test
    vector<int> trav = g.iddfs(0, 341, 300, g);

    for (int i = 0; i < int(trav.size()); i++) {
        std::cout << trav[i] << " ";
    }
    std::cout << "\n";

    // iddfs advanced test

    int max = 250;

    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            std::cout << i << " -> " << j << " :  ";

            vector<int> trav = g.iddfs(i, j, 300, g);

            for (int i = 0; i < int(trav.size()); i++) {
                std::cout << trav[i] << " ";
            }
            printf("\n");
        }
    }
>>>>>>> 46efc207f9085568c546f1d8ef1691bfa9bc1dfa
}