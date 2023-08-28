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
        Map<Vertex<V>, ArrayList<Vertex<V>>> adj;   ///< The adjacency list of the graph.
        bool isDig;                                 ///< Indicates whether the graph is directed.

        /**
         * @brief Removes an edge between two vertices.
         * 
         * @param srcVertex The source vertex of the edge.
         * @param destVertex The destination vertex of the edge.
         */
        void removeEdge(const Vertex<V>& srcVertex, const Vertex<V>& destVertex) {
            if(!this->isDig) {
                if(adj.contains(srcVertex)) adj[srcVertex].pop(destVertex, true);
                if(adj.contains(destVertex)) adj[destVertex].pop(srcVertex, true);
            } else if(adj.contains(srcVertex)) adj[srcVertex].pop(destVertex, true);
        }

    public: 

        /**
         * @brief Constructs a graph.
         * 
         * @param isDigraph True if the graph is directed, false for undirected (default).
         */
        Graph(bool isDigraph = false): isDig(isDigraph) {}
        
        /**
         * @brief Destroys the graph.
         */
        ~Graph() {}

        /**
         * @brief Adds an edge to the graph.
         * 
         * @param src The source vertex label.
         * @param dest The destination vertex label.
         * @param weight The weight of the edge (default is 0.0).
         */
        void addEdge(const V& src, const V& dest) {
            Vertex<V> srcVertex = Vertex(src);
            Vertex<V> destVertex = Vertex(dest);

            if(!this->isDig) {
                if(!adj[srcVertex].contains(destVertex))
                    adj[srcVertex].addInOrder(destVertex);

                if(!adj[destVertex].contains(srcVertex))
                    adj[destVertex].addInOrder(srcVertex);
            } else {
                if(!adj[srcVertex].contains(destVertex))
                    adj[srcVertex].addInOrder(destVertex);
            }
        }

        /**
         * @brief Removes an edge from the graph.
         * 
         * @param src The source vertex label.
         * @param dest The destination vertex label.
         */
        void removeEdge(const V& src, const V& dest) {
            this->removeEdge(Vertex(src), Vertex(dest));
        }

        /**
         * @brief Removes an edge from the graph.
         * 
         * @param edge The edge to be removed.
         */
        void removeEdge(const Edge<V>& edge) {
            this->removeEdge(edge.getSource(), edge.getDestination());
        }

        /**
         * @brief Adds a vertex to the graph.
         * 
         * @param label The label of the vertex to be added.
         */
        void addVertex(const V& label) {
            Vertex<V> ver = Vertex<V>(label);
            if(!adj.contains(ver)) adj[ver] = ArrayList<Vertex<V>>();
        }

        /**
         * @brief Removes a vertex and its associated edges from the graph.
         * 
         * @param label The label of the vertex to be removed.
         */
        void removeVertex(const V& label) {
            Vertex<V> ver = Vertex<V>(label);

            ArrayList<Vertex<V>> vertices = this->getVertices();
            ArrayList<ArrayList<Vertex<V>>> list = this->adj.values();
            for(int i = 0; i < list.size(); i++) 
                if(list[i].contains(ver))
                    this->adj[vertices[i]].pop(ver, true);

            this->adj.remove(ver);
        }

        /**
         * @brief Returns the number of vertices in the graph.
         * 
         * @return The number of vertices.
         */
        int size() const {
            return this->adj.size();
        }

        /**
         * @brief Checks if the graph is directed.
         * 
         * @return True if the graph is directed, false for undirected.
         */
        bool isDigraph() const {
            return this->isDig;
        }

        /**
         * @brief Computes the in-degree and out-degree of a vertex in a directed graph.
         * 
         * @param vertex The label of the vertex.
         * @return A pair containing the in-degree and out-degree of the vertex.
         */
        Pair<int, int> degree(const V& vertex) const {
            Vertex<V> ver = Vertex<V>(vertex);

            if(isDig) {
                ArrayList<ArrayList<Vertex<V>>> list = this->adj.values();

                int in = 0, 
                    out = this->adj.get(ver).size();
                
                for(int i = 0; i < list.size(); i++) 
                    if(list[i].contains(ver))
                        in++;
                
                return Pair<int, int>(in, out, true);
            }
                
            return Pair<int, int>(this->adj.get(ver).size());
        }

        /**
         * @brief Get the Edges of a vertex
         * 
         * @param label The label of the vertex.
         * @return ArrayList<Edge<V>> 
         */
        ArrayList<Edge<V>> getEdges(const V& label) const {
            ArrayList<Edge<V>> edges;
            Vertex<V> ver = Vertex<V>(label);

            for(int i = 0; i < this->adj.get(ver).size(); i++) {
                Edge<V> edge(ver, this->adj.get(ver)[i]);
                edge.setDirect(this->isDig);
                edges.add(edge);
            }

            return edges;
        }

        /**
         * @brief Get the Edges of a vertex
         * 
         * @param vertex The vertex.
         * @return ArrayList<Edge<V>> 
         */
        ArrayList<Edge<V>> getEdges(Vertex<V> vertex) const {
            return this->getEdges(vertex.getLabel());
        }

        /**
         * @brief Get the Vertices of the graph
         * 
         * @return ArrayList<Vertex<V>> 
         */
        ArrayList<Vertex<V>> getVertices() const {
            return this->adj.keys();
        }

        /**
         * @brief Get the degree list of the graph
         * 
         * @return ArrayList<Pair<int, int>> The degree list of the graph
         */
        ArrayList<Pair<int, int>> degreeList() const {
            ArrayList<Vertex<V>> keys = this->adj.keys();
            ArrayList<Pair<int, int>> degreeList;

            for(int i = 0; i < keys.size(); i++)
                degreeList.addInOrder(degree(keys.get(i).getLabel()));

            return degreeList;
        }

        /**
         * @brief Get the adjacent list of the graph
         * 
         * @return Map<Vertex<V>, ArrayList<Vertex<V>>> The adjacent list of the graph
         */
        Map<Vertex<V>, ArrayList<Vertex<V>>> adjacentList() const {
            return this->adj;
        }

        /**
         * @brief Clear the graph.
         */
        void clear() {
            adj.clear();
        }

        /**
         * @brief Clear the edges of the graph.
         */
        void clearEdges() {
            adj.clearValues();
        }

        /**
         * @brief Overloaded stream insertion operator to print the graph's information.
         * 
         * @param strm The output stream.
         * @param graph The graph to be printed.
         * @return The output stream after printing the graph.
         */
        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            ArrayList<Vertex<V>> keys = graph.map.keys();
            ArrayList<ArrayList<Edge<V>>> values = graph.map.values();

            for(int i = 0; i < keys.size(); i++) {
                strm << keys[i] << ": " << values[i] << std::endl;
            } 

            return strm;
        }
};

