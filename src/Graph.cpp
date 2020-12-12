#include <iostream>
#include <chrono>
#include <algorithm>

#include "Graph.h"

/****************************** Graph Functions ******************************/

void Graph::__init(const vector<Edge>& edges, size_t num_nodes, bool double_directed) {
    is_double_directed = double_directed;
    // Initialize adjacency matrix
    matrix_.clear();
    vertices.clear();
    for (size_t i = 0; i < num_nodes; ++i) {
        vector<double> line(num_nodes, 0.0);
        matrix_.push_back(line);
    }

    for (Edge e : edges) {
        matrix_[e.start][e.end] = e.weight; 

        if (double_directed)
            matrix_[e.end][e.start] = e.weight;
        
        // Initializes vertices vector
        // Check if first vertex already in vertices vector
        if (std::find(vertices.begin(), vertices.end(), e.start) == vertices.end()) {
            vertices.push_back(e.start);
        }
        // Check if second vertex already in vertices vector
        if (std::find(vertices.begin(), vertices.end(), e.end) == vertices.end()) {
            vertices.push_back(e.end);
        }
    }
}

Graph::Graph(const vector<string>& lines, bool double_directed) {
    vector<Graph::Edge> edges;

    Vertex max_node = 0;
    for (size_t i = 0; i < lines.size()/2; ++i) {
        Graph::Edge edge(lines[2*i], lines[2*i + 1], 1);
        edges.push_back(edge);

        max_node = std::max(edge.maxVertex(), max_node);
    }

    __init(edges, max_node + 1, double_directed);
}

Graph::Graph(const vector<Edge>& edges, size_t num_nodes, bool double_directed) {
    __init(edges, num_nodes, double_directed);
}

bool Graph::areConnected(const Edge& e) const {
    return areConnected(e.start, e.end);
}

bool Graph::areConnected(Vertex start, Vertex end) const {
    if (start >= matrix_.size() || end >= matrix_.size())
        return false;
    return (matrix_[start][end] != 0);
}

void Graph::changeWeight(const Edge& e) {
    changeWeight(e.start, e.end, e.weight);
}

void Graph::changeWeight(Vertex start, Vertex end, double weight) {
    if (start > matrix_.size() || end >= matrix_.size())
        return;
    matrix_[start][end] = weight;
}

double Graph::getWeight(const Edge& e) const {
    return getWeight(e.start, e.end);
}

double Graph::getWeight(Vertex start, Vertex end) const {
    if (!areConnected(start, end))
        return 0;
    return matrix_[start][end];
}

vector<Graph::Edge> Graph::getOutgoingEdges(Vertex start) const {
    vector<Edge> edges;
    if (start >= matrix_.size())
        return edges;

    for (size_t j = 0; j < matrix_[start].size(); ++j) {
        if (matrix_[start][j] != 0)
            edges.emplace_back(start, j, matrix_[start][j]);
    }
    return edges;
}

vector<Graph::Edge> Graph::getIncomingEdges(Vertex end) const {
    vector<Edge> edges;
    if (end >= matrix_.size())
        return edges;

    for (size_t i = 0; i < matrix_.size(); i++) {
        if (matrix_[i][end] != 0)
            edges.emplace_back(i, end, matrix_[i][end]);
    }
    return edges;
}

vector<Vertex> Graph::get_vertices() {
    return vertices;
}

