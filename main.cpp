#include <iostream>
#include <algorithm>

#include "src/Graph.h"
#include "src/FileReader.h"

int main() {   
    vector<string> lines;    
    start:
        int graph_file = -1;
        int double_dir = -1;
        int full_subset;
        bool is_full_dataset;

        // Welcome Message
        cout << endl << "**********************************" << endl;
        cout << "* Hello! Welcome to our project! *" << endl;
        cout << "**********************************" << endl;

        // Choosing between full dataset and subsets
        SUBSET:
        cout << "To begin, would you like to see our program work on" << endl;
        cout << "1. Full Dataset (WARNING: FUNCTIONALITY MAY SUFFER DUE TO SIZE OF DATASET)" << endl;
        cout << "2. Subsets of Dataset" << endl;
        cout << "Please type '1' or '2'" << endl;
        cin >> full_subset;
        cout << endl;

        if (full_subset == 1) {
            is_full_dataset = true;
        } else if (full_subset == 2) {
            is_full_dataset = false;
        } else {
            cout << "Sorry, that command was not recognized. Please try again." << endl;
            cout << endl;
            goto SUBSET;
        }
        
        // Picked subset
        while (!is_full_dataset && graph_file == -1){
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
        
        // Deciding between simple and complex graph (ONLY if subset was picked)
        if (!is_full_dataset && graph_file == 1) {  // Simple
            lines = FileReader::fileToVector("data/simple_graph.txt");
        } else if (!is_full_dataset && graph_file == 2) {  // Complex
            lines = FileReader::fileToVector("data/complex_graph.txt");
        } else if (is_full_dataset) {  // Full Dataset
            lines = FileReader::fileToVector("data/facebook_combined.txt");
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
    g.start_presentation(is_full_dataset);
    

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