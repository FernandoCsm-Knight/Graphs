#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "Map.hpp"

#include "helpers/Vertex.hpp"
#include "helpers/Edge.hpp"

template <class V> class Graph {
    private:
        Map<Vertex<V>, LinkedList<Edge<V>>> map;
        bool isDig;

    public: 
        Graph(bool isDigraph = false): isDig(isDigraph) {}
        ~Graph() {}

        void addEdge(V src, V dest, double weight = 0.0) {
            Vertex<V> srcVertex = Vertex(src);
            Vertex<V> destVertex = Vertex(dest);

            Edge<V> edge = Edge<V>(srcVertex, destVertex, weight);
            edge.setDirect(this->isDig);
            
            map[srcVertex].add(edge);
            if(!this->isDig) map[destVertex].add(edge);
        }

        void removeEdge(V src, V dest) {
            Vertex<V> srcVertex = Vertex(src);
            Vertex<V> destVertex = Vertex(dest);

            Edge<V> edge = Edge<V>(srcVertex, destVertex);
            edge.setDirect(this->isDig);

            map[srcVertex].pop(edge, true);
            if(!this->isDig) map[destVertex].pop(edge, true);
        }

        void addVertex(V vertex) {
            map[Vertex<V>(vertex)] = LinkedList<Edge<V>>();
        }

        void removeVertex(V vertex) {
            map.remove(Vertex<V>(vertex));
        }

        int size() const {
            return map.size();
        }

        int degree(V vertex) const {
            return map[Vertex<V>(vertex)].size();
        }

        LinkedList<Edge<V>> getEdges(V vertex) const {
            return map[Vertex<V>(vertex)];
        }

        Map<Vertex<V>, LinkedList<Vertex<V>>> adjacentList() const {
            ArrayList<Vertex<V>> keys = map.keys();
            ArrayList<LinkedList<Edge<V>>> values = map.values();

            Map<Vertex<V>, LinkedList<Vertex<V>>> adj;
            for(int i = 0; i < keys.size(); i++) {
                adj[keys[i]] = LinkedList<Vertex<V>>();
                for(int j = 0; j < values[i].size(); j++) {
                    adj[keys[i]].add(values[i][j].srcDest(keys[i]));
                }
            }

            return adj;
        }

        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            ArrayList<Vertex<V>> keys = graph.map.keys();
            ArrayList<LinkedList<Edge<V>>> values = graph.map.values();

            for(int i = 0; i < keys.size(); i++) {
                strm << keys[i] << ": " << values[i] << std::endl;
            } 

            return strm;
        }
};

#endif