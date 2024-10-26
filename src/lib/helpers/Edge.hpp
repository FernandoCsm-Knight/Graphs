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

/**
 * @brief Represents an edge in a graph.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Edge {
    private: 
        V src = V(); ///< The source vertex of the edge.
        V dest = V(); ///< The destination vertex of the edge.
        double weight = 0.0; ///< The weight associated with the edge.
        bool isDir = false; ///< Indicates whether the edge is directed.

    public:

        /**
         * @brief Default constructor for an edge.
         */
        Edge() {}

        /**
         * @brief Construct a new Edge object from a source and destination vertex.
         * 
         * @param src The source vertex.
         * @param dest The destination vertex.
         * @param weight The weight associated with the edge (default is 0.0).
         * @param isDirected True if the edge is directed, false otherwise.
         */
        Edge(const V& src, const V& dest, bool isDirected = false, double weight = 0.0): src(src), dest(dest), weight(weight), isDir(isDirected) {}

         /**
         * @brief Construct a new Edge object from an existing Edge object.
         * 
         * @param edge The Edge object to copy.
         */
        Edge(const Edge<V>& edge): src(edge.src), dest(edge.dest), weight(edge.weight), isDir(edge.isDir) {}

        /**
         * @brief Destructor for an edge.
         */
        ~Edge() {}

        /**
         * @brief Overloaded assignment operator to copy an edge.
         * 
         * @param edge The edge to copy.
         * @return Edge<V>& The edge after copying.
         */
        Edge<V>& operator=(const Edge<V>& edge) {
            if(this != &edge) {
                this->src = edge.src;
                this->dest = edge.dest;
                this->weight = edge.weight;
                this->isDir = edge.isDir;
            }

            return *this;
        }

        /**
         * @brief Gets the source vertex of the edge.
         * 
         * @return The source vertex of the edge.
         */
        const V& getSource() const { return this->src; }

        /** 
         * @brief Gets the destination vertex of the edge.
         * 
         * @return The destination vertex of the edge.
         */
        const V& getDestination() const { return this->dest; }

        /**
         * @brief Gets the weight of the edge.
         * 
         * @return The weight of the edge.
         */
        inline double getWeight() const { return this->weight; }

        /**
         * @brief Checks if the edge is directed.
         * 
         * @return True if the edge is directed, false otherwise.
         */
        inline bool isDirected() const { return this->isDir; }

        /**
         * @brief Checks if the edge has a non-zero weight.
         * 
         * @return True if the edge has a weight, false otherwise.
         */
        bool hasWeight() const {
            return this->weight != 0.0;
        }

        /**
         * @brief Sets the directionality of the edge.
         * 
         * @param value True if the edge is directed, false otherwise.
         */
        void setDirected(bool value) {
            this->isDir = value;
        }

        /**
         * @brief Sets the weight of the edge.
         * 
         * @param value The weight of the edge.
         */
        void setWeight(double value) {
            this->weight = value;
        }

        /**
         * @brief Gets the other vertex of the edge given one vertex.
         * 
         * @param vertex One vertex of the edge.
         * @return The other vertex of the edge.
         */
        V srcDest(V vertex) const {
            if(vertex == this->src) return this->dest;
            else if(vertex == this->dest) return this->src;
            else throw std::invalid_argument("Vertex is not in this edge");
        }

        /**
         * @brief Checks if the edge contains a given vertex.
         * 
         * @param vertex The vertex to check.
         * @return True if the edge contains the vertex, false otherwise.
         */
        bool contains(const V& vertex) const {
            return vertex == this->src || vertex == this->dest;
        }

        /**
         * @brief Inverts the direction of the edge.
         */
        void invert() {
            V temp = this->src;
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
            if(e1.isDirected() || e2.isDirected()) 
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
            if(e1.src == e2.src)
                return e1.dest < e2.dest;

            return e1.src < e2.src;
        }

        // Other comparison operator overloads (!=, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const Edge& e1, const Edge& e2) { return !(e1 == e2); }
        inline friend bool operator>(const Edge& e1, const Edge& e2) { return e2 < e1; }
        inline friend bool operator<=(const Edge& e1, const Edge& e2) { return !(e1 > e2); }
        inline friend bool operator>=(const Edge& e1, const Edge& e2) { return !(e1 < e2); }
};

#endif