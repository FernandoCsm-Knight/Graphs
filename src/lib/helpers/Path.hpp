#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <stdexcept>

#include "../datastructs/ArrayList.hpp"

template <class V> class Path {
    private:
        ArrayList<V> path;
        double weight = 0.0;

    public:

        Path() {
            path = ArrayList<V>();
            weight = 0.0;
        }

        Path(double weight) {
            this->weight = weight;
        }

        Path(const ArrayList<V> path, double weight) {
            this->path = path;
            this->weight = weight;
        }

        Path(const Path<V>& other) {
            path = other.path;
            weight = other.weight;
        }

        Path<V>& operator=(const Path<V>& other) {
            if (this != &other) {
                path = other.path;
                weight = other.weight;
            }

            return *this;
        }

        double getWeight() const {
            return weight;
        }

        void setWeight(double weight) {
            this->weight = weight;
        }

        ArrayList<V> getPath() const {
            return path;
        }

        void add(const V& vertex, double weight = 0.0) {
            path.add(vertex);
            this->weight += weight;
        }

        void addParent(const V& vertex, double weight = 0.0) {
            path.unshift(vertex);
            this->weight += weight;
        }

        void remove(const V& vertex, double weight = 0.0) {
            path.pop(vertex);
            this->weight -= weight;
        }

        void removeParent(const V& vertex, double weight = 0.0) {
            path.shift(vertex);
            this->weight -= weight;
        }

        bool operator==(const Path<V>& other) const {
            return path == other.path;
        }

        bool operator!=(const Path<V>& other) const {
            return path != other.path;
        }

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