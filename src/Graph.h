#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

typedef int Vertex;

// A simple undirected graph
class Graph {

    public:
        struct Edge {
            Vertex start;
            Vertex end;
            double weight; // default of 1.0

            Edge(Vertex s, Vertex e) : start(s), end(e), weight(1.0) {}
            Edge(Vertex s, Vertex e, double w) : start(s), end(e), weight(w) {}
            Edge(string s, string e) : start(std::stoi(s)), end(std::stoi(e)), weight(1.0) {}
            Edge(string s, string e, double w) : start(std::stoi(s)), end(std::stoi(e)), weight(w) {}

            Vertex maxVertex() { if (start >= end) return start; else return end; }

            friend std::ostream& operator<<(std::ostream& out, const Edge& e) {
                out << "{" << e.start << ", " << e.end << " : " << e.weight << "}";
                return out;
            }
        };

        Graph(vector<Edge>& edges, size_t num_nodes);

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);

    private:
        vector<vector<double>> matrix_;

};