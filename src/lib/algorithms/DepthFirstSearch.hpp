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

            Map<V, int> idxs;
            ArrayList<V> vertices = adj.keys();

            Path<V> path;
            Stack<V> stack;

            stack.push(vertex);
            while(!stack.isEmpty()) {
                V v = stack.peek();
                if(!idxs.contains(v)) idxs[v] = 0;
                path.add(v);

                Set<V> neighbors = adj.get(v);
                while(idxs[v] < neighbors.size() && idxs.contains(neighbors.get(idxs[v]))) {
                    idxs[v]++;
                }
                
                if(idxs[v] < neighbors.size()) stack.push(neighbors.get(idxs[v]));
                else stack.pop();

                if(stack.isEmpty()) {
                    int i = 0;
                    while(i < vertices.size() && idxs.contains(vertices[i])) ++i;
                    if(i < vertices.size()) stack.push(vertices[i]);
                }
            }

            return path;
        }
};

#endif