#ifndef DEPTH_FIRST_SEARCH_HPP
#define DEPTH_FIRST_SEARCH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/Stack.hpp"

#include "../helpers/Path.hpp"

template <class V> class Graph;

template <class V> class DepthFirstSearch {
    private:
        const Map<V, Set<V>> adj;

    public:
        explicit DepthFirstSearch(const Graph<V>& graph): adj(graph.adjacencyList()) {}

        Path<V> dfs(const V& vertex) const {
            if(!adj.contains(vertex)) 
                throw std::invalid_argument("The given vertex doesn't belongs to the current graph.");

            Path<V> path;
            Stack<V> stack;
            Set<V> visited;
            
            stack.push(vertex);
            visited.add(vertex);
            while(!stack.isEmpty()) {
                V v = stack.pop();
                path.add(v);

                for(V u : adj.get(v)) {
                    if(!visited.contains(u)) {
                        visited.add(u);
                        stack.push(u);
                    }
                }
            }

            return path;
        }
};

#endif