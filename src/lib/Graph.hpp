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
        Map<Vertex<V>, ArrayList<Vertex<V>>> adj; ///< The adjacency list of the graph.
        Map<Vertex<V>, ArrayList<Edge<V>>> map; ///< The map of vertices to their associated edges.
        bool isDig; ///< Indicates whether the graph is directed.

        /**
         * @brief Removes an edge between two vertices.
         * 
         * @param srcVertex The source vertex of the edge.
         * @param destVertex The destination vertex of the edge.
         */
        void removeEdge(Vertex<V> srcVertex, Vertex<V> destVertex) {
            Edge<V> edge = Edge<V>(srcVertex, destVertex);
            edge.setDirect(this->isDig);

            if(!this->isDig) {
                Edge<V> edge2 = Edge<V>(destVertex, srcVertex);
                if(map.contains(srcVertex)) {
                    if(map[srcVertex].contains(edge)) map[srcVertex].pop(edge, true);
                    else map[srcVertex].pop(edge2, true);
                }

                if(map.contains(destVertex)) {
                    if(map[destVertex].contains(edge)) map[destVertex].pop(edge, true);
                    else map[destVertex].pop(edge2, true);
                }

                if(adj.contains(srcVertex)) adj[srcVertex].pop(destVertex, true);
                if(adj.contains(destVertex)) adj[destVertex].pop(srcVertex, true);
            } else {
                if(map.contains(srcVertex)) map[srcVertex].pop(edge, true);
                if(adj.contains(srcVertex)) adj[srcVertex].pop(destVertex, true);
            }
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
        void addEdge(V src, V dest, double weight = 0.0) {
            Vertex<V> srcVertex = Vertex(src);
            Vertex<V> destVertex = Vertex(dest);

            Edge<V> edge = Edge<V>(srcVertex, destVertex, weight);
            Edge<V> edge2 = Edge<V>(destVertex, srcVertex, weight);
            edge.setDirect(this->isDig);
            edge2.setDirect(this->isDig);

            if(!this->isDig) {
                if(!map[srcVertex].contains(edge) && !map[srcVertex].contains(edge2))
                    map[srcVertex].addInOrder(edge);
                
                if(!map[destVertex].contains(edge) && !map[destVertex].contains(edge2))
                    map[destVertex].addInOrder(edge);
                
                if(!adj[srcVertex].contains(destVertex))
                    adj[srcVertex].addInOrder(destVertex);

                if(!adj[destVertex].contains(srcVertex))
                    adj[destVertex].addInOrder(srcVertex);
            } else {
                if(!map[srcVertex].contains(edge))
                    map[srcVertex].addInOrder(edge);
                
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
        void removeEdge(V src, V dest) {
            this->removeEdge(Vertex(src), Vertex(dest));
        }

        /**
         * @brief Adds a vertex to the graph.
         * 
         * @param vertex The label of the vertex to be added.
         */
        void addVertex(V vertex) {
            Vertex<V> ver = Vertex<V>(vertex);
            if(!map.contains(ver)) map[ver] = ArrayList<Edge<V>>();
            if(!adj.contains(ver)) adj[ver] = ArrayList<Vertex<V>>();
        }

        /**
         * @brief Removes a vertex and its associated edges from the graph.
         * 
         * @param vertex The label of the vertex to be removed.
         */
        void removeVertex(V vertex) {
            Vertex<V> ver = Vertex<V>(vertex);

            ArrayList<Edge<V>> edges = map[ver];
            for(int i = 0; i < edges.size(); i++) 
                removeEdge(edges[i].getSource(), edges[i].getDestination());

            map.remove(ver);
            adj.remove(ver);
        }

        /**
         * @brief Returns the number of vertices in the graph.
         * 
         * @return The number of vertices.
         */
        int size() const {
            return map.size();
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
        Pair<int, int> degree(V vertex) const {
            Vertex<V> ver = Vertex<V>(vertex);
            if(isDig) {
                int in = 0, out = 0;
                for(int i = 0; i < map.get(ver).size(); i++) {
                    if(map.get(ver)[i].isDirect()) {
                        if(map.get(ver)[i].getSource() == ver) out++;
                        else in++;
                    } else {
                        in++;
                        out++;
                    }
                }
                return Pair<int, int>(in, out, true);
            } else {
                return Pair<int, int>(map.get(ver).size());
            }
        }

        /**
         * @brief Get the Edges of a vertex
         * 
         * @param vertex The label of the vertex.
         * @return ArrayList<Edge<V>> 
         */
        ArrayList<Edge<V>> getEdges(V vertex) const {
            return map.get(Vertex<V>(vertex));
        }

        /**
         * @brief Get the Edges of a vertex
         * 
         * @param vertex The vertex.
         * @return ArrayList<Edge<V>> 
         */
        ArrayList<Edge<V>> getEdges(Vertex<V> vertex) const {
            return map.get(vertex);
        }

        /**
         * @brief Get the Vertexes of the graph
         * 
         * @return ArrayList<Vertex<V>> 
         */
        ArrayList<Vertex<V>> getVertexes() const {
            return map.keys();
        }

        /**
         * @brief Get the degree list of the graph
         * 
         * @return ArrayList<Pair<int, int>> The degree list of the graph
         */
        ArrayList<Pair<int, int>> degreeList() const {
            ArrayList<Vertex<V>> keys = map.keys();
            ArrayList<ArrayList<Edge<V>>> values = map.values();

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
            return adj;
        }

        /**
         * @brief Clear the graph.
         */
        void clear() {
            map.clear();
            adj.clear();
        }

        /**
         * @brief Clear the edges of the graph.
         */
        void clearEdges() {
            map.clearValues();
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
            eq = list[i].first() + list[i].second() == expectedEdges;
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
    ArrayList<Vertex<V>> vertexes = graph.getVertexes();
    Map<Vertex<V>, bool> color;

    for(int i = 0; i < vertexes.size(); i++) {
        if(!color.contains(vertexes[i])) {
            color[vertexes[i]] = false;
            Queue<Vertex<V>> queue;
            queue.push(vertexes[i]);

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