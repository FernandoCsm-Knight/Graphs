/**
 * @file ShortestPath.hpp
 * @author Fernando Campos Silva Dal' Maria (farnandocsdm@gmail.com)
 * @brief A C++ implementation of algorithms to find the shortest path in a graph.
 * 
 * This class provides implementations of common shortest path algorithms, including
 * Dijkstra's algorithm, Bellman-Ford algorithm, and Floyd-Warshall algorithm. It can
 * handle both graphs with positive and negative edge weights.
 * 
 * @version 1.0.0
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/PriorityQueue.hpp"
#include "../helpers/Edge.hpp"
#include "../helpers/Path.hpp"

template <class V> class Graph;

/**
 * @brief A class that implements various shortest path algorithms.
 * 
 * This class provides implementations for finding the shortest path in a graph using 
 * Dijkstra's algorithm, Bellman-Ford algorithm, and Floyd-Warshall algorithm. It supports
 * graphs with positive and negative edge weights.
 * 
 * @tparam V The type of vertices in the graph.
 */
template <class V> class ShortestPath {
    private:
        const Set<Edge<V>> edges;        /**< The set of edges in the graph. */
        const Graph<V>& graph;           /**< A reference to the graph object. */

        /**
         * @brief Implements the Bellman-Ford algorithm to compute shortest paths.
         * 
         * The Bellman-Ford algorithm is used for graphs with negative edge weights. It iterates
         * through all edges multiple times to calculate the shortest path distances and update
         * the parent map to reconstruct the paths.
         * 
         * @param distances A map to store the shortest distances from the source to each vertex.
         * @param parents A map to store the parent of each vertex in the shortest path tree.
         */
        void bellmanFord(Map<V, double>& distances, Map<V, V>& parents) const {
            for(int i = 0; i < graph.size() - 1; ++i) {
                for(Edge<V> edge : edges) {
                    if(distances[edge.getSource()] + edge.getWeight() < distances[edge.getDestination()]) {
                        distances[edge.getDestination()] = distances[edge.getSource()] + edge.getWeight();
                        parents[edge.getDestination()] = edge.getSource();
                    }
                }
            }

            for(int i = 0; i < graph.size() - 1; ++i) {
                for(Edge<V> edge : edges) {
                    if(distances[edge.getSource()] + edge.getWeight() < distances[edge.getDestination()]) {
                        distances[edge.getDestination()] = -std::numeric_limits<double>::infinity();
                        parents[edge.getDestination()] = edge.getSource();
                    }
                }
            }
        }

        /**
         * @brief Implements Dijkstra's algorithm to compute shortest paths.
         * 
         * Dijkstra's algorithm is used for graphs with non-negative edge weights. It uses a
         * priority queue to efficiently compute the shortest paths from the source vertex to
         * all other vertices in the graph.
         * 
         * @param vertex The source vertex from which to calculate the shortest paths.
         * @param distances A map to store the shortest distances from the source to each vertex.
         * @param parents A map to store the parent of each vertex in the shortest path tree.
         */
        void dijkstra(const V& vertex, Map<V, double>& distances, Map<V, V>& parents) const {
            PriorityQueue<Pair<double, V>> queue;
            Set<V> visited;

            queue.push(Pair<double, V>(0.0, vertex));
            while(!queue.isEmpty()) {
                V w = queue.poll().second();

                visited.add(w);
                for(const V& u : graph[w]) {
                    if(!visited.contains(u)) {
                        if(distances[u] > distances[w] + graph.weight(w, u)) {
                            distances[u] = distances[w] + graph.weight(w, u);
                            parents[u] = w;
                        }

                        queue.push(Pair<double, V>(distances[u], u));
                    }
                }
            }
        }

    public: 
        /**
         * @brief Constructor for ShortestPath class.
         * 
         * Initializes the ShortestPath object with the given graph.
         * 
         * @param graph The graph for which to calculate shortest paths.
         */
        explicit ShortestPath(const Graph<V>& graph) : 
            edges(graph.setOfEdges()), 
            graph(graph) {}

        /**
         * @brief Implements Floyd-Warshall algorithm to compute all-pairs shortest paths.
         * 
         * The Floyd-Warshall algorithm is used to find shortest paths between all pairs of vertices.
         * It is efficient for dense graphs and supports graphs with negative edge weights.
         * 
         * @return Map<V, Map<V, double>> A map of maps representing the shortest distances between all pairs of vertices.
         */
        Map<V, Map<V, double>> floydWarshal() const {
            ArrayList<V> vertices = graph.vertices();
            Map<V, Map<V, double>> distances;

            for(const V& v : vertices) {
                for(const V& u : vertices) {
                    if(v == u) distances[v][u] = 0.0;
                    else distances[v][u] = std::numeric_limits<double>::infinity();
                } 
            }

            for(const Edge<V>& edge : edges) 
                distances[edge.getSource()][edge.getDestination()] = edge.getWeight();

            for(const V& w : vertices) {
                for(const V& v : vertices) {
                    for(const V& u : vertices) {
                        double len = distances[v][w] + distances[w][u];
                        if(len < distances[v][u]) distances[v][u] = len;
                    }
                }
            }

            return distances;
        }

        /**
         * @brief Computes the shortest path distance between two vertices.
         * 
         * This method calculates the shortest path distance between the given source and destination
         * vertices using a breadth-first search (BFS) approach.
         * 
         * @param src The source vertex.
         * @param dest The destination vertex.
         * @return int The shortest path distance between the source and destination, or -1 if no path exists.
         * @throws std::invalid_argument If either the source or destination vertex is not in the graph.
         */
        int distance(const V& src, const V& dest) const {
            if(!graph.contains(src) || !graph.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return 0;

            ArrayList<V> vertices = graph.vertices();
            PriorityQueue<Pair<int, V>> queue;
            Set<V> visited;

            Pair<int, V> pair(0, src);
            queue.push(pair);
            while(!queue.isEmpty() && pair.second() != dest) {
                pair = queue.poll();

                visited.add(pair.second());
                for(const V& u : graph[pair.second()]) 
                    if(!visited.contains(u)) 
                        queue.push(Pair<int, V>(pair.first() + 1, u));
            }

            return (pair.second() == dest) ? pair.first() : -1;
        }

        /**
         * @brief Finds the shortest path from a source vertex to all other vertices.
         * 
         * This method calculates the shortest paths from the given source vertex to all other vertices
         * in the graph, using either Dijkstra's algorithm or the Bellman-Ford algorithm, depending on
         * whether the graph contains negative edge weights.
         * 
         * @param vertex The source vertex.
         * @return Map<V, Path<V>> A map from each vertex to the corresponding shortest path from the source vertex.
         * @throws std::invalid_argument If the source vertex is not in the graph.
         */
        Map<V, Path<V>> shortestPath(const V& vertex) const {
            if(!graph.contains(vertex)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            bool hasNegativeWeight = false;
            for(int i = 0; i < edges.size() && !hasNegativeWeight; ++i) 
                hasNegativeWeight = edges.get(i).getWeight() < 0;

            ArrayList<V> vertices = graph.vertices();
            Map<V, double> distances;
            Map<V, V> parents;

            for(V v : vertices) distances[v] = std::numeric_limits<double>::infinity();

            distances[vertex] = 0;

            if(hasNegativeWeight) bellmanFord(distances, parents);
            else dijkstra(vertex, distances, parents);   
            
            Map<V, Path<V>> map;
            for(int i = 0; i < vertices.size(); ++i) {
                Path<V> path;
                path.setWeight(distances[vertices[i]]);

                V curr = vertices[i];
                while(parents.contains(curr)) {
                    path.addParent(curr);
                    curr = parents[curr];
                }

                if(path.size() > 0) path.addParent(curr);
                map.put(vertices[i], path);
            }
            
            return map;
        }
};

#endif