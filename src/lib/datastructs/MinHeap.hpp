/**
 * @file MinHeap.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of the MinHeap data structure.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A class that implements a Min Heap data structure.
 * 
 * A Min Heap is a binary tree-based data structure where the parent node is always smaller than or equal to its child nodes.
 * This implementation supports dynamic resizing and operations such as insertion, removal, and access to the minimum and maximum elements.
 * 
 * @tparam T The type of elements stored in the heap.
 */
template <class T> class MinHeap : public Heap<T> {
    protected:
        /**
         * @brief Comparison function used to maintain the min heap property.
         * 
         * In a MinHeap, the parent node should always be smaller than or equal to the child node.
         * This method is used to compare the parent and child nodes to enforce this property.
         * 
         * @param parent The value of the parent node.
         * @param child The value of the child node.
         * @return true If the parent is greater than the child (meaning the heap property needs to be restored).
         * @return false Otherwise.
         */
        bool compare(const T& parent, const T& child) const override {
            return parent > child;
        }

    public:
        /**
         * @brief Default constructor for the MinHeap.
         * 
         * Initializes an empty MinHeap with a default capacity.
         */
        MinHeap() : Heap<T>() {}

        /**
         * @brief Copy constructor for MinHeap.
         * 
         * Initializes a MinHeap by copying the contents of an existing MinHeap.
         * 
         * @param heap The MinHeap to be copied.
         */
        MinHeap(const MinHeap<T>& heap) : Heap<T>(heap) {}

        /**
         * @brief Construct a MinHeap with a specified capacity.
         * 
         * Initializes an empty MinHeap with the specified capacity.
         * 
         * @param capacity The initial capacity of the MinHeap.
         */
        MinHeap(int capacity) : Heap<T>(capacity) {}

        /**
         * @brief Construct a MinHeap from an existing array.
         * 
         * Builds a MinHeap from an array of elements. The heap is not dynamically resizable.
         * 
         * @param arr The array of elements to build the heap from.
         * @param capacity The number of elements in the array.
         */
        MinHeap(const T* arr, int capacity) : Heap<T>(arr, capacity) {}

        /**
         * @brief Get the minimum element in the MinHeap.
         * 
         * Since the MinHeap maintains the property that the smallest element is always at the root,
         * this function returns the element at the root (index 0).
         * 
         * @return T The minimum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T min() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            return this->array[0];
        }

        /**
         * @brief Get the maximum element in the MinHeap.
         * 
         * This function iterates through the heap array to find the largest element.
         * While the root is the smallest element, this function finds the largest.
         * 
         * @return T The maximum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T max() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            int max = 0;
            for(int i = 1; i < this->length; ++i)
                if(this->array[i] > this->array[max])
                    max = i;

            return this->array[max];
        }
};

#endif