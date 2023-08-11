#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <stdexcept>

#include "Vertex.hpp"

template <class V> class Edge {
    private: 
        Vertex<V> src = nullptr;
        Vertex<V> dest = nullptr;
        double weight = 0.0;
        bool isDir = false;

    public:

        Edge() {}
        Edge(const Edge<V>& edge): src(edge.src), dest(edge.dest), weight(edge.weight), isDir(edge.isDir) {}
        Edge(Vertex<V> src, Vertex<V> dest, double weight = 0.0): src(src), dest(dest), weight(weight) {}
        ~Edge() {}

        inline Vertex<V> getSource() { return this->src; }
        inline Vertex<V> getDestination() { return this->dest; }
        inline double getWeight() { return this->weight; }

        void setDirect(bool value) {
            this->isDir = value;
        }

        bool isDirect() {
            return this->isDir;
        }

        Vertex<V> srcDest(Vertex<V> vertex) {
            if(vertex == this->src) return this->dest;
            else if(vertex == this->dest) return this->src;
            else throw std::invalid_argument("Vertex is not in this edge");
        }

        friend std::ostream& operator<<(std::ostream& strm, const Edge& edge) {
            strm << ((edge.isDir) ? "(" : "{") << edge.src << ", " << edge.dest;
            if(edge.weight != 0.0) strm << ", " << edge.weight;
            return strm << ((edge.isDir) ? ")" : "}");
        }

        friend bool operator==(const Edge& e1, const Edge& e2) {
            if(e1.weight != 0.0 && e2.weight != 0.0) 
                return e1.weight == e2.weight;

            return e1.src == e2.src && e1.dest == e2.dest;
        }

        friend bool operator<(const Edge& e1, const Edge& e2) {
            if(e1.weight != 0.0 && e2.weight != 0.0) 
                return e1.weight < e2.weight;

            return e1.src < e2.src && e1.dest < e2.dest;
        }

        inline friend bool operator!=(const Edge& e1, const Edge& e2) { return !(e1 == e2); }
        inline friend bool operator>(const Edge& e1, const Edge& e2) { return e2 < e1; }
        inline friend bool operator<=(const Edge& e1, const Edge& e2) { return !(e1 > e2); }
        inline friend bool operator>=(const Edge& e1, const Edge& e2) { return !(e1 < e2); }
};

#endif