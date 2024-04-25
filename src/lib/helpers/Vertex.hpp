/**
 * @file Vertex.hpp
 * @author Fernando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementation of a Vertex class, a templated container that represents a vertex in a graph.
 *        The class allows associating a label of type T with a corresponding weight of type double. It provides
 *        multiple constructors for creating vertices, including default, label-only, and label-weight constructors.
 *        Additionally, the class overloads several comparison operators, such as equality, inequality, less than,
 *        less than or equal, greater than, and greater than or equal, to compare vertices based on their labels.
 * @version 1.0.0
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief Represents a vertex in a graph.
 * 
 * @tparam T The type of the vertex label.
 */
template <class T> class Vertex {
    private: 
        T label; ///< The label of the vertex.
        double weight = 0.0; ///< The weight associated with the vertex.

    public:

        /**
         * @brief Default constructor for a vertex.
         */
        Vertex(): label(T()) {}

        /**
         * @brief Constructor for a vertex with a given label and weight.
         * 
         * @param label The label of the vertex.
         * @param weight The weight associated with the vertex (default is 0.0).
         */
        Vertex(T label, double weight = 0.0): label(label), weight(weight) {}

        /**
         * @brief Construct a new Vertex object from another vertex.
         * 
         * @param other The vertex to copy.
         */
        Vertex(const Vertex<T>& other): label(other.label), weight(other.weight) {}

        /**
         * @brief Destructor for a vertex.
         */
        ~Vertex() {}

        /**
         * @brief Overloaded assignment operator for a vertex.
         * 
         * @param other The vertex to copy.
         * @return Vertex<T>& The vertex after copying.
         */
        Vertex<T>& operator=(const Vertex<T>& other) {
            if (this != &other) {
                label = other.label;
                weight = other.weight;
            }

            return *this;
        }

        /**
         * @brief Gets the label of the vertex.
         * 
         * @return The label of the vertex.
         */
        T getLabel() const {
            return this->label;
        }

        /**
         * @brief Gets the weight of the vertex.
         * 
         * @return The weight of the vertex.
         */
        double getWeight() const {
            return this->weight;
        }

        /**
         * @brief Sets the weight of the vertex.
         * 
         * @param weight The weight to set.
         */
        void setWeight(double weight) {
            this->weight = weight;
        }

        /**
         * @brief Checks if the vertex has a non-zero weight.
         * 
         * @return True if the vertex has a weight, false otherwise.
         */
        bool hasWeight() const {
            return this->weight != 0.0;
        }

        /**
         * @brief Overloaded stream insertion operator to print the vertex.
         * 
         * @param strm The output stream.
         * @param v The vertex to print.
         * @return std::ostream& The output stream after printing the vertex.
         */
        friend std::ostream& operator<<(std::ostream& strm, const Vertex<T>& v) {
            strm << ((v.weight != 0.0) ? "[" : "") << v.label;
            if(v.weight != 0.0) strm << ", " << v.weight; 
            return strm << ((v.weight != 0.0) ? "]" : "");
        }

        /**
         * @brief Overloaded equality operator for vertices.
         * 
         * @param v1 The first vertex.
         * @param v2 The second vertex.
         * @return True if the vertices are equal, false otherwise.
         */
        friend bool operator==(const Vertex<T>& v1, const Vertex<T>& v2) {
            if(v1.weight != 0.0 && v2.weight != 0.0) 
                return v1.weight == v2.weight;

            if constexpr (std::is_same_v<T, std::string>) 
                return v1.label.compare(v2.label) == 0;
            
            return v1.label == v2.label;
        }

        /**
         * @brief Overloaded less-than operator for vertices.
         * 
         * @param v1 The first vertex.
         * @param v2 The second vertex.
         * @return True if v1 is less than v2, false otherwise.
         */
        friend bool operator<(const Vertex<T>& v1, const Vertex<T>& v2) {
            if(v1.weight != 0.0 && v2.weight != 0.0) 
                return v1.weight < v2.weight;
                
            if constexpr (std::is_same_v<T, std::string>) 
                return v1.label.compare(v2.label) < 0;
            
            return v1.label < v2.label;
        }

        // Other comparison operator overloads (!=, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 == v2); }
        inline friend bool operator>(const Vertex<T>& v1, const Vertex<T>& v2) { return v2 < v1; }
        inline friend bool operator<=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 > v2); }
        inline friend bool operator>=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 < v2); }
};

#endif