#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {   
    vector<string> lines;    
    start:
        string graph_file;
        int double_dir;
        cout << "Hello! Welcome to our project" << endl;
        cout << endl;
        cout << "Which graph are you interested in taking a closer look at?" << endl;
        cout << "Simple? or Complex?" << endl;
        cout << "Please type your answer: ";
        cin >> graph_file;

        // Deciding between simple and complex graph
        if (graph_file == "Simple" || graph_file == "simple") {
            lines = FileReader::fileToVector("data/simple_graph.txt");
        } else if (graph_file == "Complex" || graph_file == "complex") {
            // lines = FileReader::fileToVector("data/complex_graph.txt");
            lines = FileReader::fileToVector("tests/test_data_complex_path.txt");
        } else {
            cout << "Sorry, that command is not recognized. Try Again." << endl;
            cout << endl;
            goto start;
        } 

        DIRECTION:
        cout << "Which graph are you interested in taking a closer look at?" << endl;
        cout << "Single-Directed? or Double-Directed?" << endl;
        cout << "Please type '1' or '2': ";
        cin >> double_dir;
        cout << endl;
        
        if (double_dir != 1 && double_dir != 2) {
            cout << "Please choose a valid number" << endl;
            cout << endl;
            goto DIRECTION;
        }

    bool double_directed = double_dir - 1;
    Graph g(lines, double_directed);
    g.start_presentation();
    

    // // vector<Vertex> verts = g.get_vertices();
    // // for (unsigned i = 0; i < verts.size(); i++) {
    // //     cout << verts[i] << " ";
    // // }

    // g.print_longest_paths(fw_mat, double_directed);
    // g.print_shortest_paths(fw_mat, double_directed);
    // // Do some cool algorithms here guys!
  
    // //std::cout << g << std::endl;
    // //std::cout << f;
    // std::cout << g.getSize() << std::endl;

    // std::cout << " 1  ";
    // // iddfs basic test
    // vector<int> trav = g.iddfs(0, 341, 300, g);

    // for (int i = 0; i < int(trav.size()); i++) {
    //     std::cout << trav[i] << " ";
    // }
    // std::cout << "\n";

    // // iddfs advanced test

    // int max = 250;

    // for (int i = 0; i < max; i++) {
    //     for (int j = 0; j < max; j++) {
    //         std::cout << i << " -> " << j << " :  ";

    //         vector<int> trav = g.iddfs(i, j, 300, g);

    //         for (int i = 0; i < int(trav.size()); i++) {
    //             std::cout << trav[i] << " ";
    //         }
    //         printf("\n");
    //     }
    // }
}