bool operator==(const Graph& lhs, const Graph& rhs) {
    if (lhs.matrix_.size() != rhs.matrix_.size() || lhs.matrix_[0].size() != rhs.matrix_.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.matrix_.size(); i++) {
        for (size_t j = 0; j < lhs.matrix_[i].size(); j++) {
            if (lhs.matrix_[i][j] != rhs.matrix_[i][j])
                return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
    for (size_t i = 0; i < g.matrix_.size(); i++) {
        out << "[ ";
        for (size_t j = 0; j < g.matrix_.at(i).size(); j++) {
            out << g.matrix_[i][j] << " ";
        }
        out << "]" << std::endl;
    }
    return out;
}

/****************************** Complex Alg Functions ******************************/

// IDDFS: do a depth first search, but limit the max depth of the search starting at 1.
// if not found, make max_depth deeper and do the depth limited search at a deeper level
// until the node is found. Theoretically combines DFS's space efficiency w/ bfs's speed.

// Time complexity: O(b^d)
// Space complexity: O(bd)
// (b is breadth, d is depth)
vector<int> Graph::iddfs(int start, int end, int max_depth) {
    
    for (int i = 1; i < max_depth; i++) {
        // init the traversal, as well as a vector that is the reverse
        vector<int> trav;
        vector<int> reverse;

        // do the dls, go deeper if failed
        if (dls(start, end, i, trav)) {
            // flip the output to have the correct order, might slow it down (not 100% needed)
            for (int i = int(trav.size())-1; i >= 0 ; i--) {
                reverse.push_back(trav[i]);
            }
            return reverse;
        }
    }
    return vector<int>();
}

// recursively do the depth limited search
bool Graph::dls(int start, int end, int limit, vector<int> &path) {

    // base case
    if (start == end) {
        path.push_back(start);
        return true;
    }
    // stop if depth limit is reached
    if (limit <= 0) {
        return false;
    }
    // otherwise recurse through all connected vertices
    vector<Graph::Edge> adj = getOutgoingEdges(start);
    for (unsigned i = 0; i < adj.size(); i++) {
        if (dls(adj[i].end, end, limit-1, path)) {
            path.push_back(start);
            return true;
        }
    }

    return false;
}

/****************************** Traversal Functions ******************************/

/* 
 * BFS IMPLEMENTATION
 * Basic algorithm idea:
 * AFTER the adjency matrix is set up we can finally call the BFS function.
 * Create a visited array to avoid cycles
 * Given a starting node and target node check all adjacent nodes and move to the next node unless already visited
 * Recursively does this to build array of nodes that marks the shortest path
 * returns array containing path from one node to the other
 */

vector<int> Graph::BFS(int start, const Graph& g) {
    vector<bool> visited(g.matrix_.size(), false);
    vector<int> queue, traversal;
    int vs;

    queue.push_back(start);

    visited[start] = true;

    while (!queue.empty()) {
        vs = queue[0];

        traversal.push_back(vs);
        queue.erase(queue.begin());

        for (int i = 0; i < int(g.matrix_.size()); i++) {
            if (g.matrix_[vs][i] == 1 && (!visited[i])) {
                queue.push_back(i);
                visited[i] = true;
            }
        }
    }

    return traversal;
}

void Graph::DFS(int start, const Graph& g, vector<bool> &visited, vector<int> &dfsTraversal) {
    dfsTraversal.push_back(start);
    visited[start] = true;
    for (int i = 0; i < int(g.matrix_.size()); i++) {
        if (g.matrix_[start][i] == 1 && (!visited[i])) DFS(i, g, visited, dfsTraversal);
    }
}

/****************************** Basic Search Functions ******************************/
vector<int> Graph::Search_BFS(int start, int end, const Graph& g) {
    vector<bool> visited(g.matrix_.size(), false);
    vector<int> queue, traversal;
    int vs;

    queue.push_back(start);

    visited[start] = true;

    while (!queue.empty()) {
        vs = queue[0];

        traversal.push_back(vs);
        if (vs == end) return traversal;
        queue.erase(queue.begin());

        for (int i = 0; i < int(g.matrix_.size()); i++) {
            if (g.matrix_[vs][i] == 1 && (!visited[i])) {
                queue.push_back(i);
                visited[i] = true;
            }
        }
    }

    return traversal;
}

void Graph::Search_DFS(int start, int end, const Graph& g, vector<bool> &visited, vector<int> &dfsTraversal) {
    if(find(dfsTraversal.begin(), dfsTraversal.end(), end) != dfsTraversal.end()) return;
    dfsTraversal.push_back(start);
    visited[start] = true;
    if (start == end) return;
    for (int i = 0; i < int(g.matrix_.size()); i++) {
        if (g.matrix_[start][i] == 1 && (!visited[i]) && start != end) Search_DFS(i, end, g, visited, dfsTraversal);
    }
}

/****************************** Shortest Path Alg Functions ******************************/

vector<vector<double>> Graph::FloydWarshall() {
    int INFINITY = __INT_MAX__;
    int num_vertices = getSize();
    int n = num_vertices;
    vector<vector<double>> floyd_warsh_matrix(n, vector<double>(n, 0.0));
    
    // Initialize adjacency matrix to +inf and set diagonal to 0.0 
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            // Check if there is a connection (All edge weights = 1. No further calculations needed)
            if (matrix_[i][j] == 1) {
                floyd_warsh_matrix[i][j] = matrix_[i][j];
            } else if (i == j) { // Check if vertex points to self (e.g. Vertex A to Vertex A)
                floyd_warsh_matrix[i][j] = 0.0;
            } else { // Set pairs with no relationship to infinity
                floyd_warsh_matrix[i][j] = INFINITY;
            }
        }
    }

    // The meat of the Floyd Warshall Algorithm
    for (int w = 0; w < num_vertices; w++) {
        for (int u = 0; u < num_vertices; u++) {
            for (int v = 0; v < num_vertices; v++) {
                if (floyd_warsh_matrix[u][v] > floyd_warsh_matrix[u][w] + floyd_warsh_matrix[w][v]) {
                    floyd_warsh_matrix[u][v] = floyd_warsh_matrix[u][w] + floyd_warsh_matrix[w][v];
                }
            }
        }
    }

    return floyd_warsh_matrix; 
}

