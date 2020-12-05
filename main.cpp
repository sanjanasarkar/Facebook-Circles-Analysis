#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/facebook_combined.txt");

    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;

    Graph g(lines, true);
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