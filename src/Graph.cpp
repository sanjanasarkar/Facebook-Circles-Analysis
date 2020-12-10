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
    return floyd_warsh_matrix; 
}
