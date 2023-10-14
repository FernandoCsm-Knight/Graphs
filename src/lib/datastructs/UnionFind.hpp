/**
 * @file UnionFind.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of the UnionFind data structure.
 *        It is used to keep track of a set of elements partitioned
 *        into a number of disjoint subsets.
 * @version 1.0.0
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <iostream>
#include <stdexcept>

/**
 * UnionFind is a data structure that keeps track of a set of 
 * elements partitioned into a number of disjoint subsets.
 * 
 * It supports two operations:
 * - Find: Determine which subset a particular element is in.
 * - Union: Join two subsets into a single subset.
 */
class UnionFind {
    private:
        int* ids; ///< The array of ids.
        int* sizes; ///< The array of sizes.
        int count; ///< The number of components.
        int length; ///< The length of the arrays.
    
    public:
        /**
         * @brief Construct a new Union Find object
         * 
         * @param size The size of the UnionFind.
         */
        UnionFind(int size) {
            if(size <= 0)
                throw std::invalid_argument("Size must be greater than 0");

            ids = new int[size];
            sizes = new int[size];
            count = 0;
            length = size;

            for(int i = 0; i < size; i++) {
                ids[i] = i;
                sizes[i] = 1;
                count++;
            }
        }

        /**
         * @brief Destroy the Union Find object deleting the arrays.
         */
        ~UnionFind() {
            delete[] ids;
            delete[] sizes;
        }

        /**
         * @brief Find the root of the element p.
         *        It uses path compression to optimize the search.
         *        It runs in amortized constant time.
         * 
         * @param p The element to find the root.
         * @return int The root of the element p.
         */
        int find(int p) {
            if(p < 0 || p >= length) 
                throw std::invalid_argument("Index out of bounds");

            int root = ids[p];
            while(root != ids[root])
                root = ids[root];

            while(ids[p] != root) {
                int newp = ids[p]; 
                ids[p] = root; 
                p = newp; 
            }

            return root;
        }

        /**
         * @brief Unify the elements p and q.
         * 
         * @param p The first element.
         * @param q The second element.
         */
        void unify(int p, int q) {
            int rootP = this->find(p);
            int rootQ = this->find(q);

            if(rootP != rootQ) {
                if(sizes[rootP] < sizes[rootQ]) {
                    ids[rootP] = rootQ;
                    sizes[rootQ] += sizes[rootP];
                } else {
                    ids[rootQ] = rootP;
                    sizes[rootP] += sizes[rootQ];
                }

                count--;
            }
        }

        /**
         * @brief Get the number of components.
         * 
         * @return int The number of components.
         */
        int numberOfComponents() const {
            return count;
        }

        /**
         * @brief Get the size of the component that p belongs to.
         * 
         * @param p The element to get the size.
         * @return int The size of the component that p belongs to.
         */
        int componentSize(int p) {
            return sizes[this->find(p)];
        }
        
        /**
         * @brief Check if the elements p and q are connected.
         * 
         * @param p The first element.
         * @param q The second element.
         * @return True if the elements p and q are connected, false otherwise.
         */
        bool connected(int p, int q) {
            return this->find(p) == this->find(q);
        }

        /**
         * @brief Print the UnionFind.
         * 
         * @param os The output stream.
         * @param uf The UnionFind to print.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const UnionFind& uf) {
            os << "UnionFind(" << uf.count << "): [";
            for(int i = 0; i < uf.count; i++) {
                os << uf.ids[i];
                if(i != uf.count - 1)
                    os << ", ";
            }
            os << "]";

            return os;
        }
};

#endif