/**
 * @file GraphDescriber.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A class that describes a graph by its properties.
 * @version 0.1
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GRAPH_DESCRIBER_HPP
#define GRAPH_DESCRIBER_HPP

#include <string>

#include "../Graph.hpp"
#include "../datastructs/ArrayList.hpp"
#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/Stack.hpp"
#include "../datastructs/UnionFind.hpp"
#include "../helpers/Pair.hpp"

template <typename V> class Graph;

/**
 * @brief GraphDescriber class describes a graph or a digraph by the following properties:
 * 
 * - Regular: A graph is regular if all vertices have the same degree.
 * - Complete: A graph is complete if all vertices are connected to all other |V| - 1 vertices.
 * - Bipartite: A graph is bipartite if it can be colored with two colors such that no two adjacent vertices have the same color.
 * - Tree: A graph is a tree if it is connected and has |V| - 1 edges.
 * - Forest: A graph is a forest if it is connected and has |V| - cc edges, where cc is the number of connected components.
 * - Cyclic: A graph is cyclic if it contains a cycle.
 * - Eulerian: A graph is Eulerian if it has either 0 or 2 vertices with odd degree.
 * 
 * @tparam V 
 */
template <typename V> class GraphDescriber {
    private:
        const Graph<V>& graph; ///< The graph to describe.

    public:
        /**
         * @brief Construct a new GraphDescriber object.
         * 
         * @param graph the graph to describe.
         */
        explicit GraphDescriber(const Graph<V>& graph): graph(graph) {}

        /**
         * @brief Describe if the graph is regular.
         * 
         * @return true if the graph is regular, false otherwise.
         */
        bool isRegular() const {
            ArrayList<Pair<int, int>> list = graph.degreeList();

            bool value = true;
            if(!graph.isDigraph()) {
                for(int i = 0; i < list.size() && value; ++i) 
                    value = list[i].first() == list[0].first();
            } else {
                for(int i = 0; i < list.size() && value; ++i)
                    value = list[i].first() == list[0].first() && list[i].second() == list[0].second();
            }
            
            return value;
        }

        /**
         * @brief Describe if the graph is complete.
         * 
         * @return true if the graph is complete, false otherwise.
         */
        bool isComplete() const {
            ArrayList<Pair<int, int>> list = graph.degreeList();

            bool value = true;
            if(!graph.isDigraph()) {
                for(int i = 0; i < list.size() && value; ++i) 
                    value = list[i].first() == list.size() - 1;
            } else {
                for(int i = 0; i < list.size() && value; ++i)
                    value = list[i].first() == list.size() - 1 && list[i].second() == list.size() - 1;
            }

            return value;
        }

        /**
         * @brief Describe if the graph is bipartite.
         * 
         * @return true if the graph is bipartite, false otherwise.
         */
        bool isBipartite() const {
            Map<V, bool> color;
            Map<V, bool> visited;
            bool value = true;

            ArrayList<V> vertices = graph.vertices();
            for(const V& vertex : vertices) {
                color[vertex] = false;
                visited[vertex] = false;
            }

            Stack<V> stack;
            for(int i = 0; i < graph.size() && value; ++i) {
                if(!visited[i]) {

                    stack.push(vertices[i]);
                    while(!stack.isEmpty() && value) {
                        V u = stack.pop();

                        visited[u] = true;
                        for(V v : graph.setOfNeighbors(u)) {
                            if(!visited[v]) {
                                color[v] = !color[u];
                                stack.push(v);
                            } else if(color[v] == color[u]) {
                                value = false;
                            }
                        }
                    }
                } 
            }
            
            return value;
        }

        /**
         * @brief Describe if the graph is a tree.
         * 
         * @return true if the graph is a tree, false otherwise.
         */
        bool isTree() const {
            ArrayList<V> vertices = graph.vertices();
            UnionFind<V> uf(vertices);

            for(Edge<V> e : graph.setOfEdges()) 
                uf.unify(e.getSource(), e.getDestination());

            return uf.numberOfComponents() == 1 && graph.sizeEdges() == graph.size() - 1;
        }

        /**
         * @brief Describe if the graph is a forest.
         * 
         * @return true if the graph is a forest, false otherwise.
         */
        bool isForest() const {
            ArrayList<V> vertices = graph.vertices();
            UnionFind<V> uf(vertices);

            for(Edge<V> e : graph.setOfEdges()) 
                uf.unify(e.getSource(), e.getDestination());

            return graph.sizeEdges() == graph.size() - uf.numberOfComponents();
        }

        /**
         * @brief Describe if the graph is cyclic.
         * 
         * @return true if the graph is cyclic, false otherwise.
         */
        bool isCyclic() const {
            ArrayList<V> vertices = graph.vertices();
            Map<V, V> parent;
            Map<V, char> visited;
            for(const V& vertex : vertices) visited[vertex] = 'w';
            
            Stack<V> stack;
            for(const V& vertex : vertices) {
                if(visited[vertex] == 'w') {
                    stack.push(vertex);
                    parent[vertex] = vertex;
                }

                while(!stack.isEmpty()) {
                    bool done = true;
                    V v = stack.peek();
                    if(visited[v] == 'w') visited[v] = 'g';

                    for(V u : graph.setOfNeighbors(v)) {
                        if(u != parent[v]) {
                            if(visited[u] == 'w') {
                                stack.push(u);
                                parent[u] = v;
                                done = false;
                                break;
                            } else if(visited[u] == 'g') {
                                return true;
                            } 
                        }
                    }

                    if(done) visited[stack.pop()] = 'b';
                }
            }

            return false;
        }

        /**
         * @brief Describe if the graph is Eulerian.
         * 
         * @return true if the graph is Eulerian, false otherwise.
         */
        bool isEulerian() const {
            ArrayList<Pair<int, int>> list = graph.degreeList();

            if(graph.isDigraph()) {
                bool value = true;
                int j = 0, k = 0;
                for(int i = 0; i < list.size() && value; ++i) {
                    value = list[i].first() - list[i].second() <= 1 || list[i].second() - list[i].first() <= 1;
                    
                    if(value) {
                        if(list[i].first() - list[i].second() == 1) ++j;
                        if(list[i].second() - list[i].first() == 1) ++k;
                    }
                }

                return value && ((j == 1 && k == 1) || (j == 0 && k == 0));
            }

            int j = 0;
            for(int i = 0; i < list.size(); ++i) 
                if(list[i].first() % 2 != 0) ++j;

            return j == 2 || j == 0;
        }
};

#endif