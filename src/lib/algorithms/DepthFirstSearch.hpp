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

        Path<V> dfs(const V* vertex) const {
            if(!adj.contains(vertex)) 
                throw std::invalid_argument("The given vertex doesn't belongs to the current graph.");

            Set<V> visited;
            ArrayList<V> vertices = adj.keys();

            Path<V> path;
            Stack<V> stack;
            stack.push(vertex);
            while(!stack.isEmpty()) {
                V v = stack.pop();
                visited.add(v);
                path.add(v);

                for(V u : adj.get(v)) if(!visited.contains(u)) stack.push(u);
            }

            return path;
        }
};

#endif