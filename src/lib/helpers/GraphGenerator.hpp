/**
 * @file GraphGenerator.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A class that generates graphs of different types.
 * @version 1.0.0
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <stdexcept>
#include "Arithmatic.hpp"
#include "../Graph.hpp"
#include "../types/Numeric.hpp"
#include "../types/GraphTypes.hpp"

template <typename T> class Graph;

template <art::Numeric T> class GraphGenerator {
    public:
        /**
         * @brief Generates a regular graph. The regular graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param k the degree of each vertex in the graph.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> regular(int n, int k, bool directed = false) {
            if (n <= 0 || k <= 0 || k >= n) {
                throw std::invalid_argument("Invalid parameters for regular graph.");
            }

            Graph<T> graph(directed);
            for (int i = 0; i < n; ++i) {
                for (int j = 1; j <= k / 2; ++j) {
                    int dest = (i + j) % n;
                    graph.addEdge(i, dest);
                }
            }
            return graph;
        }

        /**
         * @brief Generates a complete graph. The complete graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> complete(int n, bool directed = false) {
            if (n <= 0) {
                throw std::invalid_argument("Invalid parameter for complete graph.");
            }

            Graph<T> graph(directed);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i != j) {
                        graph.addEdge(i, j);
                    }
                }
            }
            return graph;
        }

        /**
         * @brief Generates a bipartite graph. The bipartite graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n1 the number of vertices in the first partition.
         * @param n2 the number of vertices in the second partition.
         * @param p the probability of an edge between the two partitions.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> bipartite(int n1, int n2, double p, bool directed = false) {
            if (n1 <= 0 || n2 <= 0 || p < 0 || p > 1) {
                throw std::invalid_argument("Invalid parameters for bipartite graph.");
            }

            Graph<T> graph(directed);
            for (int i = 0; i < n1; ++i) {
                for (int j = n1; j < n1 + n2; ++j) {
                    if ((double)rand() / RAND_MAX <= p) {
                        graph.addEdge(i, j);
                    }
                }
            }
            return graph;
        }

        /**
         * @brief Generates a complete bipartite graph. The complete bipartite graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n1 the number of vertices in the first partition.
         * @param n2 the number of vertices in the second partition.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> completeBipartite(int n1, int n2, bool directed = false) {
            if (n1 <= 0 || n2 <= 0) {
                throw std::invalid_argument("Invalid parameters for complete bipartite graph.");
            }

            Graph<T> graph(directed);
            for (int i = 0; i < n1; ++i) {
                for (int j = n1; j < n1 + n2; ++j) {
                    graph.addEdge(i, j);
                }
            }
            return graph;
        }

        /**
         * @brief Generates an Eulerian graph. The Eulerian graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> eulerian(int n, bool directed = false) {
            if (n <= 0 || n % 2 != 0) 
                throw std::invalid_argument("Invalid parameter for Eulerian graph.");

            Graph<T> graph(directed);
            for (int i = 0; i < n; ++i) 
                graph.addEdge(i, (i + 1) % n);

            for (int i = 0; i < n; i += 2) 
                graph.addEdge(i, (i + 2) % n);

            return graph;
        }

        /**
         * @brief Generates a tree graph. The tree graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param isDirected indicates whether the graph is directed or undirected.
         * @return Graph<T> the generated graph.
         */
        Graph<T> tree(int n, bool isDirected = false) {
            if (n <= 0) {
                throw std::invalid_argument("Invalid parameter for tree graph.");
            }

            Graph<T> graph(isDirected);
            for (int i = 1; i < n; ++i) {
                int parent = rand() % i;
                graph.addEdge(parent, i);
            }
            return graph;
        }

        /**
         * @brief Generates a forest graph. The forest graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param numTrees the number of trees in the forest.
         * @param isDirected indicates whether the graph is directed or undirected.
         * @return Graph<T> the generated graph.
         */
        Graph<T> forest(int n, int numTrees, bool isDirected = false) {
            if (n <= 0 || numTrees <= 0 || numTrees > n) {
                throw std::invalid_argument("Invalid parameters for forest graph.");
            }

            Graph<T> graph(isDirected);
            std::vector<int> roots(numTrees);
            for (int i = 0; i < numTrees; ++i) {
                roots[i] = i;
                graph.addVertex(i);
            }

            for (int i = numTrees; i < n; ++i) {
                int parent = roots[rand() % numTrees];
                graph.addEdge(parent, i);
                roots.push_back(i);
            }
            return graph;
        }

        /**
         * @brief Generates a cyclic graph. The cyclic graph will only be generated
         * if the graph type is Numeric.
         * 
         * @param n the number of vertices in the graph.
         * @param directed whether the graph is directed or not.
         * @return Graph<T> the generated graph.
         */
        Graph<T> cyclic(int n, bool directed = false) {
            if (n <= 0) {
                throw std::invalid_argument("Invalid parameter for cyclic graph.");
            }

            Graph<T> graph(directed);
            for (int i = 0; i < n; ++i) {
                graph.addEdge(i, (i + 1) % n);
            }
            return graph;
        }
};

#endif