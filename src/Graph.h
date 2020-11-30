#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

typedef size_t Vertex;

/** A simple directed graph, implemented via an Adjacency Matrix. */
class Graph {

    public:
        /**
         * Simple struct to contain the Edges.
         */
        struct Edge {
            Vertex start;
            Vertex end;
            double weight; // default of 1.0

            Edge(Vertex s, Vertex e) : start(s), end(e), weight(1.0) {}
            Edge(Vertex s, Vertex e, double w) : start(s), end(e), weight(w) {}
            Edge(string s, string e) : start(std::stoi(s)), end(std::stoi(e)), weight(1.0) {}
            Edge(string s, string e, double w) : start(std::stoi(s)), end(std::stoi(e)), weight(w) {}

            /**
             * Returns the Vertex of this Edge with greater index magnitude
             */
            Vertex maxVertex() { if (start >= end) return start; else return end; }

            friend std::ostream& operator<<(std::ostream& out, const Edge& e) {
                out << "{" << e.start << ", " << e.end << " : " << e.weight << "}";
                return out;
            }
            
            friend bool operator==(const Edge& a, const Edge& b) {
                return a.start == b.start && a.end == b.end && a.weight == b.weight;   
            }
        };

        /**
         * Constructs a Graph. Input should be one single integer n>=0, per line.
         * Each Edge is represented by the current line and the one following it - e.g. for [1, 2, 3, 2]
         * there is an Edge from 1->2 and an Edge from 3->2.
         */ 
        Graph(const vector<string>& lines);

        /**
         * Constructs a Graph. Input is a list of Edges, as well as the total number of nodes in the Graph.
         */
        Graph(const vector<Edge>& edges, size_t num_nodes);

        /**
         * Changes the weight of the given Edge to that of the Edge e. Can also be used to create new edges.
         */
        void changeWeight(const Edge& e);
        /**
         * Changes the weight of the Edge from start to end. Directional! Can also be used to create new edges.
         */
        void changeWeight(Vertex start, Vertex end, double weight);

        /**
         * Checks if the passed-in Edge exists. Directional!
         */
        bool areConnected(const Edge& e);
        /**
         * Checks if the edge exists from start to end. Directional!
         */
        bool areConnected(Vertex start, Vertex end);

        /**
         * Gets weight of Edge e, if it exists, else returns 0
         */
        double getWeight(const Edge& e);
        /**
         * Gets weight of the edge from start to end, if it exists, else returns 0
         */
        double getWeight(Vertex start, Vertex end);

        /**
         * Returns a Vector of the outgoing Edges from node start. Empty list if no edges, OR if start doesn't exist.
         */
        vector<Edge> getOutgoingEdges(Vertex start);

        /**
         * Returns a Vector of the incoming Edges to node start. Empty list if no edges, OR if end doesn't exist.
         */
        vector<Edge> getIncomingEdges(Vertex end);

        inline size_t getSize() { return matrix_.size(); }
        inline Vertex getMaxVertex() { return getSize(); }

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);

        friend bool operator==(const Graph& lhs, const Graph& rhs);
        inline friend bool operator!=(const Graph& lhs, const Graph& rhs) { return !(lhs == rhs); }

    private:
        vector<vector<double>> matrix_;

        void __init(const vector<Edge>& edges, size_t num_nodes);

};
