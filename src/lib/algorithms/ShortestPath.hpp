#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/PriorityQueue.hpp"
#include "../helpers/Edge.hpp"
#include "../helpers/Path.hpp"

template <class V> class Graph;

template <class V> class ShortestPath {
    private:
        const Map<V, Set<V>> adj;
        const Set<Edge<V>> edges;
        const Graph<V>& graph;
        
        void bellmanFord(Map<V, double>& distances, Map<V, V>& parents) const {
            for(int i = 0; i < adj.size() - 1; ++i) {
                for(Edge<V> edge : edges) {
                    if(distances[edge.getSource()] + edge.getWeight() < distances[edge.getDestination()]) {
                        distances[edge.getDestination()] = distances[edge.getSource()] + edge.getWeight();
                        parents[edge.getDestination()] = edge.getSource();
                    }
                }
            }

            for(int i = 0; i < adj.size() - 1; ++i) {
                for(Edge<V> edge : edges) {
                    if(distances[edge.getSource()] + edge.getWeight() < distances[edge.getDestination()]) {
                        distances[edge.getDestination()] = -std::numeric_limits<double>::infinity();
                        parents[edge.getDestination()] = edge.getSource();
                    }
                }
            }
        }

        void dijkstra(const V& vertex, Map<V, double>& distances, Map<V, V>& parents) const {
            PriorityQueue<Pair<double, V>> queue;
            Set<V> visited;

            queue.push(Pair<double, V>(0.0, vertex));
            while(!queue.isEmpty()) {
                V w = queue.poll().second();

                if(!visited.contains(w)) {
                    visited.add(w);
                    for(const V& u : adj.get(w)) {
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
        }

    public: 
        explicit ShortestPath(const Graph<V>& graph) : 
            adj(graph.adjacencyList()),  
            edges(graph.getEdges()), 
            graph(graph) {}

        Map<V, Map<V, double>> floydWarshal() const {
            ArrayList<V> vertices = this->adj.keys();
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

        int distance(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return 0;

            ArrayList<V> vertices = adj.keys();
            PriorityQueue<Pair<int, V>> queue;
            Set<V> visited;

            Pair<int, V> pair(0, src);
            queue.push(pair);
            while(!queue.isEmpty() && pair.second() != dest) {
                pair = queue.poll();

                if(!visited.contains(pair.second())) {
                    visited.add(pair.second());
                    for(V u : adj.get(pair.second())) 
                        if(!visited.contains(u)) 
                            queue.push(Pair<int, V>(pair.first() + 1, u));
                }
            }

            return (pair.second() == dest) ? pair.first() : -1;
        }

        Map<V, Path<V>> shortestPath(const V& vertex) const {
            if(!adj.contains(vertex)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            bool hasNegativeWeight = false;
            for(int i = 0; i < edges.size() && !hasNegativeWeight; i++) 
                hasNegativeWeight = edges.get(i).getWeight() < 0;

            ArrayList<V> vertices = adj.keys();
            Map<V, double> distances;
            Map<V, V> parents;

            for(V v : vertices) distances[v] = std::numeric_limits<double>::infinity();

            distances[vertex] = 0;

            if(hasNegativeWeight) bellmanFord(distances, parents);
            else dijkstra(vertex, distances, parents);   
            
            Map<V, Path<V>> map;
            for(int i = 0; i < vertices.size(); i++) {
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