void Graph::print_shortest_paths(const vector<vector<double>> fw_matrix, bool double_directed) {
    double smallest = find_min_max_paths(fw_matrix)[0];

    // Compile all relationships that have the min path length
    std::vector<std::string> shortest_paths;

    // This loop traverses the upper triangle (including diagonal) of the square floyd-warshall matrix
    unsigned cur_row = 0;
    for (unsigned i = 0; i < fw_matrix[0].size(); i++) {
        for (unsigned j = cur_row; j < fw_matrix[0].size(); j++) {
            if (fw_matrix[i][j] == smallest && !double_directed) {
                string shortest_path = "Friend " + to_string(i) + " -> Friend " + to_string(j);
                shortest_paths.push_back(shortest_path);
            }
            if (fw_matrix[i][j] == smallest && double_directed) {
                string shortest_path = "Friend " + to_string(i) + " <-> Friend " + to_string(j);
                shortest_paths.push_back(shortest_path);
            }
        }
        cur_row++;
    }
    cout << "Shortest Path Length: " << smallest << endl;

    unsigned lim;
    if (shortest_paths.size() > 30) {
        lim = 30;
        cout << "NOTE: The following output is truncated for printing purposes:" << endl;
    } else {
        lim = shortest_paths.size();
    }

    cout << "The shortest paths occur between:" << endl;
    for (unsigned i = 0; i < lim; i++) {
        cout << shortest_paths[i] << endl;
    } 
}

void Graph::print_longest_paths(const vector<vector<double>> fw_matrix, bool double_directed) {
    double longest = find_min_max_paths(fw_matrix)[1];

    // Compile all relationships that have the max path length
    std::vector<std::string> longest_paths;

    // This loop traverses the upper triangle (including diagonal) of the square floyd-warshall matrix
    unsigned cur_row = 0;
    for (unsigned i = 0; i < fw_matrix[0].size(); i++) {
        for (unsigned j = cur_row; j < fw_matrix[0].size(); j++) {
            if (fw_matrix[i][j] == longest && !double_directed) {
                string longest_path = "Friend " + to_string(i) + " -> Friend " + to_string(j);
                longest_paths.push_back(longest_path);
            }
            if (fw_matrix[i][j] == longest && double_directed) {
                string longest_path = "Friend " + to_string(i) + " <-> Friend " + to_string(j);
                longest_paths.push_back(longest_path);
            }
        }
        cur_row++;
    }
    cout << "Longest Path Length: " << longest << endl;
    unsigned lim;
    if (longest_paths.size() > 30) {
        lim = 30;
        cout << "NOTE: The following output is truncated for printing purposes:" << endl;
    } else {
        lim = longest_paths.size();
    }

    cout << "The longest paths occur between:" << endl;
    for (unsigned i = 0; i < lim; i++) {
        cout << longest_paths[i] << endl;
    } 
}

