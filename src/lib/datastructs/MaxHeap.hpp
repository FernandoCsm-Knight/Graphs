/**
 * @file MaxHeap.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of the MaxHeap data structure.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MIN_MAX_HEAP_HPP
#define MIN_MAX_HEAP_HPP

#include "Heap.hpp"

/**
 * @brief A class that implements a Max Heap data structure.
 * 
 * A Max Heap is a binary tree-based data structure where the parent node is always greater than or equal to its child nodes.
 * This implementation supports dynamic resizing and operations such as insertion, removal, and access to the maximum and minimum elements.
 * 
 * @tparam T The type of elements stored in the heap.
 */
template <class T> class MaxHeap : public Heap<T> {
    protected:
        /**
         * @brief Comparison function used to maintain the max heap property.
         * 
         * In a MaxHeap, the parent node should always be greater than or equal to the child node.
         * This method is used to compare the parent and child nodes to enforce this property.
         * 
         * @param parent The value of the parent node.
         * @param child The value of the child node.
         * @return true If the parent is less than the child (meaning the heap property needs to be restored).
         * @return false Otherwise.
         */
        bool compare(const T& parent, const T& child) const override {
            return parent < child;
        }

    public:
        /**
         * @brief Default constructor for the MaxHeap.
         * 
         * Initializes an empty MaxHeap with a default capacity.
         */
        MaxHeap() : Heap<T>() {}

        /**
         * @brief Copy constructor for MaxHeap.
         * 
         * Initializes a MaxHeap by copying the contents of an existing MaxHeap.
         * 
         * @param heap The MaxHeap to be copied.
         */
        MaxHeap(const MaxHeap<T>& heap) : Heap<T>(heap) {}

        /**
         * @brief Construct a MaxHeap with a specified capacity.
         * 
         * Initializes an empty MaxHeap with the specified capacity.
         * 
         * @param capacity The initial capacity of the MaxHeap.
         */
        MaxHeap(int capacity) : Heap<T>(capacity) {}

        /**
         * @brief Construct a MaxHeap from an existing array.
         * 
         * Builds a MaxHeap from an array of elements. The heap is not dynamically resizable.
         * 
         * @param arr The array of elements to build the heap from.
         * @param capacity The number of elements in the array.
         */
        MaxHeap(const T* arr, int capacity) : Heap<T>(arr, capacity) {}

        /**
         * @brief Get the maximum element in the MaxHeap.
         * 
         * Since the MaxHeap maintains the property that the largest element is always at the root,
         * this function returns the element at the root (index 0).
         * 
         * @return T The maximum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T max() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            return this->array[0];
        }

        /**
         * @brief Get the minimum element in the MaxHeap.
         * 
         * This function iterates through the heap array to find the smallest element.
         * While the root is the largest element, this function finds the smallest.
         * 
         * @return T The minimum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T min() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            int min = 0;
            for(int i = 1; i < this->length; ++i)
                if(this->array[i] < this->array[min])
                    min = i;
            
            return this->array[min];
        }
};

#endif