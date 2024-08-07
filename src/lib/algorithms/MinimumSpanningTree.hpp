#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include "../datastructs/IndexedPriorityQueue.hpp"
#include "../datastructs/UnionFind.hpp"
#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"

#include "../helpers/Edge.hpp"
#include "../helpers/Path.hpp"

#include <functional>

template <class V> class Graph;

template <class V> class MinimumSpanningTree {
    private:
        const Graph<V>& graph;
        const Map<V, Set<V>> adj;

    public:
        explicit MinimumSpanningTree(const Graph<V>& graph) : graph(graph), adj(graph.adjacencyList()) {}

        Path<Edge<V>> kruskal() const {
            UnionFind<V> uf(adj.keys());
            Path<Edge<V>> path;
            
            ArrayList<Edge<V>> edges(std::function<int(const Edge<V>&, const Edge<V>&)>([&](const Edge<V>& edge1, const Edge<V>& edge2) {
                int result = 0;
                if(edge1.getWeight() < edge2.getWeight()) result = -1;
                if(edge1.getWeight() > edge2.getWeight()) result = 1;
                return result;
            }));
            
            for(const Edge<V>& edge : graph.getEdges()) edges.add(edge);
            edges.sort();

            for(const Edge<V>& edge : edges) {
                V u = edge.getSource();
                V v = edge.getDestination();

                if(!uf.connected(u, v)) {
                    uf.unify(u, v);
                    path.add(edge);
                }
            }

            return path;
        }

        Path<Edge<V>> prim() const {
            IndexedPriorityQueue<Pair<double, Edge<V>>> queue(graph.size());
            ArrayList<V> vertices = adj.keys();
            bool visited[graph.size()];
            Path<Edge<V>> path;

            for(int i = 0; i < graph.size(); ++i) 
                visited[i] = false;

            queue.insert(0, Pair<double, Edge<V>>(0.0, Edge<V>(vertices[0], vertices[0], graph.isDigraph())));

            while(!queue.isEmpty()) {
                visited[queue.minKey()] = true;
                Pair<double, Edge<V>> pair = queue.poll();
                path.add(pair.second(), pair.first());

                V u = pair.second().getDestination();
                for(V w : adj.get(u)) {
                    int indexW = vertices.indexOf(w, true);
                
                    if(!visited[indexW]) {
                        double weight = graph.weight(u, w);

                        if(queue.contains(indexW)) 
                            queue.decrease(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, graph.isDigraph(), weight)));
                        else 
                            queue.insert(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, graph.isDigraph(), weight)));
                    }
                }
            }

            return path;
        }
};

#endif