#ifndef WIPEST_PATH_HPP
#define WIPEST_PATH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/PriorityQueue.hpp"
#include "../helpers/Edge.hpp"
#include "../helpers/Path.hpp"

template <class V> class Graph;

template <class V> class WidestPath {
    private:
        const Graph<V>& graph;
        const Set<Edge<V>>& edges;

        Map<V, Path<V>> parentsToPath(Map<V, V>& parents, ArrayList<V>& vertices, Map<V, double> weights) const {
            Map<V, Path<V>> map;

            for(int i = 0; i < vertices.size(); ++i) {
                Path<V> path;
                path.setWeight(weights[vertices[i]]);

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

    public:
        explicit WidestPath(const Graph<V>& graph): graph(graph), edges(graph.setOfEdges()) {}

        Map<V, Path<V>> widestPath(const V& vertex) const {
            PriorityQueue<Pair<double, V>> queue(HeapType::MAX);
            Set<V> visited;
            Map<V, V> parents;
            Map<V, double> weights;
            ArrayList<V> vertices = graph.vertices();

            for(const V& v : vertices) {
                if(v == vertex) {
                    weights[v] = std::numeric_limits<double>::infinity();
                } else {
                    weights[v] = -std::numeric_limits<double>::infinity();
                }
            }

            queue.push(Pair<double, V>(std::numeric_limits<double>::infinity(), vertex));
            while(!queue.isEmpty()) {
                V u = queue.poll().second();
                visited.add(u);

                for(const V& v : graph[u]) {
                    if(!visited.contains(v)) {
                        double min = weights[u] < graph.weight(u, v) ? weights[u] : graph.weight(u, v);

                        if(min > weights[v]) {
                            weights[v] = min;
                            parents[v] = u;
                        }

                        queue.push(Pair<double, V>(weights[v], v));
                    }
                }
            }

            return parentsToPath(parents, vertices, weights);
        }

        Map<V, Path<V>> narrrowestPath(const V& vertex) const {
            PriorityQueue<Pair<double, V>> queue;
            Set<V> visited;
            Map<V, V> parents;
            Map<V, double> weights;
            ArrayList<V> vertices = graph.vertices();

            for(const V& v : vertices) {
                if(v == vertex) {
                    weights[v] = -std::numeric_limits<double>::infinity();
                } else {
                    weights[v] = std::numeric_limits<double>::infinity();
                }
            }

            queue.push(Pair<double, V>(-std::numeric_limits<double>::infinity(), vertex));
            while(!queue.isEmpty()) {
                V u = queue.poll().second();
                visited.add(u);

                for(const V& v : graph[u]) {
                    if(!visited.contains(v)) {
                        double max = weights[u] > graph.weight(u, v) ? weights[u] : graph.weight(u, v);

                        if(max < weights[v]) {
                            weights[v] = max;
                            parents[v] = u;
                        }

                        queue.push(Pair<double, V>(weights[v], v));
                    }
                }
            }

            return parentsToPath(parents, vertices, weights);
        }
};

#endif
