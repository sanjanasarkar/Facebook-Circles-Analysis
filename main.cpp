#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {   
    vector<string> lines;    
    start:
        int graph_file = -1;
        int double_dir = -1;
        cout << endl << "**********************************" << endl;
        cout << "* Hello! Welcome to our project! *" << endl;
        // Include code for whole dataset here
        while (graph_file == -1){
            cout << "**********************************" << endl;
            cout << "Which graph are you interested in taking a closer look at?" << endl;
            cout << "1. Simple" << endl << "2. Complex" << endl;
            cout << "Please type '1' or '2': ";
            cin >> graph_file;
            cout << endl;
            if (cin.fail()) {
                cout << "sorry, you did not input an integer " << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                graph_file = -1;
            }
        }
        
        // Deciding between simple and complex graph
        if (graph_file == 1) {
            lines = FileReader::fileToVector("data/simple_graph.txt");
        } else if (graph_file == 2) {
            // lines = FileReader::fileToVector("data/complex_graph.txt");
            lines = FileReader::fileToVector("tests/test_data_complex_path.txt");
        } else {
            cout << "Sorry, that command is not recognized. Try Again." << endl;
            graph_file = -1;
            goto start;
        } 

        DIRECTION:

        while (double_dir == -1) {
            cout << "**********************************" << endl;
            cout << "Which graph are you interested in taking a closer look at?" << endl;
            cout << "Single-Directed? or Double-Directed?" << endl;
            cout << "Please type '1' or '2': ";
            cin >> double_dir;
            cout << endl;
            if (cin.fail()) {
                cout << "sorry, you did not input an integer " << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                double_dir = -1;
            }
        }
        
        if (double_dir != 1 && double_dir != 2) {
            cout << "Please choose a valid number" << endl;
            cout << endl;
            double_dir = -1;
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