vector<double> Graph::find_min_max_paths(const vector<vector<double>> matrix) {
    // First find smallest and longest path length
    double smallest = __INT_MAX__; 
    double longest = 0.0;

    for (unsigned i = 0; i < matrix[0].size(); i++) {
        for (unsigned j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] < smallest && matrix[i][j] != 0.0) {
                smallest = matrix[i][j];
            }
            if (matrix[i][j] > longest && matrix[i][j] != __INT_MAX__) {
                longest = matrix[i][j];
            }
        }
    }
    vector<double> min_max_vals {smallest, longest};
    return min_max_vals;
}

/*************************** I/O Driver Code ***************************/
void Graph::start_presentation(bool is_full_dataset) {
    vector<string> lines;
    cout << "We examined a dataset of social circles on Facebook" << endl;
    Current_State current_state = Current_State::MENU;
    bool structure = false;
    bool traversals = false;
    bool shortpath = false;
    bool complexalg = false;
    bool timecomplexity = false;

    LOOP:
    while (!(structure && traversals && shortpath && complexalg && timecomplexity)) {
        switch(current_state) {
            MENU_START:
            case Current_State::MENU: {
                cout << "**********************************" << endl;
                cout << "What would you like to see?"  << endl;
                cout << "1. Graph Structure" << endl;
                if (!is_full_dataset) cout << "2. Traversals" << endl;
                if (!is_full_dataset)  cout << "3. Shortest Path Algorithm" << endl;
                if (!is_full_dataset) cout << "4. Complex Algorithm" << endl;
                (is_full_dataset) ? cout << "2. Runtimes of Traversals and Searches" << endl : cout << "5. Run Times of Traversals and Searches" << endl;
                (is_full_dataset) ? cout << "3. Quit Program" << endl : cout << "6. Quit Program" << endl;
                cout << "Type in the number: "; 
                int num;
                
                cin >> num;
                if (cin.fail()) {
                    cout << endl << "sorry, you did not input an integer " << endl << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cout << endl;
                switch(num) {
                    case 1:
                        current_state = Current_State::STRUCTURE;
                        break;
                    case 2:
                        (is_full_dataset) ? current_state = Current_State::TIMECOMPLEXITY : current_state = Current_State::TRAVERSALS;
                        break;
                    case 3:
                        (is_full_dataset) ? current_state = Current_State::QUIT : current_state = Current_State::SHORTESTPATH;
                        break;
                    case 4:
                        if (!is_full_dataset) current_state = Current_State::COMPLEXALG;
                        else {
                            cout << "Sorry, that command is not recognized. Try Again." << endl << endl;
                            num = -1;
                            goto MENU_START;
                        }
                        break;
                    case 5:
                        if (!is_full_dataset) current_state = Current_State::TIMECOMPLEXITY;
                        else {
                            cout << "Sorry, that command is not recognized. Try Again." << endl << endl;
                            num = -1;
                            goto MENU_START;
                        }
                        break;
                    case 6:
                        if (!is_full_dataset) current_state = Current_State::QUIT;
                        else {
                            cout << "Sorry, that command is not recognized. Try Again." << endl << endl;
                            num = -1;
                            goto MENU_START;
                        }
                        break;
                    default:
                        cout << "Sorry, that command is not recognized. Try Again." << endl << endl;
                        num = -1;
                        goto MENU_START;
                }
                break;
            }
            case Current_State::STRUCTURE: {
                /************* STRUCTURE OUTPUT HERE *************/
                cout << "Overall Graph Structure" << endl;
                cout << "Number of Nodes in Facebook graph: " << getSize() << endl;

                int dim = get_vertices().size();
                cout << "Subset of Adjacency matrix with dimensions [" << dim << "] x [" << dim << "]: " << endl;
                cout << endl;

                if (!is_full_dataset) {
                    // Prints out subset of adjacency matrix. Starts at matrix[0][0] and goes to matrix[dim][dim]
                    vector<vector<double>> adj_mat = this->getAdjacencyMatrix();
                    cout << *this << endl;
                } else {
                    cout << "Sorry, adjacency matrix cannot be displayed due to its size" << endl;
                    cout << endl;
                }

                current_state = Current_State::MENU;
                break;
            }

            TRAVERSALS:
            case Current_State::TRAVERSALS: {
                /************* TRAVERSALS OUTPUT HERE *************/
                cout << "Traversals" << endl;
                cout << endl;
                cout << "Choose between the following options: " << endl;
                cout << "1. BFS" << endl << "2. DFS" << endl;
                cout << "Type in the number: ";

                // initialize required variables
                vector<int> path, traversal;
                int selector, start = -1;
                vector<bool> visited;
	            for (size_t i = 0; i < this->getSize(); i++) visited.push_back(false);

                // choose traversal
                cin >> selector;
                if (cin.fail()) {
                    cout << endl << "sorry, you did not input an integer " << endl << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                // display vertices
                cout << "Vertices in graph:  " << endl;
                for(unsigned i : vertices) cout << i << " ";
                cout << endl;

                // select starting node thats in the graph
                while (start == -1) {
                    cout << "**********************************" << endl << "What node do you want to start at?" << endl;
                    cout << "Type in the number: ";
                    cin >> start;
                    if (cin.fail()) {
                        cout << endl << "sorry, you did not input an integer " << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        start = -1;
                    }
                    if (this->getOutgoingEdges(start).size() == 0) {
                        cout << endl << "sorry, that vertix doesn't exist, try again " << endl << endl;
                        start = -1;
                    }
                }

                // perform traversals based on selector
                switch(selector) {
                    case 1:
                        path = this->BFS(start, * this);
                        cout << endl << "BFS Traversal produces: " << endl;
                        for(unsigned i : path) cout << i << " ";
                        cout << endl;
                        break;
                    case 2:
                        this->DFS(start, * this, visited, traversal);
                        cout << endl << "DFS Traversal produces: " << endl;
                        for(unsigned i : traversal) cout << i << " ";
                        cout << endl;
                        break;
                    default:
                        cout << "Sorry, that command is not recognized. Try Again." << endl;
                        cout << endl;
                        selector = -1;
                        goto TRAVERSALS;
                }

                current_state = Current_State::MENU;
                break;
            }
            case Current_State::SHORTESTPATH: {
                /************* SHORTEST PATH OUTPUT HERE *************/
                cout << "Shortest Path - Floyd-Warshall Algorithm" << endl;
                cout << endl;

                if (!is_full_dataset) {
                    vector<vector<double>> fw_mat = this->FloydWarshall();
                    cout << "All-Pairs matrix: " << endl;

                    unsigned size = this->getSize();
                    // Prints out floyd-warshall matrix
                    for (unsigned i = 0; i < size; i++) {
                        for (unsigned j = 0; j < size; j++) {
                            if (fw_mat[i][j] == __INT_MAX__) {
                                std::cout << " " << "INF";
                                continue;
                            }
                            std::cout << " " << fw_mat[i][j];
                        }
                        std::cout << std::endl;
                    }
                    cout << endl;
                    // Printing longest paths in graph
                    this->print_longest_paths(fw_mat, is_double_directed);
                    cout << endl;
                    // Printing shortest paths in graph
                    this->print_shortest_paths(fw_mat, is_double_directed);
                    cout << endl;
                } else {
                    cout << "Sorry, nothing to see here!" << endl;
                    cout << "Floyd-Warshall runs with a time complexity of O(n^3) ";
                    cout << "therefore, on a graph of this size, it would take hours to run." << endl;
                    cout << "Try a smaller subset of data!" << endl;
                    cout << endl;
                }

                current_state = Current_State::MENU;
                break;
            }
            case Current_State::COMPLEXALG: {
                /************* COMPLEXALG OUTPUT HERE *************/
                cout << "********************************" << endl << "Complex Alg - IDDFS" << endl << endl;
                current_state = Current_State::MENU;
                //vector<int> trav;
                // if (vertices.size() > 5) {
                //     trav = iddfs(0, 6, 200);
                // } else {
                //     trav = iddfs(0, 3, 200);
                // }
                
                cout << "Vertices in graph:  ";
                //cout << int(vertices.size());
                for(unsigned i : vertices) {
                    cout << i << " ";
                }
                cout << endl;

                int start = -1;
                int end = -1;

                while (start == -1) {
                    cout << "**********************************" << endl << "What node do you want to start at?" << endl;
                    cin >> start;
                    if (cin.fail()) {
                        cout << endl << "sorry, you did not input an integer " << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        start = -1;
                    }
                    if (this->getOutgoingEdges(start).size() == 0) {
                        cout << endl << "sorry, that vertix doesn't exist " << endl << endl;
                        start = -1;
                    }
                }
                
                while (end == -1) {
                    cout << "********************************" << endl << "What node do you want to end at?" << endl;
                    cin >> end;
                    if (cin.fail()) {
                        cout << endl << "sorry, you did not input an integer " << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        end = -1;
                    }
                    if (this->getOutgoingEdges(end).size() == 0) {
                        cout << endl << "sorry, that vertix doesn't exist " << endl << endl;
                        end = -1;
                    }
                }
                cout << endl;

                vector<int> trav = iddfs(start, end, 20);

                cout << "**********************************" << endl;

                if(trav.size() == 0) {
                    cout << "No path found. ";
                } else {
                    cout << "Path from Vertex " << start << " to Vertex " << end << " :  ";
                    for(int i : trav) {
                        cout << i << " ";
                    }
                }
                cout << endl << endl;
                
                break;
            }
            case Current_State::TIMECOMPLEXITY: {
                cout << "********************************" << endl << "Checking Traversal Run Times" << endl << endl;
                current_state = Current_State::MENU;

                // INITIALIZING VARIABLES FOR TRAVERSALS
                vector<int> path, traversal;
                vector<bool> visited;
                for (size_t i = 0; i < this->getSize(); i++) visited.push_back(false);

                // calculate time function takes for BFS
                cout << "Time to run BFS: ";
                auto t1 = std::chrono::high_resolution_clock::now();
                path = this->BFS(0, * this);
                auto t2 = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
                cout << duration << " microseconds" << endl;

                // calculate time function take for DFS
                cout << "Time to run DFS: ";
                t1 = std::chrono::high_resolution_clock::now();
                this->DFS(0, * this, visited, traversal);
                t2 = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
                cout << duration << " microseconds" << endl;

                cout << endl << "********************************" << endl << "Checking Search Run Times" << endl << endl;

                //  Initialize start and end for search
                int start = -1, end = -1;

                // Select start value
                while (start == -1) {
                    cout << "**********************************" << endl << "What node do you want to start at?" << endl;
                    cin >> start;
                    if (cin.fail()) {
                        cout << endl << "sorry, you did not input an integer " << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        start = -1;
                    }
                    if (this->getOutgoingEdges(start).size() == 0) {
                        cout << endl << "sorry, that vertix doesn't exist " << endl << endl;
                        start = -1;
                    }
                }
                
                // Select end value
                while (end == -1) {
                    cout << "********************************" << endl << "What node do you want to end at?" << endl;
                    cin >> end;
                    if (cin.fail()) {
                        cout << endl << "sorry, you did not input an integer " << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        end = -1;
                    }
                    if (this->getOutgoingEdges(end).size() == 0) {
                        cout << endl << "sorry, that vertix doesn't exist " << endl << endl;
                        end = -1;
                    }
                }

                // calculate time function takes for BFS Search
                cout << endl << "Time to run BFS Search: ";
                t1 = std::chrono::high_resolution_clock::now();
                path = this->Search_BFS(start, end, * this);
                t2 = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
                cout << duration << " microseconds" << endl;

                // calculate time function take for DFS Search
                cout << "Time to run DFS Search: ";
                t1 = std::chrono::high_resolution_clock::now();
                this->Search_DFS(start, end, * this, visited, traversal);
                t2 = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
                cout << duration << " microseconds" << endl;

                // calculate time function take for IDDFS
                cout << "Time to run IDDFS: ";
                t1 = std::chrono::high_resolution_clock::now();
                vector<int> trav = iddfs(start, end, vertices.size());
                t2 = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
                cout << duration << " microseconds" << endl << endl;
                break;
            }
            case Current_State::QUIT: {
                goto END;
                break;
            }
        }
        goto LOOP;
    }
    END:
        cout << "**********************************" << endl;
        cout << "*    Thank you for your time!    *" << endl;
        cout << "**********************************" << endl;
}