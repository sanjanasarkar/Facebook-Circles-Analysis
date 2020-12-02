#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <iterator>

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
            /**
             * Vertex which this Edge starts from
             */
            Vertex start;

            /**
             * Vertex which this Edge ends at
             */
            Vertex end;

            /**
             * Weight of this Edge. Default of 1.0.
             */
            double weight;

            /**
             * Construct a new Edge object
             * 
             * @param s Starting vertex
             * @param e Ending vertex
             */
            Edge(Vertex s, Vertex e) : start(s), end(e), weight(1.0) {}
            /**
             * @brief Construct a new Edge object
             * 
             * @param s Starting vertex
             * @param e Ending vertex
             * @param w Weight of Edge
             */
            Edge(Vertex s, Vertex e, double w) : start(s), end(e), weight(w) {}
            /**
             * @brief Construct a new Edge object
             * 
             * @param s String representation of starting Vertex
             * @param e String representation of ending Vertex
             */
            Edge(string s, string e) : start(std::stoi(s)), end(std::stoi(e)), weight(1.0) {}
            /**
             * @brief Construct a new Edge object
             * 
             * @param s String representation of starting Vertex
             * @param e String representation of ending Vertex
             * @param w Weight of Edge
             */
            Edge(string s, string e, double w) : start(std::stoi(s)), end(std::stoi(e)), weight(w) {}

            /**
             * Determines which Vertex, start or end, has greater magnitude
             * 
             * @return Vertex of this Edge with greater index magnitude 
             */
            Vertex maxVertex() const { if (start >= end) return start; else return end; }

            /**
             * Insertion operator for output
             * 
             * @param out ostream ref for operator chaining
             * @param e edge to insert
             * @return std::ostream& for operator chaining
             */
            friend std::ostream& operator<<(std::ostream& out, const Edge& e) {
                out << "{" << e.start << ", " << e.end << " : " << e.weight << "}";
                return out;
            }
            
            friend bool operator==(const Edge& a, const Edge& b) {
                return a.start == b.start && a.end == b.end && a.weight == b.weight;   
            }
        };

        /**
         * @brief Construct a new Graph object
         * 
         * @param lines String vector. Should be one single integer n>=0, per line.
         * Each Edge is represented by the current line and the one following it - e.g. for [1, 2, 3, 2]
         * there is an Edge from 1->2 and an Edge from 3->2.
         */
        Graph(const vector<string>& lines);

        /**
         * @brief Construct a new Graph object
         * 
         * @param edges Vector of Edges to add
         * @param num_nodes Total number of nodes/vertices in the graph
         */
        Graph(const vector<Edge>& edges, size_t num_nodes);

        /**
         * @brief Changes the weight of the Edge with e's start and end to the weight in e
         * 
         * @param e Edge containing the start, end, and weight
         */
        void changeWeight(const Edge& e);
        
        /**
         * @brief Changes the weight of the Edge from start to end. Directional!
         * Can also be used to create new Edges.
         * 
         * @param start Starting Vertex of edge to set
         * @param end Ending Vertex of edge to set
         * @param weight Weight to set
         */
        void changeWeight(Vertex start, Vertex end, double weight);

        /**
         * @brief Checks if the given Edge exists. Ignores weight of e.
         * 
         * @param e Edge to check
         * @return true if the Edge exists in this Graph, else false
         */
        bool areConnected(const Edge& e) const;

        /**
         * @brief Checks if the edge exists from start to end. Directional!
         * 
         * @param start Starting vertex
         * @param end Ending vertex
         * @return true if Edge exists, else false
         */
        bool areConnected(Vertex start, Vertex end) const;

        /**
         * @brief Gets the Weight of Edge e
         * 
         * @param e Edge to check
         * @return double weight of Edge, or 0 if the Edge does not exist
         */
        double getWeight(const Edge& e) const;

        /**
         * @brief Get the Weight of Edge e
         * 
         * @param start Starting vertex
         * @param end Ending vertex
         * @return double weight of Edge, or 0 if the Edge does not exist
         */
        double getWeight(Vertex start, Vertex end) const;
        
        /**
         * @brief Get the outgoing edges FROM a Vertex
         * 
         * @param start Vertex to check 
         * @return vector<Edge> of all outgoing Edges from Start if it exists, else empty vector
         */
        vector<Edge> getOutgoingEdges(Vertex start) const;

        /**
         * @brief Get the incoming edges TO a Vertex
         * 
         * @param end Vertex to check
         * @return vector<Edge> of all incoming Edges to End if it exists, else empty vector
         */
        vector<Edge> getIncomingEdges(Vertex end) const;

        /**
         * @brief Get the Size of the Graph. Equivalent to getMaxVertex().
         * 
         * @return size_t Size of graph
         */
        inline size_t getSize() const { return matrix_.size(); }

        /**
         * @brief Get the Max Vertex object Equivalent to getSize().
         * 
         * @return Vertex Maximum Vertex magnitude
         */
        inline Vertex getMaxVertex() const { return getSize(); }

        /**
         * @brief Insertion operator to print the Adjacency Matrix.
         * 
         * @param out ostream ref for operator chaining
         * @param g Graph to output
         * @return std::ostream& ostream ref for operator chaining
         */
        friend std::ostream& operator<<(std::ostream& out, const Graph& g);

        /**
         * @brief Equality checking operator. Compares the adjacency matrices, entry by entry.
         * 
         * @param lhs First Graph
         * @param rhs Second Graph
         * @return true if adjacency matrices are the same
         * @return false if not
         */
        friend bool operator==(const Graph& lhs, const Graph& rhs);

        /**
         * @brief Inequality operator. Logical inverse of operator==
         * 
         * @param lhs First Graph
         * @param rhs Second Graph
         * @return true if the adjacency matrices are NOT the same
         * @return false otherwise
         */
        inline friend bool operator!=(const Graph& lhs, const Graph& rhs) { return !(lhs == rhs); }
 
        /**
         * @brief Get a const reference of the Adjacency Matrix. Const ref to avoid extra copy
         * 
         * @return const vector<vector<double>>& Constant reference to the matrix
         */
        inline const vector<vector<double>>& getAdjacencyMatrix() const { return matrix_; }

        vector<int> BFS(int start, const Graph& g);

    private:
        /**
         * @brief Adjacency matrix
         */
        vector<vector<double>> matrix_;

        /**
         * @brief Helper function for both constructors. Creates the Adjacency Matrix.
         * 
         * @param edges Edges vector list
         * @param num_nodes Total number of nodes
         */
        void __init(const vector<Edge>& edges, size_t num_nodes);

};
