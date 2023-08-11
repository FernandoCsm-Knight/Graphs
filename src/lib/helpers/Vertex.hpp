#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <stdexcept>

template <class T> class Vertex {
    private: 
        T label;
        double weight = 0.0;

    public:
        Vertex(): label(T()) {}
        Vertex(T label, double weight = 0.0): label(label), weight(weight) {}
        ~Vertex() {}

        void setWeight(double weight) {
            this->weight = weight;
        }

        friend std::ostream& operator<<(std::ostream& strm, const Vertex<T>& v) {
            strm << ((v.weight != 0.0) ? "[" : "") << v.label;
            if(v.weight != 0.0) strm << ", " << v.weight; 
            return strm << ((v.weight != 0.0) ? "]" : "");
        }

        friend bool operator==(const Vertex<T>& v1, const Vertex<T>& v2) {
            if(v1.weight != 0.0 && v2.weight != 0.0) 
                return v1.weight == v2.weight;

            if constexpr (std::is_same_v<T, std::string>) {
                return v1.label.compare(v2.label) == 0;
            } 
            
            return v1.label == v2.label;
        }

        friend bool operator<(const Vertex<T>& v1, const Vertex<T>& v2) {
            if(v1.weight != 0.0 && v2.weight != 0.0) 
                return v1.weight < v2.weight;
                
            if constexpr (std::is_same_v<T, std::string>) {
                return v1.label.compare(v2.label) < 0;
            }
            
            return v1.label < v2.label;
        }

        inline friend bool operator!=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 == v2); }
        inline friend bool operator>(const Vertex<T>& v1, const Vertex<T>& v2) { return v2 < v1; }
        inline friend bool operator<=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 > v2); }
        inline friend bool operator>=(const Vertex<T>& v1, const Vertex<T>& v2) { return !(v1 < v2); }

};

#endif