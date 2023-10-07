/**
 * @file Graph.hpp
 * @author Fernando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementation of a Graph class, a templated container that represents a graph data structure.
 *        The class allows associating a vertex label of type V with a corresponding list of adjacent vertices.
 *        It provides multiple constructors for creating graphs, including default and directed constructors.
 *        Additionally, the class overloads the stream insertion operator to print the graph's information.
 *        The class is designed to be used in data structures and algorithms that require storing and managing
 *        graphs efficiently.
 * @version 1.0.0
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "Map.hpp"
#include "Queue.hpp"
#include "Set.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Pair.hpp"
#include "helpers/Vertex.hpp"

/**
 * @brief Represents a graph data structure.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Graph {
    private:
        Map<Vertex<V>, Set<Vertex<V>>> adj; ///< The adjacency list of the graph.
        Map<Vertex<V>, Set<Edge<V>>> edges; ///< The edge list of the graph.
        bool isDig = false; ///< Indicates whether the graph is directed.

    public:
        Graph() {}

        Graph(bool isDirected): isDig(isDirected) {}

        Graph(Edge<V> edges[], int size, bool isDirected = false) {
            for (int i = 0; i < size; i++) 
                this->addEdge(edges[i]);

            isDig = isDirected;
        }

        Graph(const Graph<V>& other): adj(other.adj), edges(other.edges), isDig(other.isDig) {}

        ~Graph() {}

        Graph<V>& operator=(const Graph<V>& other) {
            if (this != &other) {
                adj = other.adj;
                edges = other.edges;
                isDig = other.isDig;
            }

            return *this;
        }

        void addVertex(const V& vertex) {
            this->addVertex(Vertex<V>(vertex));
        }

        void addVertex(const Vertex<V>& vertex) {
            if(!adj.contains(vertex)) {
                adj.put(vertex, Set<Vertex<V>>());
                edges.put(vertex, Set<Edge<V>>());
            }
        }

        void removeVertex(const V& vertex) {
            this->removeVertex(Vertex<V>(vertex));
        }

        void removeVertex(const Vertex<V>& vertex) {
            if(adj.contains(vertex)) {
                Set<Vertex<V>> vertices = adj[vertex];

                adj.remove(vertex);
                edges.remove(vertex);

                if(!isDig) {
                    for(int i = 0; i < vertices.size(); i++) {
                        adj[vertices[i]].pop(vertex);
                        edges[vertices[i]].pop(Edge<V>(vertex, vertices[i]));
                    }
                } else {
                    ArrayList<Vertex<V>> keys = adj.keys();

                    for(int i = 0; i < keys.size(); i++) {
                        adj[keys[i]].pop(vertex);
                        edges[keys[i]].pop(Edge<V>(vertex, keys[i]));
                        edges[keys[i]].pop(Edge<V>(keys[i], vertex));
                    }
                }
            }
        }

        void addEdge(const V& src, const V& dest, double weight = 0.0) {
            this->addEdge(Edge<V>(src, dest, isDig, weight));
        }

        void addEdge(const Edge<V>& edge) {
            this->addVertex(edge.getSource());
            this->addVertex(edge.getDestination());

            adj[edge.getSource()].add(edge.getDestination());
            edges[edge.getSource()].add(edge);

            if(!isDig) {
                adj[edge.getDestination()].add(edge.getSource());
                edges[edge.getDestination()].add(edge);
            }
        }

        void removeEdge(const V& src, const V& dest) {
            this->removeEdge(Edge<V>(src, dest, isDig));
        }

        void removeEdge(const Edge<V>& edge) {
            if(adj.contains(edge.getSource())) {
                adj[edge.getSource()].pop(edge.getDestination());
                edges[edge.getSource()].pop(edge);

                if(!isDig) {
                    adj[edge.getDestination()].pop(edge.getSource());
                    edges[edge.getDestination()].pop(edge);
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            strm << graph.edges;
            return strm << graph.adj;
        }
};



#endif