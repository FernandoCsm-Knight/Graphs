/**
 * @file Path.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a Path data structure.
 *        It is used to represent a path in a graph or
 *        a sequence of elements.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <stdexcept>

#include "../datastructs/ArrayList.hpp"

/**
 * @brief A class representing a path in a graph.
 * 
 * This class manages a sequence of vertices (the path) and the total weight of the path.
 * It provides various methods to manipulate the path and its weight.
 * 
 * @tparam V The type of the vertices in the path.
 */
template <class V> class Path {
    private:
        ArrayList<V> path; /**< The list of vertices in the path */
        double weight = 0.0; /**< The total weight of the path */

    public:

        /**
         * @brief Default constructor for the Path class.
         * 
         * Initializes an empty path with a weight of 0.
         */
        Path() {
            path = ArrayList<V>();
            weight = 0.0;
        }

        /**
         * @brief Constructor that initializes a path with a specified weight.
         * 
         * @param weight The initial weight of the path.
         */
        Path(double weight) {
            this->weight = weight;
        }

        /**
         * @brief Constructor that initializes a path with a specified list of vertices and weight.
         * 
         * @param path The initial list of vertices.
         * @param weight The initial weight of the path.
         */
        Path(const ArrayList<V> path, double weight) {
            this->path = path;
            this->weight = weight;
        }

        /**
         * @brief Copy constructor for the Path class.
         * 
         * Creates a copy of an existing Path object.
         * 
         * @param other The Path object to copy.
         */
        Path(const Path<V>& other) {
            path = other.path;
            weight = other.weight;
        }

        /**
         * @brief Assignment operator for the Path class.
         * 
         * @param other The Path object to assign from.
         * @return Path<V>& Reference to the assigned Path object.
         */
        Path<V>& operator=(const Path<V>& other) {
            if (this != &other) {
                path = other.path;
                weight = other.weight;
            }

            return *this;
        }

        /**
         * @brief Get the number of vertices in the path.
         * 
         * @return int The number of vertices in the path.
         */
        int size() const {
            return path.size();
        }

        /**
         * @brief Get the total weight of the path.
         * 
         * @return double The weight of the path.
         */
        double getWeight() const {
            return weight;
        }

        /**
         * @brief Set the weight of the path.
         * 
         * @param weight The new weight of the path.
         */
        void setWeight(double weight) {
            this->weight = weight;
        }

        /**
         * @brief Get the list of vertices in the path.
         * 
         * @return ArrayList<V> The list of vertices in the path.
         */
        ArrayList<V> getPath() const {
            return path;
        }

        /**
         * @brief Add a vertex to the end of the path and update the weight.
         * 
         * @param vertex The vertex to add.
         * @param weight The weight to add to the total path weight (default is 0).
         */
        void add(const V& vertex, double weight = 0.0) {
            path.add(vertex);
            this->weight += weight;
        }

        /**
         * @brief Add a vertex to the beginning of the path and update the weight.
         * 
         * @param vertex The vertex to add.
         * @param weight The weight to add to the total path weight (default is 0).
         */
        void addParent(const V& vertex, double weight = 0.0) {
            path.unshift(vertex);
            this->weight += weight;
        }

        /**
         * @brief Remove a vertex from the end of the path and update the weight.
         * 
         * @param vertex The vertex to remove.
         * @param weight The weight to subtract from the total path weight (default is 0).
         */
        void remove(const V& vertex, double weight = 0.0) {
            path.pop(vertex);
            this->weight -= weight;
        }

        /**
         * @brief Remove a vertex from the beginning of the path and update the weight.
         * 
         * @param vertex The vertex to remove.
         * @param weight The weight to subtract from the total path weight (default is 0).
         */
        void removeParent(const V& vertex, double weight = 0.0) {
            path.shift(vertex);
            this->weight -= weight;
        }

        /**
         * @brief Equality operator for comparing two paths.
         * 
         * @param other The other Path object to compare with.
         * @return true If the paths are equal.
         * @return false If the paths are not equal.
         */
        bool operator==(const Path<V>& other) const {
            return path == other.path;
        }

        /**
         * @brief Inequality operator for comparing two paths.
         * 
         * @param other The other Path object to compare with.
         * @return true If the paths are not equal.
         * @return false If the paths are equal.
         */
        bool operator!=(const Path<V>& other) const {
            return path != other.path;
        }

        /**
         * @brief Stream insertion operator for outputting the path to an output stream.
         * 
         * @param os The output stream.
         * @param path The Path object to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Path<V>& path) {
            os << "Path: " << ((path.path.size() == 0) ? "{}" : "");
            for (int i = 0; i < path.path.size(); i++) {
                os << path.path.get(i);
                if (i != path.path.size() - 1)
                    os << " -> ";
            }

            os << " | Weight: " << path.weight;
            return os;
        }
};

#endif