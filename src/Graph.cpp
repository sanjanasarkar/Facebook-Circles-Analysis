#include "Graph.h"

void Graph::__init(const vector<Edge>& edges, size_t num_nodes) {
    for (size_t i = 0; i < num_nodes; ++i) {
        vector<double> line(num_nodes, 0.0);
        matrix_.push_back(line);
    }

    for (Edge e : edges) {
        matrix_[e.start][e.end] = e.weight;
    }
}

Graph::Graph(const vector<string>& lines) {
    vector<Graph::Edge> edges;

    Vertex max_node = 0;
    for (size_t i = 0; i < lines.size()/2; ++i) {
        Graph::Edge edge(lines[2*i], lines[2*i + 1], 1);
        edges.push_back(edge);
        max_node = std::max(edge.maxVertex(), max_node);
    }

    __init(edges, max_node);
}

Graph::Graph(const vector<Edge>& edges, size_t num_nodes) {
    __init(edges, num_nodes);
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