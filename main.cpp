#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");

    Graph g(lines, true);
  
    std::cout << "Number of Nodes in Facebook graph: " << g.getSize() << std::endl;
    
    unsigned num = 50;
    std::cout << "Subset of Adjacency matrix with dimensions [" << num << "] x [" << num << "]: " <<std::endl;
    // Prints out subset of adjacency matrix. Starts at matrix[0][0] and goes to matrix[num][num]
    vector<vector<double>> adj_mat = g.getAdjacencyMatrix();
    // Define subset size here
    for (unsigned i = 0; i < num; i++) {
        for (unsigned j = 0; j < num; j++) {
            std::cout << adj_mat[i][j];
        }
        std::cout << std::endl;
    }

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
}