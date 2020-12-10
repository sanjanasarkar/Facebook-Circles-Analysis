#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {
    vector<string> lines = FileReader::fileToVector("data/twitter_combined.txt");

    vector<Graph::Edge> edges;
    std::cout << lines.size() << " " << lines[lines.size() - 1] << std::endl;

    Graph g(lines, true);
    //std::cout << g << std::endl;
    //std::cout << f;
    std::cout << g.getSize() << std::endl;
}