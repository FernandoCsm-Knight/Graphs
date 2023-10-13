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
#include <fstream>
#include <stdexcept>

#include "datastructs/ArrayList.hpp"
#include "datastructs/Map.hpp"
#include "datastructs/Queue.hpp"
#include "datastructs/Set.hpp"
#include "datastructs/PriorityQueue.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Pair.hpp"
#include "helpers/Path.hpp"
#include "helpers/Vertex.hpp"

/**
 * @brief Represents a graph data structure.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Graph {
    private:
        Map<V, Set<V>> adj; ///< The adjacency list of the graph.
        Set<Edge<V>> edges; ///< The edge list of the graph.
        bool isDig = false; ///< Indicates whether the graph is directed.

    public:
    
        // Constructors & Destructor
        Graph() {}

        Graph(bool isDirected): isDig(isDirected) {}

        Graph(Edge<V> edges[], int size, bool isDirected = false) {
            for (int i = 0; i < size; i++) 
                this->addEdge(edges[i]);

            isDig = isDirected;
        }

        Graph(const Graph<V>& other): adj(other.adj), edges(other.edges), isDig(other.isDig) {}

        ~Graph() {}

        // Operators

        Graph<V>& operator=(const Graph<V>& other) {
            if (this != &other) {
                adj = other.adj;
                edges = other.edges;
                isDig = other.isDig;
            }

            return *this;
        }

        // Inline Methods

        inline bool contains(const V& vertex) const { return adj.contains(vertex); }
        inline bool contains(const Edge<V>& edge) const { return edges.contains(edge); }
        inline bool contains(const V& src, const V& dest) const { return edges.contains(Edge<V>(src, dest, isDig)); }

        inline bool isEmpty() const { return adj.isEmpty(); }
        inline int size() const { return adj.size(); }
        inline int sizeEdges() const { return edges.size(); }

        // Other Methods

        void addVertex(const V& vertex) {
            if(!adj.contains(vertex)) 
                adj.put(vertex, Set<V>());
        }

        void removeVertex(const V& vertex) {
            if(adj.contains(vertex)) {
                Set<V> vertices = adj[vertex];
                adj.remove(vertex);

                if(!isDig) {
                    for(int i = 0; i < vertices.size(); i++) 
                        adj[vertices[i]].pop(vertex);
                } else {
                    ArrayList<V> keys = adj.keys();

                    for(int i = 0; i < keys.size(); i++) 
                        adj[keys[i]].pop(vertex);
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
            edges.add(edge);

            if(!isDig) adj[edge.getDestination()].add(edge.getSource());
        }

        void removeEdge(const V& src, const V& dest) {
            this->removeEdge(Edge<V>(src, dest, isDig));
        }

        void removeEdge(const Edge<V>& edge) {
            if(edges.contains(edge)) {
                adj[edge.getSource()].pop(edge.getDestination());
                edges.pop(edge);

                if(!isDig) adj[edge.getDestination()].pop(edge.getSource());
            }
        }

        int distance(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return 0;

            ArrayList<V> vertices = adj.keys();
            PriorityQueue<Pair<int, V>> queue;
            int distances[this->size()];
            bool visited[this->size()];

            for(int i = 0; i < this->size(); i++) {
                distances[i] = __INT32_MAX__;
                visited[i] = false;
            }

            distances[vertices.indexOf(src, true)] = 0;
            queue.push(Pair<int, V>(0, src));

            while(!queue.isEmpty()) {
                V w = queue.poll().second();
                int indexW = vertices.indexOf(w, true);

                visited[indexW] = true;
                for(V u : adj.get(w)) {
                    int indexU = vertices.indexOf(u, true);

                    if(!visited[indexU]) {
                        distances[indexU] = (distances[indexU] < distances[indexW] + 1) ? distances[indexU] : distances[indexW] + 1;
                        queue.push(Pair<int, V>(distances[indexU], u));
                    }
                }
            }

            int indexDest = vertices.indexOf(dest, true);
            return distances[indexDest] == __INT32_MAX__ ? -1 : distances[indexDest];
        }

        Path<V> shortestPaht(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return Path<V>();

            ArrayList<V> vertices = adj.keys();
            PriorityQueue<Pair<double, V>> queue;
            double distances[this->size()];
            bool visited[this->size()];
            V parents[this->size()];

            for(int i = 0; i < this->size(); i++) {
                distances[i] = __DBL_MAX__;
                visited[i] = false;
            }

            parents[vertices.indexOf(src, true)] = src;
            distances[vertices.indexOf(src, true)] = 0;
            queue.push(Pair<double, V>(0.0, src));

            while(!queue.isEmpty()) {
                V w = queue.poll().second();
                int indexW = vertices.indexOf(w, true);

                visited[indexW] = true;
                for(V u : adj.get(w)) {
                    int indexU = vertices.indexOf(u, true);
                    if(!visited[indexU]) {
                        if(distances[indexU] < distances[indexW] + weight(w, u)) {
                            distances[indexU] = distances[indexU];
                        } else {
                            parents[indexU] = w;
                            distances[indexU] = distances[indexW] + weight(w, u);
                        }

                        queue.push(Pair<double, V>(distances[indexU], u));
                    }
                }
            }

            int indexDest = vertices.indexOf(dest, true);
            if(distances[indexDest] == __DBL_MAX__)
                return Path<V>();


            Path<V> path;
            int index = indexDest;
            V tmp = parents[index];
            while(vertices[index] != tmp) {
                path.addParent(vertices[index]);
                index = vertices.indexOf(tmp, true);
                tmp = parents[index];
            }

            path.addParent(vertices[index]);
            path.setWeight(distances[indexDest]);
            return path;
        }

        double weight(const V& src, const V& dest) const {
            int idx = edges.search(Edge<V>(src, dest, isDig));
            if(idx == -1) throw std::invalid_argument("The given edge does not exist in the graph.");

            return edges.get(idx).getWeight();
        }

        void clear() {
            adj.clear();
            edges.clear();
        }

        // Output Methods

        void toJsonFile() const {
            std::ofstream file;
            file.open("graph.json");

            if(file.is_open()) {
                file << "[" << std::endl;
                file << "{" << std::endl << "\"Graph\": {" << std::endl;
                file << "\t\"isDirected\": " << (isDig ? "true" : "false") << "," << std::endl;
                file << "\t\"Adjacency List\": {" << std::endl;

                ArrayList<V> vertices = adj.keys();

                for(int i = 0; i < vertices.size(); i++) {
                    Set<V> set = adj.get(vertices[i]);
                    V* list = set.toVector();

                    file << "\t\t\"" << vertices[i] << "\": [";
                    
                    for(int i = 0; i < set.size(); i++) 
                        file << "\"" << list[i] << "\"" << ((i < set.size() - 1) ? ", " : "");

                    file << "]" << ((i < vertices.size() - 1) ? "," : "") << std::endl;
                }

                file << "\t}," << std::endl << "\t\"Edges\": {" << std::endl;

                Edge<V>* list = edges.toVector();
                for(int i = 0; i < edges.size(); i++) 
                    file << "\t\t\"" << list[i].getSource() << " -> " << list[i].getDestination() << "\": " << list[i].getWeight() << ((i < edges.size() - 1) ? "," : "") << std::endl;
                
                file << "\t}" << std::endl << "}" << std::endl << "}" << std::endl << "]" << std::endl;
            }

            file.close();
        }

        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            strm << graph.edges << std::endl;
            return strm << graph.adj << std::endl;
        }
};

#endif