#include <iostream>

#include "Graph.h"

void Graph::__init(const vector<Edge>& edges, size_t num_nodes, bool double_directed) {
    matrix_.clear();
    for (size_t i = 0; i < num_nodes; ++i) {
        vector<double> line(num_nodes, 0.0);
        matrix_.push_back(line);
    }

    for (Edge e : edges) {
        matrix_[e.start][e.end] = e.weight; 

        if (double_directed)
            matrix_[e.end][e.start] = e.weight;
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

vector<int> Graph::iddfs(int start, int end, int max_depth, const Graph& g) {
    for (int i = 0; i < max_depth; i++) {
        vector<int> trav;
        vector<int> reverse;
        if (dls(start, end, i, trav, g)) {
            for (int i = int(trav.size())-1; i >= 0 ; i--) {
                reverse.push_back(trav[i]);
            }
            return reverse;
        }
    }
    return vector<int>();
}

bool Graph::dls(int start, int end, int limit, vector<int> &path, const Graph& g) {
    if (start == end) {
        path.push_back(start);
        return true;
    }

    if (limit <= 0) {
        return false;
    }

    vector<Graph::Edge> adj = getOutgoingEdges(start);
    for (unsigned i = 0; i < adj.size(); i++) {
        if (dls(adj[i].end, end, limit-1, path, g)) {
            path.push_back(start);
            return true;
        }
    }

    return false;
}

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

    // return dfsTraversal;
}

    // // Print all paths
	// cout << "All Pairs Shortest Paths : \n\n";
	// for (i = 0; i < num_vertices; i++)
	// {
	// 	cout << endl;
	// 	for (j=0; j<num_vertices; j++)
	// 	{
	// 		cout << "From : " << i+1 << " To : " << j+1 << endl;
	// 		cout << "Path : " << 1+i << obtainPath(i,j) << j+1 << endl;
	// 		cout << "Distance : " << floyd_warsh_matrix[i][j].getWeight() << endl << endl;
	// 	}
	// }
vector<vector<double>> Graph::FloydWarshall(const Graph& g) {
    int INFINITY = __INT_MAX__;
    int num_vertices = g.getSize();
    vector<vector<double>> floyd_warsh_matrix;
    
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