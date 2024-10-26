#ifndef BREATH_FIRST_SEARCH_HPP
#define BREATH_FIRST_SEARCH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/Queue.hpp"

#include "../helpers/Path.hpp"

template <class V> class Graph;

template <class V> class BreathFirstSearch {
    private:
        const Graph<V>& graph;

    public:
        explicit BreathFirstSearch(const Graph<V>& graph): graph(graph) {}

        Path<V> bfs(const V& vertex) const {
            if(!graph.contains(vertex))
                throw std::invalid_argument("The given vertex doesn't belongs to the current graph.");

            ArrayList<V> vertices = graph.vertices();
            Set<V> visited;

            Path<V> path;
            Queue<V> queue;
            queue.push(vertex);
            visited.add(vertex);
            while(!queue.isEmpty()) {
                V v = queue.pop();
                path.add(v);

                for(const V& u : graph[v]) {
                    if(!visited.contains(u)) {
                        visited.add(u);
                        queue.push(u);
                    }
                }
            }
            
            return path;
        }
};

#endif