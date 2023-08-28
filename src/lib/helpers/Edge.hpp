/**
 * @file Edge.hpp
 * @author Fernando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementation of an Edge class, a templated container that represents an edge in a graph.
 *        The class allows associating a source vertex, a destination vertex, and a weight with an edge.
 *        It provides multiple constructors for creating edges, including default, source-destination-only,
 *        source-destination-weight, and source-destination-weight-directed constructors. Additionally, the
 *        class overloads several comparison operators, such as equality, inequality, less than, less than or
 *        equal, greater than, and greater than or equal, to compare edges based on their source, weight, and
 *        destination vertices. 
 * @version 1.0.0
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <stdexcept>

#include "Vertex.hpp"

/**
 * @brief Represents an edge in a graph.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Edge {
    private: 
        Vertex<V> src = V(); ///< The source vertex of the edge.
        Vertex<V> dest = V(); ///< The destination vertex of the edge.
        double weight = 0.0; ///< The weight associated with the edge.
        bool isDir = false; ///< Indicates whether the edge is directed.

    public:

        /**
         * @brief Default constructor for an edge.
         */
        Edge() {}

        /**
         * @brief Constructor for an edge with a given source, destination, and weight.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         * @param weight The weight associated with the edge (default is 0.0).
         */
        Edge(Vertex<V> src, Vertex<V> dest, double weight = 0.0): src(src), dest(dest), weight(weight) {}

        /**
         * @brief Destructor for an edge.
         */
        ~Edge() {}

        /**
         * @brief Gets the source vertex of the edge.
         * 
         * @return The source vertex of the edge.
         */
        inline Vertex<V> getSource() { return this->src; }

        /**
         * @brief Gets the destination vertex of the edge.
         * 
         * @return The destination vertex of the edge.
         */
        inline Vertex<V> getDestination() { return this->dest; }

        /**
         * @brief Gets the weight of the edge.
         * 
         * @return The weight of the edge.
         */
        inline double getWeight() { return this->weight; }

        /**
         * @brief Sets the directionality of the edge.
         * 
         * @param value True if the edge is directed, false otherwise.
         */
        void setDirect(bool value) {
            this->isDir = value;
        }

        /**
         * @brief Checks if the edge is directed.
         * 
         * @return True if the edge is directed, false otherwise.
         */
        bool isDirect() const {
            return this->isDir;
        }

        /**
         * @brief Checks if the edge has a non-zero weight.
         * 
         * @return True if the edge has a weight, false otherwise.
         */
        bool hasWeight() const {
            return this->weight != 0.0;
        }

        /**
         * @brief Gets the other vertex of the edge given one vertex.
         * 
         * @param vertex One vertex of the edge.
         * @return The other vertex of the edge.
         */
        Vertex<V> srcDest(Vertex<V> vertex) const {
            if(vertex == this->src) return this->dest;
            else if(vertex == this->dest) return this->src;
            else throw std::invalid_argument("Vertex is not in this edge");
        }

        /**
         * @brief Inverts the direction of the edge.
         */
        void invert() {
            Vertex<V> temp = this->src;
            this->src = this->dest;
            this->dest = temp;
        }

        /**
         * @brief Overloaded output stream operator to print an edge.
         * 
         * @param strm The output stream.
         * @param edge The edge to print.
         * @return std::ostream& The output stream after printing the edge.
         */
        friend std::ostream& operator<<(std::ostream& strm, const Edge& edge) {
            strm << ((edge.isDir) ? "(" : "{") << edge.src << ", " << edge.dest;
            if(edge.weight != 0.0) strm << ", " << edge.weight;
            return strm << ((edge.isDir) ? ")" : "}");
        }

        /**
         * @brief Overloaded equality operator to compare two edges based on their source, weight and destination vertices.
         * 
         * @param e1 The first edge to compare.
         * @param e2 The second edge to compare.
         * @return True if the edges are equal, false otherwise.
         */
        friend bool operator==(const Edge& e1, const Edge& e2) {
            if(e1.weight != 0.0 && e2.weight != 0.0) 
                return e1.weight == e2.weight;

            if(e1.isDirect() && e2.isDirect()) 
                return e1.src == e2.src && e1.dest == e2.dest;

            return (e1.src == e2.src && e1.dest == e2.dest) || (e1.src == e2.dest && e1.dest == e2.src);
        }

        /**
         * @brief Overloaded less than operator to compare two edges based on their source, weight and destination vertices.
         * 
         * @param e1 The first edge to compare.
         * @param e2 The second edge to compare.
         * @return True if the first edge is less than the second, false otherwise.
         */
        friend bool operator<(const Edge& e1, const Edge& e2) {
            if(e1.weight != 0.0 && e2.weight != 0.0) 
                return e1.weight < e2.weight;

            if(e1.src == e2.src) 
                return e1.dest < e2.dest;
            else 
                return e1.src < e2.src;
        }

        // Other comparison operator overloads (!=, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const Edge& e1, const Edge& e2) { return !(e1 == e2); }
        inline friend bool operator>(const Edge& e1, const Edge& e2) { return e2 < e1; }
        inline friend bool operator<=(const Edge& e1, const Edge& e2) { return !(e1 > e2); }
        inline friend bool operator>=(const Edge& e1, const Edge& e2) { return !(e1 < e2); }
};

#endif