/**
 * @brief Determines if a graph is complete.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to be tested.
 * @return True if the graph is complete, false otherwise.
 */
template <class V> bool isComplete(const Graph<V>& graph) {
    int expectedEdges = graph.size() - 1;
    ArrayList<Pair<int, int>> list = graph.degreeList();

    bool eq = !list.isEmpty();
    for(int i = 0; eq && i < list.size(); i++) {
        if(graph.isDigraph()) 
            eq = list[i].first() == expectedEdges && list[i].second() == expectedEdges;
        else 
            eq = list[i].first() == expectedEdges;
    }

    return eq;
}

/**
 * @brief Determines if a graph is regular.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to be tested.
 * @return True if the graph is regular, false otherwise.
 */
template <class V> bool isRegular(const Graph<V>& graph) {
    ArrayList<Pair<int, int>> degreeList = graph.degreeList();

    bool eq = !degreeList.isEmpty();
    for(int i = 0; eq && i < degreeList.size(); i++) 
        eq = degreeList[i] == degreeList[0];
    
    return eq;
}

/**
 * @brief Determines if a graph is bipartite.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to be tested.
 * @return True if the graph is bipartite, false otherwise.
 */
template <class V> bool isBipartite(const Graph<V>& graph) {
    ArrayList<Vertex<V>> vertices = graph.getVertices();
    Map<Vertex<V>, bool> color;

    for(int i = 0; i < vertices.size(); i++) {
        if(!color.contains(vertices[i])) {
            color[vertices[i]] = false;
            Queue<Vertex<V>> queue;
            queue.push(vertices[i]);

            while(!queue.isEmpty()) {
                Vertex<V> vertex = queue.pop();
                ArrayList<Edge<V>> edges = graph.getEdges(vertex);

                for(int j = 0; j < edges.size(); j++) {
                    Vertex<V> dest = edges[j].srcDest(vertex);
                    if(!color.contains(dest)) {
                        color[dest] = !color[vertex];
                        queue.push(dest);
                    } else if(color[dest] == color[vertex]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

#endif